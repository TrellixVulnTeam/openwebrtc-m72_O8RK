// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/editing/spellcheck/idle_spell_check_controller.h"

#include "third_party/blink/public/platform/task_type.h"
#include "third_party/blink/renderer/core/dom/idle_request_options.h"
#include "third_party/blink/renderer/core/editing/commands/undo_stack.h"
#include "third_party/blink/renderer/core/editing/commands/undo_step.h"
#include "third_party/blink/renderer/core/editing/editing_utilities.h"
#include "third_party/blink/renderer/core/editing/editor.h"
#include "third_party/blink/renderer/core/editing/ephemeral_range.h"
#include "third_party/blink/renderer/core/editing/frame_selection.h"
#include "third_party/blink/renderer/core/editing/iterators/character_iterator.h"
#include "third_party/blink/renderer/core/editing/selection_template.h"
#include "third_party/blink/renderer/core/editing/spellcheck/cold_mode_spell_check_requester.h"
#include "third_party/blink/renderer/core/editing/spellcheck/hot_mode_spell_check_requester.h"
#include "third_party/blink/renderer/core/editing/spellcheck/spell_check_requester.h"
#include "third_party/blink/renderer/core/editing/spellcheck/spell_checker.h"
#include "third_party/blink/renderer/core/editing/visible_selection.h"
#include "third_party/blink/renderer/core/editing/visible_units.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/trace_event.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/time.h"

