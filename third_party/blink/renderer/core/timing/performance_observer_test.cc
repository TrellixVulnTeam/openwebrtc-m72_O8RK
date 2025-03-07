// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/timing/performance_observer.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/public/platform/task_type.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_binding_for_testing.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_performance_observer_callback.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/timing/performance.h"
#include "third_party/blink/renderer/core/timing/performance_mark.h"
#include "third_party/blink/renderer/core/timing/performance_observer_init.h"
#include "third_party/blink/renderer/core/timing/window_performance.h"
#include "third_party/blink/renderer/platform/wtf/time.h"

namespace blink {

class MockPerformance : public Performance {
 public:
  explicit MockPerformance(ScriptState* script_state)
      : Performance(TimeTicks(),
                    ExecutionContext::From(script_state)
                        ->GetTaskRunner(TaskType::kPerformanceTimeline)) {}
  ~MockPerformance() override = default;

  ExecutionContext* GetExecutionContext() const override { return nullptr; }
};

class PerformanceObserverTest : public testing::Test {
 protected:
  void Initialize(ScriptState* script_state) {
    v8::Local<v8::Function> callback =
        v8::Function::New(script_state->GetContext(), nullptr).ToLocalChecked();
    base_ = MakeGarbageCollected<MockPerformance>(script_state);
    cb_ = V8PerformanceObserverCallback::Create(callback);
    observer_ = new PerformanceObserver(ExecutionContext::From(script_state),
                                        base_, cb_);
  }

  bool IsRegistered() { return observer_->is_registered_; }
  int NumPerformanceEntries() { return observer_->performance_entries_.size(); }
  void Deliver() { observer_->Deliver(); }

  Persistent<MockPerformance> base_;
  Persistent<V8PerformanceObserverCallback> cb_;
  Persistent<PerformanceObserver> observer_;
};

TEST_F(PerformanceObserverTest, Observe) {
  V8TestingScope scope;
  Initialize(scope.GetScriptState());

  NonThrowableExceptionState exception_state;
  PerformanceObserverInit* options = PerformanceObserverInit::Create();
  Vector<String> entry_type_vec;
  entry_type_vec.push_back("mark");
  options->setEntryTypes(entry_type_vec);

  observer_->observe(options, exception_state);
  EXPECT_TRUE(IsRegistered());
}

TEST_F(PerformanceObserverTest, Enqueue) {
  V8TestingScope scope;
  Initialize(scope.GetScriptState());

  ScriptValue empty_value;
  Persistent<PerformanceEntry> entry =
      PerformanceMark::Create(scope.GetScriptState(), "m", 1234, empty_value);
  EXPECT_EQ(0, NumPerformanceEntries());

  observer_->EnqueuePerformanceEntry(*entry);
  EXPECT_EQ(1, NumPerformanceEntries());
}

TEST_F(PerformanceObserverTest, Deliver) {
  V8TestingScope scope;
  Initialize(scope.GetScriptState());

  ScriptValue empty_value;
  Persistent<PerformanceEntry> entry =
      PerformanceMark::Create(scope.GetScriptState(), "m", 1234, empty_value);
  EXPECT_EQ(0, NumPerformanceEntries());

  observer_->EnqueuePerformanceEntry(*entry);
  EXPECT_EQ(1, NumPerformanceEntries());

  Deliver();
  EXPECT_EQ(0, NumPerformanceEntries());
}

TEST_F(PerformanceObserverTest, Disconnect) {
  V8TestingScope scope;
  Initialize(scope.GetScriptState());

  ScriptValue empty_value;
  Persistent<PerformanceEntry> entry =
      PerformanceMark::Create(scope.GetScriptState(), "m", 1234, empty_value);
  EXPECT_EQ(0, NumPerformanceEntries());

  observer_->EnqueuePerformanceEntry(*entry);
  EXPECT_EQ(1, NumPerformanceEntries());

  observer_->disconnect();
  EXPECT_FALSE(IsRegistered());
  EXPECT_EQ(0, NumPerformanceEntries());
}
}