namespace blink {

namespace {

constexpr TimeDelta kColdModeTimerInterval = TimeDelta::FromMilliseconds(1000);
constexpr TimeDelta kConsecutiveColdModeTimerInterval =
    TimeDelta::FromMilliseconds(200);
const int kHotModeRequestTimeoutMS = 200;
const int kInvalidHandle = -1;
const int kDummyHandleForForcedInvocation = -2;
constexpr TimeDelta kIdleSpellcheckTestTimeout = TimeDelta::FromSeconds(10);

}  // namespace

class IdleSpellCheckController::IdleCallback final
    : public ScriptedIdleTaskController::IdleTask {
 public:
  static IdleCallback* Create(IdleSpellCheckController* controller) {
    return MakeGarbageCollected<IdleCallback>(controller);
  }

  explicit IdleCallback(IdleSpellCheckController* controller)
      : controller_(controller) {}

  void Trace(blink::Visitor* visitor) final {
    visitor->Trace(controller_);
    ScriptedIdleTaskController::IdleTask::Trace(visitor);
  }

 private:
  void invoke(IdleDeadline* deadline) final { controller_->Invoke(deadline); }

  const Member<IdleSpellCheckController> controller_;

  DISALLOW_COPY_AND_ASSIGN(IdleCallback);
};

IdleSpellCheckController::~IdleSpellCheckController() = default;

void IdleSpellCheckController::Trace(blink::Visitor* visitor) {
  visitor->Trace(frame_);
  visitor->Trace(cold_mode_requester_);
  DocumentShutdownObserver::Trace(visitor);
}

IdleSpellCheckController* IdleSpellCheckController::Create(LocalFrame& frame) {
  return new IdleSpellCheckController(frame);
}

IdleSpellCheckController::IdleSpellCheckController(LocalFrame& frame)
    : state_(State::kInactive),
      idle_callback_handle_(kInvalidHandle),
      frame_(frame),
      last_processed_undo_step_sequence_(0),
      cold_mode_requester_(ColdModeSpellCheckRequester::Create(frame)),
      cold_mode_timer_(frame.GetTaskRunner(TaskType::kInternalDefault),
                       this,
                       &IdleSpellCheckController::ColdModeTimerFired) {}

SpellCheckRequester& IdleSpellCheckController::GetSpellCheckRequester() const {
  return GetFrame().GetSpellChecker().GetSpellCheckRequester();
}

bool IdleSpellCheckController::IsSpellCheckingEnabled() const {
  return GetFrame().GetSpellChecker().IsSpellCheckingEnabled();
}

void IdleSpellCheckController::DisposeIdleCallback() {
  if (idle_callback_handle_ != kInvalidHandle && IsAvailable())
    GetDocument().CancelIdleCallback(idle_callback_handle_);
  idle_callback_handle_ = kInvalidHandle;
}

void IdleSpellCheckController::Deactivate() {
  state_ = State::kInactive;
  if (cold_mode_timer_.IsActive())
    cold_mode_timer_.Stop();
  cold_mode_requester_->ClearProgress();
  DisposeIdleCallback();
}

void IdleSpellCheckController::SetNeedsInvocation() {
  if (!IsSpellCheckingEnabled() || !IsAvailable()) {
    Deactivate();
    return;
  }

  if (state_ == State::kHotModeRequested)
    return;

  cold_mode_requester_->ClearProgress();

  if (state_ == State::kColdModeTimerStarted) {
    DCHECK(cold_mode_timer_.IsActive());
    cold_mode_timer_.Stop();
  }

  if (state_ == State::kColdModeRequested)
    DisposeIdleCallback();

  IdleRequestOptions* options = IdleRequestOptions::Create();
  options->setTimeout(kHotModeRequestTimeoutMS);
  idle_callback_handle_ =
      GetDocument().RequestIdleCallback(IdleCallback::Create(this), options);
  state_ = State::kHotModeRequested;
}

void IdleSpellCheckController::SetNeedsColdModeInvocation() {
  if (!RuntimeEnabledFeatures::IdleTimeColdModeSpellCheckingEnabled() ||
      !IsSpellCheckingEnabled()) {
    Deactivate();
    return;
  }

  if (state_ != State::kInactive && state_ != State::kInHotModeInvocation &&
      state_ != State::kInColdModeInvocation)
    return;

  DCHECK(!cold_mode_timer_.IsActive());
  TimeDelta interval = state_ == State::kInColdModeInvocation
                           ? kConsecutiveColdModeTimerInterval
                           : kColdModeTimerInterval;
  cold_mode_timer_.StartOneShot(interval, FROM_HERE);
  state_ = State::kColdModeTimerStarted;
}

void IdleSpellCheckController::ColdModeTimerFired(TimerBase*) {
  DCHECK(RuntimeEnabledFeatures::IdleTimeColdModeSpellCheckingEnabled());
  DCHECK_EQ(State::kColdModeTimerStarted, state_);

  if (!IsSpellCheckingEnabled() || !IsAvailable()) {
    Deactivate();
    return;
  }

  idle_callback_handle_ = GetDocument().RequestIdleCallback(
      IdleCallback::Create(this), IdleRequestOptions::Create());
  state_ = State::kColdModeRequested;
}

void IdleSpellCheckController::HotModeInvocation(IdleDeadline* deadline) {
  TRACE_EVENT0("blink", "IdleSpellCheckController::hotModeInvocation");

  // TODO(xiaochengh): Figure out if this has any performance impact.
  GetDocument().UpdateStyleAndLayout();

  HotModeSpellCheckRequester requester(GetSpellCheckRequester());

  requester.CheckSpellingAt(
      GetFrame().Selection().GetSelectionInDOMTree().Extent());

  const uint64_t watermark = last_processed_undo_step_sequence_;
  for (const UndoStep* step :
       GetFrame().GetEditor().GetUndoStack().UndoSteps()) {
    if (step->SequenceNumber() <= watermark)
      break;
    last_processed_undo_step_sequence_ =
        std::max(step->SequenceNumber(), last_processed_undo_step_sequence_);
    if (deadline->timeRemaining() == 0)
      break;
    // The ending selection stored in undo stack can be invalid, disconnected
    // or have been moved to another document, so we should check its validity
    // before using it.
    if (!step->EndingSelection().IsValidFor(GetDocument()))
      continue;
    requester.CheckSpellingAt(step->EndingSelection().Extent());
  }
}

void IdleSpellCheckController::Invoke(IdleDeadline* deadline) {
  DCHECK_NE(idle_callback_handle_, kInvalidHandle);
  idle_callback_handle_ = kInvalidHandle;

  if (!IsSpellCheckingEnabled() || !IsAvailable()) {
    Deactivate();
    return;
  }

  if (state_ == State::kHotModeRequested) {
    state_ = State::kInHotModeInvocation;
    HotModeInvocation(deadline);
    SetNeedsColdModeInvocation();
  } else if (state_ == State::kColdModeRequested) {
    DCHECK(RuntimeEnabledFeatures::IdleTimeColdModeSpellCheckingEnabled());
    state_ = State::kInColdModeInvocation;
    cold_mode_requester_->Invoke(deadline);
    if (cold_mode_requester_->FullyChecked())
      state_ = State::kInactive;
    else
      SetNeedsColdModeInvocation();
  } else {
    NOTREACHED();
  }
}

void IdleSpellCheckController::DidAttachDocument(Document* document) {
  SetContext(document);
}

void IdleSpellCheckController::ContextDestroyed(Document*) {
  Deactivate();
}

void IdleSpellCheckController::ForceInvocationForTesting() {
  if (!IsSpellCheckingEnabled())
    return;

  IdleDeadline* deadline =
      IdleDeadline::Create(CurrentTimeTicks() + kIdleSpellcheckTestTimeout,
                           IdleDeadline::CallbackType::kCalledWhenIdle);

  switch (state_) {
    case State::kColdModeTimerStarted:
      cold_mode_timer_.Stop();
      state_ = State::kColdModeRequested;
      idle_callback_handle_ = kDummyHandleForForcedInvocation;
      Invoke(deadline);
      break;
    case State::kHotModeRequested:
    case State::kColdModeRequested:
      GetDocument().CancelIdleCallback(idle_callback_handle_);
      Invoke(deadline);
      break;
    case State::kInactive:
    case State::kInHotModeInvocation:
    case State::kInColdModeInvocation:
      NOTREACHED();
  }
}

void IdleSpellCheckController::SkipColdModeTimerForTesting() {
  DCHECK(cold_mode_timer_.IsActive());
  cold_mode_timer_.Stop();
  ColdModeTimerFired(&cold_mode_timer_);
}

void IdleSpellCheckController::SetNeedsMoreColdModeInvocationForTesting() {
  cold_mode_requester_->SetNeedsMoreInvocationForTesting();
}

}  // namespace blink
