/*
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/layout/layout_block_flow.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "third_party/blink/renderer/core/editing/editing_behavior.h"
#include "third_party/blink/renderer/core/editing/editor.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/use_counter.h"
#include "third_party/blink/renderer/core/html/html_dialog_element.h"
#include "third_party/blink/renderer/core/layout/hit_test_location.h"
#include "third_party/blink/renderer/core/layout/layout_analyzer.h"
#include "third_party/blink/renderer/core/layout/layout_flow_thread.h"
#include "third_party/blink/renderer/core/layout/layout_inline.h"
#include "third_party/blink/renderer/core/layout/layout_multi_column_flow_thread.h"
#include "third_party/blink/renderer/core/layout/layout_multi_column_spanner_placeholder.h"
#include "third_party/blink/renderer/core/layout/layout_object_factory.h"
#include "third_party/blink/renderer/core/layout/layout_paged_flow_thread.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/layout/line/glyph_overflow.h"
#include "third_party/blink/renderer/core/layout/line/inline_iterator.h"
#include "third_party/blink/renderer/core/layout/line/inline_text_box.h"
#include "third_party/blink/renderer/core/layout/line/line_width.h"
#include "third_party/blink/renderer/core/layout/logical_values.h"
#include "third_party/blink/renderer/core/layout/ng/inline/ng_line_height_metrics.h"
#include "third_party/blink/renderer/core/layout/ng/layout_ng_block_flow.h"
#include "third_party/blink/renderer/core/layout/ng/legacy_layout_tree_walking.h"
#include "third_party/blink/renderer/core/layout/ng/ng_absolute_utils.h"
#include "third_party/blink/renderer/core/layout/ng/ng_box_fragment.h"
#include "third_party/blink/renderer/core/layout/ng/ng_fragmentation_utils.h"
#include "third_party/blink/renderer/core/layout/ng/ng_layout_result.h"
#include "third_party/blink/renderer/core/layout/ng/ng_physical_box_fragment.h"
#include "third_party/blink/renderer/core/layout/ng/ng_unpositioned_float.h"
#include "third_party/blink/renderer/core/layout/shapes/shape_outside_info.h"
#include "third_party/blink/renderer/core/layout/text_autosizer.h"
#include "third_party/blink/renderer/core/paint/block_flow_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/ng/ng_paint_fragment.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/paint/paint_layer_scrollable_area.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {

bool LayoutBlockFlow::can_propagate_float_into_sibling_ = false;

struct SameSizeAsLayoutBlockFlow : public LayoutBlock {
  LineBoxList line_boxes;
  void* pointers[2];
};

static_assert(sizeof(LayoutBlockFlow) == sizeof(SameSizeAsLayoutBlockFlow),
              "LayoutBlockFlow should stay small");

struct SameSizeAsMarginInfo {
  uint16_t bitfields;
  LayoutUnit margins[2];
};

static_assert(sizeof(LayoutBlockFlow::MarginValues) == sizeof(LayoutUnit[4]),
              "MarginValues should stay small");

typedef HashMap<LayoutBlockFlow*, int> LayoutPassCountMap;
static LayoutPassCountMap& GetLayoutPassCountMap() {
  DEFINE_STATIC_LOCAL(LayoutPassCountMap, map, ());
  return map;
}

// Caches all our current margin collapsing state.
class MarginInfo {
  // Collapsing flags for whether we can collapse our margins with our
  // children's margins.
  bool can_collapse_with_children_ : 1;
  bool can_collapse_margin_before_with_children_ : 1;
  bool can_collapse_margin_after_with_children_ : 1;
  bool can_collapse_margin_after_with_last_child_ : 1;

  // Whether or not we are a quirky container, i.e., do we collapse away top and
  // bottom margins in our container. Table cells and the body are the common
  // examples. We also have a custom style property for Safari RSS to deal with
  // TypePad blog articles.
  bool quirk_container_ : 1;

  // This flag tracks whether we are still looking at child margins that can all
  // collapse together at the beginning of a block. They may or may not collapse
  // with the top margin of the block (|m_canCollapseTopWithChildren| tells us
  // that), but they will always be collapsing with one another. This variable
  // can remain set to true through multiple iterations as long as we keep
  // encountering self-collapsing blocks.
  bool at_before_side_of_block_ : 1;

  // This flag is set when we know we're examining bottom margins and we know
  // we're at the bottom of the block.
  bool at_after_side_of_block_ : 1;

  // These variables are used to detect quirky margins that we need to collapse
  // away (in table cells
  // and in the body element).
  bool has_margin_before_quirk_ : 1;
  bool has_margin_after_quirk_ : 1;
  bool determined_margin_before_quirk_ : 1;

  bool discard_margin_ : 1;
  bool last_child_is_self_collapsing_block_with_clearance_ : 1;

  // These flags track the previous maximal positive and negative margins.
  LayoutUnit positive_margin_;
  LayoutUnit negative_margin_;

 public:
  MarginInfo(LayoutBlockFlow*,
             LayoutUnit before_border_padding,
             LayoutUnit after_border_padding);

  void SetAtBeforeSideOfBlock(bool b) { at_before_side_of_block_ = b; }
  void SetAtAfterSideOfBlock(bool b) { at_after_side_of_block_ = b; }
  void ClearMargin() {
    positive_margin_ = LayoutUnit();
    negative_margin_ = LayoutUnit();
  }
  void SetHasMarginBeforeQuirk(bool b) { has_margin_before_quirk_ = b; }
  void SetHasMarginAfterQuirk(bool b) { has_margin_after_quirk_ = b; }
  void SetDeterminedMarginBeforeQuirk(bool b) {
    determined_margin_before_quirk_ = b;
  }
  void SetPositiveMargin(LayoutUnit p) {
    DCHECK(!discard_margin_);
    positive_margin_ = p;
  }
  void SetNegativeMargin(LayoutUnit n) {
    DCHECK(!discard_margin_);
    negative_margin_ = n;
  }
  void SetPositiveMarginIfLarger(LayoutUnit p) {
    DCHECK(!discard_margin_);
    if (p > positive_margin_)
      positive_margin_ = p;
  }
  void SetNegativeMarginIfLarger(LayoutUnit n) {
    DCHECK(!discard_margin_);
    if (n > negative_margin_)
      negative_margin_ = n;
  }

  void SetMargin(LayoutUnit p, LayoutUnit n) {
    DCHECK(!discard_margin_);
    positive_margin_ = p;
    negative_margin_ = n;
  }
  void SetCanCollapseMarginAfterWithChildren(bool collapse) {
    can_collapse_margin_after_with_children_ = collapse;
  }
  void SetCanCollapseMarginAfterWithLastChild(bool collapse) {
    can_collapse_margin_after_with_last_child_ = collapse;
  }
  void SetDiscardMargin(bool value) { discard_margin_ = value; }

  bool AtBeforeSideOfBlock() const { return at_before_side_of_block_; }
  bool CanCollapseWithMarginBefore() const {
    return at_before_side_of_block_ &&
           can_collapse_margin_before_with_children_;
  }
  bool CanCollapseWithMarginAfter() const {
    return at_after_side_of_block_ && can_collapse_margin_after_with_children_;
  }
  bool CanCollapseMarginBeforeWithChildren() const {
    return can_collapse_margin_before_with_children_;
  }
  bool CanCollapseMarginAfterWithChildren() const {
    return can_collapse_margin_after_with_children_;
  }
  bool CanCollapseMarginAfterWithLastChild() const {
    return can_collapse_margin_after_with_last_child_;
  }
  bool QuirkContainer() const { return quirk_container_; }
  bool DeterminedMarginBeforeQuirk() const {
    return determined_margin_before_quirk_;
  }
  bool HasMarginBeforeQuirk() const { return has_margin_before_quirk_; }
  bool HasMarginAfterQuirk() const { return has_margin_after_quirk_; }
  LayoutUnit PositiveMargin() const { return positive_margin_; }
  LayoutUnit NegativeMargin() const { return negative_margin_; }
  bool DiscardMargin() const { return discard_margin_; }
  LayoutUnit Margin() const { return positive_margin_ - negative_margin_; }
  void SetLastChildIsSelfCollapsingBlockWithClearance(bool value) {
    last_child_is_self_collapsing_block_with_clearance_ = value;
  }
  bool LastChildIsSelfCollapsingBlockWithClearance() const {
    return last_child_is_self_collapsing_block_with_clearance_;
  }
};

// Some features, such as floats, margin collapsing and fragmentation, require
// some knowledge about things that happened when laying out previous block
// child siblings. Only looking at the object currently being laid out isn't
// always enough.
class BlockChildrenLayoutInfo {
 public:
  BlockChildrenLayoutInfo(LayoutBlockFlow* block_flow,
                          LayoutUnit before_edge,
                          LayoutUnit after_edge)
      : margin_info_(block_flow, before_edge, after_edge),
        previous_break_after_value_(EBreakBetween::kAuto),
        is_at_first_in_flow_child_(true) {}

  // Store multicol layout state before first layout of a block child. The child
  // may contain a column spanner. If we need to re-lay out the block child
  // because our initial logical top estimate was wrong, we need to roll back to
  // how things were before laying out the child.
  void StoreMultiColumnLayoutState(const LayoutFlowThread& flow_thread) {
    multi_column_layout_state_ = flow_thread.GetMultiColumnLayoutState();
  }
  void RollBackToInitialMultiColumnLayoutState(LayoutFlowThread& flow_thread) {
    flow_thread.RestoreMultiColumnLayoutState(multi_column_layout_state_);
  }

  const MarginInfo& GetMarginInfo() const { return margin_info_; }
  MarginInfo& GetMarginInfo() { return margin_info_; }
  LayoutUnit& PreviousFloatLogicalBottom() {
    return previous_float_logical_bottom_;
  }

  EBreakBetween PreviousBreakAfterValue() const {
    return previous_break_after_value_;
  }
  void SetPreviousBreakAfterValue(EBreakBetween value) {
    previous_break_after_value_ = value;
  }

  bool IsAtFirstInFlowChild() const { return is_at_first_in_flow_child_; }
  void ClearIsAtFirstInFlowChild() { is_at_first_in_flow_child_ = false; }

 private:
  MultiColumnLayoutState multi_column_layout_state_;
  MarginInfo margin_info_;
  LayoutUnit previous_float_logical_bottom_;
  EBreakBetween previous_break_after_value_;
  bool is_at_first_in_flow_child_;
};

LayoutBlockFlow::LayoutBlockFlow(ContainerNode* node) : LayoutBlock(node) {
  static_assert(sizeof(MarginInfo) == sizeof(SameSizeAsMarginInfo),
                "MarginInfo should stay small");
  SetChildrenInline(true);
}

#if DCHECK_IS_ON()
LayoutBlockFlow::~LayoutBlockFlow() {
  line_boxes_.AssertIsEmpty();
}
#else
LayoutBlockFlow::~LayoutBlockFlow() = default;
#endif

LayoutBlockFlow* LayoutBlockFlow::CreateAnonymous(
    Document* document,
    scoped_refptr<ComputedStyle> style) {
  LayoutBlockFlow* layout_block_flow =
      LayoutObjectFactory::CreateBlockFlow(*document, *style);
  layout_block_flow->SetDocumentForAnonymous(document);
  layout_block_flow->SetStyle(style);
  return layout_block_flow;
}

LayoutObject* LayoutBlockFlow::LayoutSpecialExcludedChild(
    bool relayout_children,
    SubtreeLayoutScope& layout_scope) {
  LayoutMultiColumnFlowThread* flow_thread = MultiColumnFlowThread();
  if (!flow_thread)
    return nullptr;
  SetLogicalTopForChild(*flow_thread, BorderBefore() + PaddingBefore());
  flow_thread->LayoutColumns(layout_scope);
  DetermineLogicalLeftPositionForChild(*flow_thread);
  return flow_thread;
}

bool LayoutBlockFlow::UpdateLogicalWidthAndColumnWidth() {
  bool relayout_children = LayoutBlock::UpdateLogicalWidthAndColumnWidth();
  if (LayoutMultiColumnFlowThread* flow_thread = MultiColumnFlowThread()) {
    if (flow_thread->NeedsNewWidth())
      return true;
  }
  return relayout_children;
}

void LayoutBlockFlow::SetBreakAtLineToAvoidWidow(int line_to_break) {
  DCHECK_GE(line_to_break, 0);
  EnsureRareData();
  DCHECK(!rare_data_->did_break_at_line_to_avoid_widow_);
  rare_data_->line_break_to_avoid_widow_ = line_to_break;
}

void LayoutBlockFlow::SetDidBreakAtLineToAvoidWidow() {
  DCHECK(!ShouldBreakAtLineToAvoidWidow());

  // This function should be called only after a break was applied to avoid
  // widows so assert |m_rareData| exists.
  DCHECK(rare_data_);

  rare_data_->did_break_at_line_to_avoid_widow_ = true;
}

void LayoutBlockFlow::ClearDidBreakAtLineToAvoidWidow() {
  if (!rare_data_)
    return;

  rare_data_->did_break_at_line_to_avoid_widow_ = false;
}

void LayoutBlockFlow::ClearShouldBreakAtLineToAvoidWidow() const {
  DCHECK(ShouldBreakAtLineToAvoidWidow());
  if (!rare_data_)
    return;

  rare_data_->line_break_to_avoid_widow_ = -1;
}

bool LayoutBlockFlow::IsSelfCollapsingBlock() const {
  if (NeedsLayout()) {
    // Sometimes we don't lay out objects in DOM order (column spanners being
    // one such relevant type of object right here). As long as the object in
    // question establishes a new formatting context, that's nothing to worry
    // about, though.
    DCHECK(CreatesNewFormattingContext());
    return false;
  }
  DCHECK_EQ(!is_self_collapsing_, !CheckIfIsSelfCollapsingBlock());
  return is_self_collapsing_;
}

bool LayoutBlockFlow::CheckIfIsSelfCollapsingBlock() const {
  // We are not self-collapsing if we
  // (a) have a non-zero height according to layout (an optimization to avoid
  //     wasting time)
  // (b) have border/padding,
  // (c) have a min-height
  // (d) have specified that one of our margins can't collapse using a CSS
  //     extension
  // (e) establish a new block formatting context.

  // The early exit must be done before we check for clean layout.
  // We should be able to give a quick answer if the box is a relayout boundary.
  // Being a relayout boundary implies a block formatting context, and also
  // our internal layout shouldn't affect our container in any way.
  if (CreatesNewFormattingContext())
    return false;

  // Placeholder elements are not laid out until the dimensions of their parent
  // text control are known, so they don't get layout until their parent has had
  // layout - this is unique in the layout tree and means when we call
  // isSelfCollapsingBlock on them we find that they still need layout.
  DCHECK(!NeedsLayout() || (GetNode() && GetNode()->IsElementNode() &&
                            ToElement(GetNode())->ShadowPseudoId() ==
                                "-webkit-input-placeholder"));

  if (LogicalHeight() > LayoutUnit() || BorderAndPaddingLogicalHeight() ||
      StyleRef().LogicalMinHeight().IsPositive() ||
      StyleRef().MarginBeforeCollapse() == EMarginCollapse::kSeparate ||
      StyleRef().MarginAfterCollapse() == EMarginCollapse::kSeparate)
    return false;

  Length logical_height_length = StyleRef().LogicalHeight();
  bool has_auto_height = logical_height_length.IsAuto();
  if (logical_height_length.IsPercentOrCalc() &&
      !GetDocument().InQuirksMode()) {
    has_auto_height = true;
    for (LayoutBlock* cb = ContainingBlock(); !cb->IsLayoutView();
         cb = cb->ContainingBlock()) {
      if (cb->StyleRef().LogicalHeight().IsFixed() || cb->IsTableCell())
        has_auto_height = false;
    }
  }

  // If the height is 0 or auto, then whether or not we are a self-collapsing
  // block depends on whether we have content that is all self-collapsing.
  // TODO(alancutter): Make this work correctly for calc lengths.
  if (has_auto_height || ((logical_height_length.IsFixed() ||
                           logical_height_length.IsPercentOrCalc()) &&
                          logical_height_length.IsZero())) {
    // Marker_container should be a self-collapsing block. Marker_container is a
    // zero height anonymous block and marker is its only child.
    if (logical_height_length.IsFixed() && logical_height_length.IsZero() &&
        IsAnonymous() && Parent() && Parent()->IsListItem()) {
      LayoutObject* first_child = FirstChild();
      if (first_child && first_child->IsListMarker() &&
          !first_child->NextSibling())
        return true;
    }

    // If the block has inline children, see if we generated any line boxes.
    // If we have any line boxes, then we can't be self-collapsing, since we
    // have content.
    if (ChildrenInline())
      return !FirstLineBox();

    // Whether or not we collapse is dependent on whether all our normal flow
    // children are also self-collapsing.
    for (LayoutBox* child = FirstChildBox(); child;
         child = child->NextSiblingBox()) {
      if (child->IsFloatingOrOutOfFlowPositioned() || child->IsColumnSpanAll())
        continue;
      if (!child->IsSelfCollapsingBlock())
        return false;
    }
    return true;
  }
  return false;
}

DISABLE_CFI_PERF
void LayoutBlockFlow::UpdateBlockLayout(bool relayout_children) {
  DCHECK(NeedsLayout());
  DCHECK(IsInlineBlockOrInlineTable() || !IsInline());

  if (RuntimeEnabledFeatures::TrackLayoutPassesPerBlockEnabled())
    IncrementLayoutPassCount();

  if (!relayout_children && SimplifiedLayout())
    return;

  LayoutAnalyzer::BlockScope analyzer(*this);
  SubtreeLayoutScope layout_scope(*this);

  LayoutUnit previous_height = LogicalHeight();
  LayoutUnit old_left = LogicalLeft();
  bool logical_width_changed = UpdateLogicalWidthAndColumnWidth();
  relayout_children |= logical_width_changed;

  TextAutosizer::LayoutScope text_autosizer_layout_scope(this, &layout_scope);

  bool pagination_state_changed = pagination_state_changed_;
  bool preferred_logical_widths_were_dirty = PreferredLogicalWidthsDirty();

  // Multiple passes might be required for column based layout.
  // The number of passes could be as high as the number of columns.
  LayoutMultiColumnFlowThread* flow_thread = MultiColumnFlowThread();
  do {
    LayoutState state(*this, logical_width_changed);
    if (pagination_state_changed_) {
      // We now need a deep layout to clean up struts after pagination, if we
      // just ceased to be paginated, or, if we just became paginated on the
      // other hand, we now need the deep layout, to insert pagination struts.
      pagination_state_changed_ = false;
      state.SetPaginationStateChanged();
    }

    LayoutChildren(relayout_children, layout_scope);

    if (!preferred_logical_widths_were_dirty && PreferredLogicalWidthsDirty()) {
      // The only thing that should dirty preferred widths at this point is the
      // addition of overflow:auto scrollbars in a descendant. To avoid a
      // potential infinite loop, run layout again with auto scrollbars frozen
      // in their current state.
      PaintLayerScrollableArea::FreezeScrollbarsScope freeze_scrollbars;
      relayout_children |= UpdateLogicalWidthAndColumnWidth();
      LayoutChildren(relayout_children, layout_scope);
    }

    if (flow_thread && !flow_thread->FinishLayout()) {
      SetChildNeedsLayout(kMarkOnlyThis);
      continue;
    }

    if (ShouldBreakAtLineToAvoidWidow()) {
      SetEverHadLayout();
      continue;
    }
    break;
  } while (true);

  LayoutState state(*this, logical_width_changed);
  if (pagination_state_changed) {
    // We still haven't laid out positioned descendants, and we need to perform
    // a deep layout on those too if pagination state changed.
    state.SetPaginationStateChanged();
  }

  // Remember the automatic logical height we got from laying out the children.
  LayoutUnit unconstrained_height = LogicalHeight();
  LayoutUnit unconstrained_client_after_edge = ClientLogicalBottom();

  // Adjust logical height to satisfy whatever computed style requires.
  UpdateLogicalHeight();

  if (!ChildrenInline())
    AddOverhangingFloatsFromChildren(unconstrained_height);

  if (LogicalHeight() != previous_height || IsDocumentElement())
    relayout_children = true;

  PositionedLayoutBehavior behavior = kDefaultLayout;
  if (old_left != LogicalLeft())
    behavior = kForcedLayoutAfterContainingBlockMoved;
  LayoutPositionedObjects(relayout_children, behavior);

  // Add overflow from children.
  ComputeOverflow(unconstrained_client_after_edge);

  descendants_with_floats_marked_for_layout_ = false;

  UpdateAfterLayout();

  if (IsHTMLDialogElement(GetNode()) && IsOutOfFlowPositioned())
    PositionDialog();

  ClearNeedsLayout();
  UpdateIsSelfCollapsing();
}

DISABLE_CFI_PERF
void LayoutBlockFlow::ResetLayout() {
  if (!FirstChild() && !IsAnonymousBlock())
    SetChildrenInline(true);
  SetContainsInlineWithOutlineAndContinuation(false);

  // Text truncation kicks in if overflow isn't visible and text-overflow isn't
  // 'clip'. If this is an anonymous block, we have to examine the parent.
  // FIXME: CSS3 says that descendants that are clipped must also know how to
  // truncate. This is insanely difficult to figure out in general (especially
  // in the middle of doing layout), so we only handle the simple case of an
  // anonymous block truncating when its parent is clipped.
  // Walk all the lines and delete our ellipsis line boxes if they exist.
  if (ChildrenInline() && ShouldTruncateOverflowingText())
    DeleteEllipsisLineBoxes();

  RebuildFloatsFromIntruding();

  // We use four values, maxTopPos, maxTopNeg, maxBottomPos, and maxBottomNeg,
  // to track our current maximal positive and negative margins. These values
  // are used when we are collapsed with adjacent blocks, so for example, if you
  // have block A and B collapsing together, then you'd take the maximal
  // positive margin from both A and B and subtract it from the maximal negative
  // margin from both A and B to get the true collapsed margin. This algorithm
  // is recursive, so when we finish layout() our block knows its current
  // maximal positive/negative values.
  //
  // Start out by setting our margin values to our current margins. Table cells
  // have no margins, so we don't fill in the values for table cells.
  if (!IsTableCell()) {
    InitMaxMarginValues();
    SetHasMarginBeforeQuirk(StyleRef().HasMarginBeforeQuirk());
    SetHasMarginAfterQuirk(StyleRef().HasMarginAfterQuirk());
  }

  if (View()->GetLayoutState()->IsPaginated()) {
    SetPaginationStrutPropagatedFromChild(LayoutUnit());
    SetFirstForcedBreakOffset(LayoutUnit());

    // Start with any applicable computed break-after and break-before values
    // for this object. During child layout, breakBefore will be joined with the
    // breakBefore value of the first in-flow child, and breakAfter will be
    // joined with the breakAfter value of the last in-flow child. This is done
    // in order to honor the requirement that a class A break point [1] may only
    // exists *between* in-flow siblings (i.e. not before the first child and
    // not after the last child).
    //
    // [1] https://drafts.csswg.org/css-break/#possible-breaks
    SetBreakBefore(LayoutBlock::BreakBefore());
    SetBreakAfter(LayoutBlock::BreakAfter());
  }
}

DISABLE_CFI_PERF
void LayoutBlockFlow::LayoutChildren(bool relayout_children,
                                     SubtreeLayoutScope& layout_scope) {
  ResetLayout();

  LayoutUnit before_edge = BorderBefore() + PaddingBefore();
  LayoutUnit after_edge = BorderAfter() + PaddingAfter();

  if (HasFlippedBlocksWritingMode())
    before_edge += ScrollbarLogicalHeight();
  else
    after_edge += ScrollbarLogicalHeight();

  SetLogicalHeight(before_edge);

  if (ChildrenInline())
    LayoutInlineChildren(relayout_children, after_edge);
  else
    LayoutBlockChildren(relayout_children, layout_scope, before_edge,
                        after_edge);

  // Expand our intrinsic height to encompass floats.
  if (LowestFloatLogicalBottom() > (LogicalHeight() - after_edge) &&
      CreatesNewFormattingContext())
    SetLogicalHeight(LowestFloatLogicalBottom() + after_edge);
}

void LayoutBlockFlow::AddOverhangingFloatsFromChildren(
    LayoutUnit unconstrained_height) {
  LayoutBlockFlow* lowest_block = nullptr;
  bool added_overhanging_floats = false;
  // One of our children's floats may have become an overhanging float for us.
  for (LayoutObject* child = LastChild(); child;
       child = child->PreviousSibling()) {
    // TODO(robhogan): We should exclude blocks that create formatting
    // contexts, not just out of flow or floating blocks.
    if (child->IsLayoutBlockFlow() &&
        !child->IsFloatingOrOutOfFlowPositioned()) {
      LayoutBlockFlow* block = ToLayoutBlockFlow(child);
      if (!block->ContainsFloats())
        continue;
      lowest_block = block;
      if (unconstrained_height <= LogicalHeight())
        break;
      LayoutUnit logical_bottom =
          block->LogicalTop() + block->LowestFloatLogicalBottom();
      if (logical_bottom <= LogicalHeight())
        break;
      AddOverhangingFloats(block, false);
      added_overhanging_floats = true;
    }
  }
  // If we have no overhanging floats we still pass a record of the lowest
  // non-overhanging float up the tree so we can enclose it if we are a
  // formatting context and allow siblings to avoid it if they have negative
  // margin and find themselves in its vicinity.
  if (!added_overhanging_floats)
    AddLowestFloatFromChildren(lowest_block);
}

void LayoutBlockFlow::AddLowestFloatFromChildren(LayoutBlockFlow* block) {
  // TODO(robhogan): Make createsNewFormattingContext an ASSERT.
  if (!block || !block->ContainsFloats() ||
      block->CreatesNewFormattingContext())
    return;

  FloatingObject* floating_object =
      block->floating_objects_->LowestFloatingObject();
  if (!floating_object || ContainsFloat(floating_object->GetLayoutObject()))
    return;

  LayoutSize offset(-block->LogicalLeft(), -block->LogicalTop());
  if (!IsHorizontalWritingMode())
    offset = offset.TransposedSize();

  if (!floating_objects_)
    CreateFloatingObjects();
  FloatingObject* new_floating_object = floating_objects_->Add(
      floating_object->CopyToNewContainer(offset, false, true));
  new_floating_object->SetIsLowestNonOverhangingFloatInChild(true);
}

DISABLE_CFI_PERF
void LayoutBlockFlow::DetermineLogicalLeftPositionForChild(LayoutBox& child) {
  LayoutUnit start_position = BorderStart() + PaddingStart();
  LayoutUnit initial_start_position = start_position;
  start_position -= LogicalLeftScrollbarWidth();
  LayoutUnit total_available_logical_width =
      BorderAndPaddingLogicalWidth() + AvailableLogicalWidth();

  LayoutUnit child_margin_start = MarginStartForChild(child);
  LayoutUnit new_position = start_position + child_margin_start;

  if (child.AvoidsFloats() && ContainsFloats()) {
    LayoutUnit position_to_avoid_floats = StartOffsetForAvoidingFloats(
        LogicalTopForChild(child), LogicalHeightForChild(child));

    // If the child has an offset from the content edge to avoid floats then use
    // that, otherwise let any negative margin pull it back over the content
    // edge or any positive margin push it out.
    // If the child is being centred then the margin calculated to do that has
    // factored in any offset required to avoid floats, so use it if necessary.
    if (StyleRef().GetTextAlign() == ETextAlign::kWebkitCenter ||
        child.StyleRef().MarginStartUsing(StyleRef()).IsAuto())
      new_position =
          std::max(new_position, position_to_avoid_floats + child_margin_start);
    else if (position_to_avoid_floats > initial_start_position)
      new_position = std::max(new_position, position_to_avoid_floats);
  }

  SetLogicalLeftForChild(child, StyleRef().IsLeftToRightDirection()
                                    ? new_position
                                    : total_available_logical_width -
                                          new_position -
                                          LogicalWidthForChild(child));
}

void LayoutBlockFlow::SetLogicalLeftForChild(LayoutBox& child,
                                             LayoutUnit logical_left) {
  LayoutPoint new_location(child.Location());
  if (IsHorizontalWritingMode()) {
    new_location.SetX(logical_left);
  } else {
    new_location.SetY(logical_left);
  }
  child.SetLocationAndUpdateOverflowControlsIfNeeded(new_location);
}

void LayoutBlockFlow::SetLogicalTopForChild(LayoutBox& child,
                                            LayoutUnit logical_top) {
  if (IsHorizontalWritingMode()) {
    child.SetY(logical_top);
  } else {
    child.SetX(logical_top);
  }
}

void LayoutBlockFlow::MarkDescendantsWithFloatsForLayoutIfNeeded(
    LayoutBlockFlow& child,
    LayoutUnit new_logical_top,
    LayoutUnit previous_float_logical_bottom) {
  // TODO(mstensho): rework the code to return early when there is no need for
  // marking, instead of this |markDescendantsWithFloats| flag.
  bool mark_descendants_with_floats = false;
  if (new_logical_top != child.LogicalTop() && !child.AvoidsFloats() &&
      child.ContainsFloats()) {
    mark_descendants_with_floats = true;
  } else if (UNLIKELY(new_logical_top.MightBeSaturated())) {
    // The logical top might be saturated for very large elements. Comparing
    // with the old logical top might then yield a false negative, as adding and
    // removing margins, borders etc. from a saturated number might yield
    // incorrect results. If this is the case, always mark for layout.
    mark_descendants_with_floats = true;
  } else if (!child.AvoidsFloats() || child.ShrinkToAvoidFloats()) {
    // If an element might be affected by the presence of floats, then always
    // mark it for layout.
    LayoutUnit lowest_float =
        std::max(previous_float_logical_bottom, LowestFloatLogicalBottom());
    if (lowest_float > new_logical_top)
      mark_descendants_with_floats = true;
  }

  if (mark_descendants_with_floats)
    child.MarkAllDescendantsWithFloatsForLayout();
}

bool LayoutBlockFlow::PositionAndLayoutOnceIfNeeded(
    LayoutBox& child,
    LayoutUnit new_logical_top,
    BlockChildrenLayoutInfo& layout_info) {
  if (LayoutFlowThread* flow_thread = FlowThreadContainingBlock())
    layout_info.RollBackToInitialMultiColumnLayoutState(*flow_thread);

  if (child.IsLayoutBlockFlow()) {
    LayoutUnit& previous_float_logical_bottom =
        layout_info.PreviousFloatLogicalBottom();
    LayoutBlockFlow& child_block_flow = ToLayoutBlockFlow(child);
    if (child_block_flow.ContainsFloats() || ContainsFloats())
      MarkDescendantsWithFloatsForLayoutIfNeeded(
          child_block_flow, new_logical_top, previous_float_logical_bottom);

    // TODO(mstensho): A writing mode root is one thing, but we should be able
    // to skip anything that establishes a new block formatting context here.
    // Their floats don't affect us.
    if (!child_block_flow.IsWritingModeRoot())
      previous_float_logical_bottom =
          std::max(previous_float_logical_bottom,
                   child_block_flow.LogicalTop() +
                       child_block_flow.LowestFloatLogicalBottom());
  }

  LayoutUnit old_logical_top = LogicalTopForChild(child);
  SetLogicalTopForChild(child, new_logical_top);

  SubtreeLayoutScope layout_scope(child);
  if (!child.NeedsLayout()) {
    if (new_logical_top != old_logical_top && child.ShrinkToAvoidFloats()) {
      // The child's width is affected by adjacent floats. When the child shifts
      // to clear an item, its width can change (because it has more available
      // width).
      layout_scope.SetChildNeedsLayout(&child);
    } else {
      MarkChildForPaginationRelayoutIfNeeded(child, layout_scope);
    }
  }

  bool needed_layout = child.NeedsLayout();
  if (needed_layout)
    child.UpdateLayout();
  if (View()->GetLayoutState()->IsPaginated())
    UpdateFragmentationInfoForChild(child);
  return needed_layout;
}

void LayoutBlockFlow::InsertForcedBreakBeforeChildIfNeeded(
    LayoutBox& child,
    BlockChildrenLayoutInfo& layout_info) {
  if (layout_info.IsAtFirstInFlowChild()) {
    // There's no class A break point before the first child (only *between*
    // siblings), so steal its break value and join it with what we already have
    // here.
    SetBreakBefore(
        JoinFragmentainerBreakValues(BreakBefore(), child.BreakBefore()));
    return;
  }

  // Figure out if a forced break should be inserted in front of the child. If
  // we insert a forced break, the margins on this child may not collapse with
  // those preceding the break.
  EBreakBetween class_a_break_point_value =
      child.ClassABreakPointValue(layout_info.PreviousBreakAfterValue());
  if (IsForcedFragmentainerBreakValue(class_a_break_point_value)) {
    layout_info.GetMarginInfo().ClearMargin();
    LayoutUnit old_logical_top = LogicalHeight();
    LayoutUnit new_logical_top =
        ApplyForcedBreak(old_logical_top, class_a_break_point_value);
    SetLogicalHeight(new_logical_top);
    LayoutUnit pagination_strut = new_logical_top - old_logical_top;
    child.SetPaginationStrut(pagination_strut);
  }
}

void LayoutBlockFlow::LayoutBlockChild(LayoutBox& child,
                                       BlockChildrenLayoutInfo& layout_info) {
  MarginInfo& margin_info = layout_info.GetMarginInfo();
  LayoutBlockFlow* child_layout_block_flow =
      child.IsLayoutBlockFlow() ? ToLayoutBlockFlow(&child) : nullptr;
  LayoutUnit old_pos_margin_before = MaxPositiveMarginBefore();
  LayoutUnit old_neg_margin_before = MaxNegativeMarginBefore();

  // The child is a normal flow object. Compute the margins we will use for
  // collapsing now.
  child.ComputeAndSetBlockDirectionMargins(this);

  // Try to guess our correct logical top position. In most cases this guess
  // will be correct. Only if we're wrong (when we compute the real logical top
  // position) will we have to potentially relayout.
  LayoutUnit estimate_without_pagination;
  LayoutUnit logical_top_estimate = EstimateLogicalTopPosition(
      child, layout_info, estimate_without_pagination);

  LayoutRect old_rect = child.FrameRect();

  if (LayoutFlowThread* flow_thread = FlowThreadContainingBlock())
    layout_info.StoreMultiColumnLayoutState(*flow_thread);

  // Use the estimated block position and lay out the child if needed. After
  // child layout, when we have enough information to perform proper margin
  // collapsing, float clearing and pagination, we may have to reposition and
  // lay out again if the estimate was wrong.
  bool child_needed_layout =
      PositionAndLayoutOnceIfNeeded(child, logical_top_estimate, layout_info);

  // Cache if we are at the top of the block right now.
  bool at_before_side_of_block = margin_info.AtBeforeSideOfBlock();
  bool child_is_self_collapsing = child.IsSelfCollapsingBlock();
  bool child_discard_margin_before = MustDiscardMarginBeforeForChild(child);
  bool child_discard_margin_after = MustDiscardMarginAfterForChild(child);
  bool paginated = View()->GetLayoutState()->IsPaginated();

  // If there should be a forced break before the child, we need to insert it
  // before attempting to collapse margins or apply clearance.
  if (paginated) {
    // We will now insert the strut needed by any forced break. After this
    // operation, we will have calculated the offset where we can apply margin
    // collapsing and clearance. After having applied those things, we'll be at
    // the position where we can honor requirements of unbreakable content,
    // which may extend the strut further.
    child.ResetPaginationStrut();
    InsertForcedBreakBeforeChildIfNeeded(child, layout_info);
  }

  // Now determine the correct ypos based off examination of collapsing margin
  // values.
  LayoutUnit logical_top_before_clear =
      CollapseMargins(child, layout_info, child_is_self_collapsing,
                      child_discard_margin_before, child_discard_margin_after);

  // Now check for clear.
  bool child_discard_margin =
      child_discard_margin_before || child_discard_margin_after;
  LayoutUnit new_logical_top = ClearFloatsIfNeeded(
      child, margin_info, old_pos_margin_before, old_neg_margin_before,
      logical_top_before_clear, child_is_self_collapsing, child_discard_margin);

  // If there's a forced break in front of this child, its final position has
  // already been determined. Otherwise, see if there are other reasons for
  // breaking before it (break-inside:avoid, or not enough space for the first
  // piece of child content to fit in the current fragmentainer), and adjust the
  // position accordingly.
  if (paginated) {
    if (estimate_without_pagination != new_logical_top) {
      // We got a new position due to clearance or margin collapsing. Before we
      // attempt to paginate (which may result in the position changing again),
      // let's try again at the new position (since a new position may result in
      // a new logical height).
      PositionAndLayoutOnceIfNeeded(child, new_logical_top, layout_info);
    }

    // We have now applied forced breaks, margin collapsing and clearance, and
    // we're at the position where we can honor requirements of unbreakable
    // content.
    new_logical_top = AdjustBlockChildForPagination(
        new_logical_top, child, layout_info,
        at_before_side_of_block && logical_top_before_clear == new_logical_top);
  }

  // Clearance, margin collapsing or pagination may have given us a new logical
  // top, in which case we may have to reposition and possibly relayout as well.
  // If we determined during child layout that we need to insert a break to
  // honor widows, we also need to relayout.
  if (new_logical_top != logical_top_estimate || child.NeedsLayout() ||
      (paginated && child_layout_block_flow &&
       child_layout_block_flow->ShouldBreakAtLineToAvoidWidow())) {
    PositionAndLayoutOnceIfNeeded(child, new_logical_top, layout_info);
  }

  // If we previously encountered a self-collapsing sibling of this child that
  // had clearance then we set this bit to ensure we would not collapse the
  // child's margins, and those of any subsequent self-collapsing siblings, with
  // our parent. If this child is not self-collapsing then it can collapse its
  // margins with the parent so reset the bit.
  if (!margin_info.CanCollapseMarginAfterWithLastChild() &&
      !child_is_self_collapsing)
    margin_info.SetCanCollapseMarginAfterWithLastChild(true);

  // We are no longer at the top of the block if we encounter a non-empty child.
  // This has to be done after checking for clear, so that margins can be reset
  // if a clear occurred.
  if (margin_info.AtBeforeSideOfBlock() && !child_is_self_collapsing)
    margin_info.SetAtBeforeSideOfBlock(false);

  // Now place the child in the correct left position
  DetermineLogicalLeftPositionForChild(child);

  LayoutSize child_offset = child.Location() - old_rect.Location();

  // Update our height now that the child has been placed in the correct
  // position.
  SetLogicalHeight(LogicalHeight() + LogicalHeightForChild(child));
  if (MustSeparateMarginAfterForChild(child)) {
    SetLogicalHeight(LogicalHeight() + MarginAfterForChild(child));
    margin_info.ClearMargin();
  }
  // If the child has overhanging floats that intrude into following siblings
  // (or possibly out of this block), then the parent gets notified of the
  // floats now.
  if (child_layout_block_flow)
    AddOverhangingFloats(child_layout_block_flow, !child_needed_layout);

  // If the child moved, we have to invalidate its paint as well as any
  // floating/positioned descendants. An exception is if we need a layout.
  // In this case, we know we're going to invalidate our paint (and the child)
  // anyway.
  if (!SelfNeedsLayout() && (child_offset.Width() || child_offset.Height()) &&
      child.IsLayoutBlockFlow())
    BlockFlowPaintInvalidator(ToLayoutBlockFlow(child))
        .InvalidatePaintForOverhangingFloats();

  if (paginated) {
    // Keep track of the break-after value of the child, so that it can be
    // joined with the break-before value of the next in-flow object at the next
    // class A break point.
    layout_info.SetPreviousBreakAfterValue(child.BreakAfter());

    PaginatedContentWasLaidOut(child.LogicalBottom());

    if (child_layout_block_flow) {
      // If a forced break was inserted inside the child, translate and
      // propagate the offset to this object.
      if (LayoutUnit offset = child_layout_block_flow->FirstForcedBreakOffset())
        SetFirstForcedBreakOffset(offset + new_logical_top);
    }
  }

  if (child.IsLayoutMultiColumnSpannerPlaceholder()) {
    // The actual column-span:all element is positioned by this placeholder
    // child.
    PositionSpannerDescendant(ToLayoutMultiColumnSpannerPlaceholder(child));
  }
}

LayoutUnit LayoutBlockFlow::AdjustBlockChildForPagination(
    LayoutUnit logical_top,
    LayoutBox& child,
    BlockChildrenLayoutInfo& layout_info,
    bool at_before_side_of_block) {
  LayoutBlockFlow* child_block_flow =
      child.IsLayoutBlockFlow() ? ToLayoutBlockFlow(&child) : nullptr;

  // See if we need a soft (unforced) break in front of this child, and set the
  // pagination strut in that case. An unforced break may come from two sources:
  // 1. The first piece of content inside the child doesn't fit in the current
  //    page or column
  // 2. The child itself has breaking restrictions (break-inside:avoid, replaced
  //    content, etc.) and doesn't fully fit in the current page or column.
  //
  // No matter which source, if we need to insert a strut, it should always take
  // us to the exact top of a page or column further ahead, or be zero.

  // The first piece of content inside the child may have set a strut during
  // layout. Currently, only block flows support strut propagation, but this may
  // (and should) change in the future. See crbug.com/539873
  LayoutUnit strut_from_content =
      child_block_flow ? child_block_flow->PaginationStrutPropagatedFromChild()
                       : LayoutUnit();
  LayoutUnit logical_top_with_content_strut = logical_top + strut_from_content;

  LayoutUnit logical_top_after_unsplittable =
      AdjustForUnsplittableChild(child, logical_top);

  // Pick the largest offset. Tall unsplittable content may take us to a page or
  // column further ahead than the next one.
  LayoutUnit logical_top_after_pagination =
      std::max(logical_top_with_content_strut, logical_top_after_unsplittable);
  LayoutUnit new_logical_top = logical_top;

  // Forced breaks may already have caused a strut, and this needs to be added
  // together with any strut detected here in this method.
  LayoutUnit previous_strut = child.PaginationStrut();

  if (LayoutUnit pagination_strut =
          logical_top_after_pagination - logical_top + previous_strut) {
    DCHECK_GT(pagination_strut, 0);
    // If we're not at the first in-flow child, there's a class A break point
    // before the child. If we *are* at the first in-flow child, but the child
    // isn't flush with the content edge of its container, due to e.g.
    // clearance, there's a class C break point before the child. Otherwise we
    // should propagate the strut to our parent block, and attempt to break
    // there instead. See https://drafts.csswg.org/css-break/#possible-breaks
    bool can_break =
        !layout_info.IsAtFirstInFlowChild() || !at_before_side_of_block;
    if (!can_break && child.GetPaginationBreakability() == kForbidBreaks &&
        !AllowsPaginationStrut()) {
      // The child is monolithic content, e.g. an image. It is truly
      // unsplittable. Breaking inside it would be bad. Since this block doesn't
      // allow pagination struts to be propagated to it, we're left to handle it
      // on our own right here. Break before the child, even if we're currently
      // at the block start (i.e. there's no class A or C break point here).
      can_break = true;
    }
    if (can_break) {
      child.SetPaginationStrut(pagination_strut);
      // |previousStrut| was already baked into the logical top, so don't add
      // it again.
      new_logical_top += pagination_strut - previous_strut;
    } else {
      // No valid break point here. Propagate the strut from the child to this
      // block, but only if the block allows it. If the block doesn't allow it,
      // we'll just ignore the strut and carry on, without breaking. This
      // happens e.g. when a tall break-inside:avoid object with a top margin is
      // the first in-flow child in the fragmentation context.
      if (AllowsPaginationStrut()) {
        pagination_strut += logical_top;
        SetPaginationStrutPropagatedFromChild(pagination_strut);
        if (child_block_flow)
          child_block_flow->SetPaginationStrutPropagatedFromChild(LayoutUnit());
      }
      child.ResetPaginationStrut();
    }
  }

  // Similar to how we apply clearance. Go ahead and boost height() to be the
  // place where we're going to position the child.
  SetLogicalHeight(LogicalHeight() + (new_logical_top - logical_top));

  // Return the final adjusted logical top.
  return new_logical_top;
}

LayoutUnit LayoutBlockFlow::AdjustFloatLogicalTopForPagination(
    LayoutBox& child,
    LayoutUnit logical_top_margin_edge) {
  // The first piece of content inside the child may have set a strut during
  // layout.
  LayoutUnit strut;
  if (child.IsLayoutBlockFlow())
    strut = ToLayoutBlockFlow(child).PaginationStrutPropagatedFromChild();

  LayoutUnit margin_before = MarginBeforeForChild(child);
  if (margin_before > LayoutUnit()) {
    // Avoid breaking inside the top margin of a float.
    if (strut) {
      // If we already had decided to break, just add the margin. The strut so
      // far only accounts for pushing the top border edge to the next
      // fragmentainer. We need to push the margin over as well, because
      // there's no break opportunity between margin and border.
      strut += margin_before;
    } else {
      // Even if we didn't break before the border box to the next
      // fragmentainer, we need to check if we can fit the margin before it.
      if (IsPageLogicalHeightKnown()) {
        LayoutUnit remaining_space = PageRemainingLogicalHeightForOffset(
            logical_top_margin_edge, kAssociateWithLatterPage);
        if (remaining_space <= margin_before) {
          strut += CalculatePaginationStrutToFitContent(logical_top_margin_edge,
                                                        margin_before);
        }
      }
    }
  }
  if (!strut) {
    // If we are unsplittable and don't fit, move to the next page or column
    // if that helps the situation.
    LayoutUnit new_logical_top_margin_edge =
        AdjustForUnsplittableChild(child, logical_top_margin_edge);
    strut = new_logical_top_margin_edge - logical_top_margin_edge;
  }

  child.SetPaginationStrut(strut);
  return logical_top_margin_edge + strut;
}

static bool ShouldSetStrutOnBlock(const LayoutBlockFlow& block,
                                  const RootInlineBox& line_box,
                                  LayoutUnit line_logical_offset,
                                  int line_index,
                                  LayoutUnit page_logical_height) {
  if (line_box == block.FirstRootBox()) {
    // This is the first line in the block. We can take the whole block with us
    // to the next page or column, rather than keeping a content-less portion of
    // it in the previous one. Only do this if the line is flush with the
    // content edge of the block, though. If it isn't, it means that the line
    // was pushed downwards by preceding floats that didn't fit beside the line,
    // and we don't want to move all that, since it has already been established
    // that it fits nicely where it is. In this case we have a class "C" break
    // point [1] in front of this line.
    //
    // [1] https://drafts.csswg.org/css-break/#possible-breaks
    if (line_logical_offset > block.BorderAndPaddingBefore())
      return false;

    LayoutUnit line_height =
        line_box.LineBottomWithLeading() - line_box.LineTopWithLeading();
    LayoutUnit total_logical_height =
        line_height + line_logical_offset.ClampNegativeToZero();
    // It's rather pointless to break before the block if the current line isn't
    // going to fit in the same column or page, so check that as well.
    if (total_logical_height > page_logical_height)
      return false;
  } else {
    if (line_index > block.StyleRef().Orphans())
      return false;

    // Not enough orphans here. Push the entire block to the next column / page
    // as an attempt to better satisfy the orphans requirement.
    //
    // Note that we should ideally check if the first line in the block is flush
    // with the content edge of the block here, because if it isn't, we should
    // break at the class "C" break point in front of the first line, rather
    // than before the entire block.
  }
  return block.AllowsPaginationStrut();
}

void LayoutBlockFlow::AdjustLinePositionForPagination(RootInlineBox& line_box,
                                                      LayoutUnit& delta) {
  // TODO(mstensho): Pay attention to line overflow. It should be painted in the
  // same column as the rest of the line, possibly overflowing the column. We
  // currently only allow overflow above the first column. We clip at all other
  // column boundaries, and that's how it has to be for now. The paint we have
  // to do when a column has overflow has to be special.
  // We need to exclude content that paints in a previous column (and content
  // that paints in the following column).
  //
  // FIXME: Another problem with simply moving lines is that the available line
  // width may change (because of floats). Technically if the location we move
  // the line to has a different line width than our old position, then we need
  // to dirty the line and all following lines.
  LayoutUnit logical_offset = line_box.LineTopWithLeading();
  LayoutUnit line_height = line_box.LineBottomWithLeading() - logical_offset;
  logical_offset += delta;
  line_box.SetPaginationStrut(LayoutUnit());
  line_box.SetIsFirstAfterPageBreak(false);
  LayoutState* layout_state = View()->GetLayoutState();
  if (!layout_state->IsPaginated())
    return;
  if (!IsPageLogicalHeightKnown())
    return;
  LayoutUnit page_logical_height = PageLogicalHeightForOffset(logical_offset);
  LayoutUnit remaining_logical_height = PageRemainingLogicalHeightForOffset(
      logical_offset, kAssociateWithLatterPage);
  int line_index = LineCount(&line_box);
  if (remaining_logical_height < line_height ||
      (ShouldBreakAtLineToAvoidWidow() &&
       LineBreakToAvoidWidow() == line_index)) {
    LayoutUnit pagination_strut =
        CalculatePaginationStrutToFitContent(logical_offset, line_height);
    LayoutUnit new_logical_offset = logical_offset + pagination_strut;
    // Moving to a different page or column may mean that its height is
    // different.
    page_logical_height = PageLogicalHeightForOffset(new_logical_offset);
    if (line_height > page_logical_height) {
      // Too tall to fit in one page / column. Give up. Don't push to the next
      // page / column.
      // TODO(mstensho): Get rid of this. This is just utter weirdness, but the
      // other browsers also do something slightly similar, although in much
      // more specific cases than we do here, and printing Google Docs depends
      // on it.
      PaginatedContentWasLaidOut(logical_offset + line_height);
      return;
    }

    // We need to insert a break now, either because there's no room for the
    // line in the current column / page, or because we have determined that we
    // need a break to satisfy widow requirements.
    if (ShouldBreakAtLineToAvoidWidow() &&
        LineBreakToAvoidWidow() == line_index) {
      ClearShouldBreakAtLineToAvoidWidow();
      SetDidBreakAtLineToAvoidWidow();
    }
    if (ShouldSetStrutOnBlock(*this, line_box, logical_offset, line_index,
                              page_logical_height)) {
      // Note that when setting the strut on a block, it may be propagated to
      // parent blocks later on, if a block's logical top is flush with that of
      // its parent. We don't want content-less portions (struts) at the
      // beginning of a block before a break, if it can be avoided. After all,
      // that's the reason for setting struts on blocks and not lines in the
      // first place.
      SetPaginationStrutPropagatedFromChild(pagination_strut + logical_offset);
    } else {
      delta += pagination_strut;
      line_box.SetPaginationStrut(pagination_strut);
      line_box.SetIsFirstAfterPageBreak(true);
    }
    PaginatedContentWasLaidOut(new_logical_offset + line_height);
    return;
  }

  LayoutUnit strut_to_propagate;
  if (remaining_logical_height == page_logical_height) {
    // We're at the very top of a page or column.
    if (line_box != FirstRootBox())
      line_box.SetIsFirstAfterPageBreak(true);
    // If this is the first line in the block, and the block has a top border or
    // padding, we may want to set a strut on the block, so that everything ends
    // up in the next column or page. Setting a strut on the block is also
    // important when it comes to satisfying orphan requirements.
    if (ShouldSetStrutOnBlock(*this, line_box, logical_offset, line_index,
                              page_logical_height)) {
      DCHECK(!IsTableCell());
      strut_to_propagate =
          logical_offset + layout_state->HeightOffsetForTableHeaders();
    } else if (LayoutUnit pagination_strut =
                   layout_state->HeightOffsetForTableHeaders()) {
      delta += pagination_strut;
      line_box.SetPaginationStrut(pagination_strut);
    }
  } else if (line_box == FirstRootBox() && AllowsPaginationStrut()) {
    // This is the first line in the block. The block may still start in the
    // previous column or page, and if that's the case, attempt to pull it over
    // to where this line is, so that we don't split the top border or padding.
    LayoutUnit strut = remaining_logical_height + logical_offset +
                       layout_state->HeightOffsetForTableHeaders() -
                       page_logical_height;
    if (strut > LayoutUnit()) {
      // The block starts in a previous column or page. Set a strut on the block
      // if there's room for the top border, padding and the line in one column
      // or page.
      if (logical_offset + line_height <= page_logical_height)
        strut_to_propagate = strut;
    }
  }

  // If we found that some preceding content (lines, border and padding) belongs
  // together with this line, we should pull the entire block with us to the
  // fragmentainer we're currently in. We need to avoid this when the block
  // precedes the first fragmentainer, though. We shouldn't fragment content
  // there, but rather let it appear in the overflow area before the first
  // fragmentainer.
  if (strut_to_propagate && OffsetFromLogicalTopOfFirstPage() > LayoutUnit())
    SetPaginationStrutPropagatedFromChild(strut_to_propagate);

  PaginatedContentWasLaidOut(logical_offset + line_height);
}

LayoutUnit LayoutBlockFlow::AdjustForUnsplittableChild(
    LayoutBox& child,
    LayoutUnit logical_offset) const {
  if (child.GetPaginationBreakability() == kAllowAnyBreaks)
    return logical_offset;
  LayoutUnit child_logical_height = LogicalHeightForChild(child);
  // Floats' margins do not collapse with page or column boundaries.
  if (child.IsFloating())
    child_logical_height +=
        MarginBeforeForChild(child) + MarginAfterForChild(child);
  if (!IsPageLogicalHeightKnown())
    return logical_offset;
  LayoutUnit remaining_logical_height = PageRemainingLogicalHeightForOffset(
      logical_offset, kAssociateWithLatterPage);
  if (remaining_logical_height >= child_logical_height)
    return logical_offset;  // It fits fine where it is. No need to break.
  LayoutUnit pagination_strut = CalculatePaginationStrutToFitContent(
      logical_offset, child_logical_height);
  if (pagination_strut == remaining_logical_height &&
      remaining_logical_height == PageLogicalHeightForOffset(logical_offset)) {
    // Don't break if we were at the top of a page, and we failed to fit the
    // content completely. No point in leaving a page completely blank.
    return logical_offset;
  }

  if (child.IsLayoutBlockFlow()) {
    // If there's a forced break inside this object, figure out if we can fit
    // everything before that forced break in the current fragmentainer. If it
    // fits, we don't need to insert a break before the child.
    const LayoutBlockFlow& block_child = ToLayoutBlockFlow(child);
    if (LayoutUnit first_break_offset = block_child.FirstForcedBreakOffset()) {
      if (remaining_logical_height >= first_break_offset)
        return logical_offset;
    }
  }

  return logical_offset + pagination_strut;
}

DISABLE_CFI_PERF
void LayoutBlockFlow::RebuildFloatsFromIntruding() {
  if (floating_objects_)
    floating_objects_->SetHorizontalWritingMode(IsHorizontalWritingMode());

  HashSet<LayoutBox*> old_intruding_float_set;
  if (!ChildrenInline() && floating_objects_) {
    const FloatingObjectSet& floating_object_set = floating_objects_->Set();
    FloatingObjectSetIterator end = floating_object_set.end();
    for (FloatingObjectSetIterator it = floating_object_set.begin(); it != end;
         ++it) {
      const FloatingObject& floating_object = *it->get();
      if (!floating_object.IsDescendant())
        old_intruding_float_set.insert(floating_object.GetLayoutObject());
    }
  }

  // Inline blocks are covered by the isAtomicInlineLevel() check in the
  // avoidFloats method.
  if (AvoidsFloats() || IsDocumentElement() || IsLayoutView() ||
      IsFloatingOrOutOfFlowPositioned() || IsTableCell()) {
    if (floating_objects_) {
      floating_objects_->Clear();
    }
    if (!old_intruding_float_set.IsEmpty())
      MarkAllDescendantsWithFloatsForLayout();
    return;
  }

  LayoutBoxToFloatInfoMap float_map;

  if (floating_objects_) {
    if (ChildrenInline())
      floating_objects_->MoveAllToFloatInfoMap(float_map);
    else
      floating_objects_->Clear();
  }

  // We should not process floats if the parent node is not a LayoutBlockFlow.
  // Otherwise, we will add floats in an invalid context. This will cause a
  // crash arising from a bad cast on the parent.
  // See <rdar://problem/8049753>, where float property is applied on a text
  // node in a SVG.
  if (!Parent() || !Parent()->IsLayoutBlockFlow())
    return;

  // Attempt to locate a previous sibling with overhanging floats. We skip any
  // elements that may have shifted to avoid floats, and any objects whose
  // floats cannot interact with objects outside it (i.e. objects that create a
  // new block formatting context).
  LayoutBlockFlow* parent_block_flow = ToLayoutBlockFlow(Parent());
  bool sibling_float_may_intrude = false;
  LayoutObject* prev = PreviousSibling();
  while (prev && (!prev->IsBox() || !prev->IsLayoutBlock() ||
                  ToLayoutBlock(prev)->AvoidsFloats() ||
                  ToLayoutBlock(prev)->CreatesNewFormattingContext())) {
    if (prev->IsFloating())
      sibling_float_may_intrude = true;
    prev = prev->PreviousSibling();
  }

  // First add in floats from the parent. Self-collapsing blocks let their
  // parent track any floats that intrude into them (as opposed to floats they
  // contain themselves) so check for those here too. If margin collapsing has
  // moved us up past the top a previous sibling then we need to check for
  // floats from the parent too.
  bool parent_floats_may_intrude =
      !sibling_float_may_intrude &&
      (!prev || ToLayoutBlockFlow(prev)->IsSelfCollapsingBlock() ||
       ToLayoutBlock(prev)->LogicalTop() > LogicalTop()) &&
      parent_block_flow->LowestFloatLogicalBottom() > LogicalTop();
  if (sibling_float_may_intrude || parent_floats_may_intrude)
    AddIntrudingFloats(parent_block_flow,
                       parent_block_flow->LogicalLeftOffsetForContent(),
                       LogicalTop());

  // Add overhanging floats from the previous LayoutBlockFlow, but only if it
  // has a float that intrudes into our space.
  if (prev) {
    LayoutBlockFlow* previous_block_flow = ToLayoutBlockFlow(prev);
    if (LogicalTop() < previous_block_flow->LogicalTop() +
                           previous_block_flow->LowestFloatLogicalBottom())
      AddIntrudingFloats(previous_block_flow, LayoutUnit(),
                         LogicalTop() - previous_block_flow->LogicalTop());
  }

  if (ChildrenInline()) {
    LayoutUnit change_logical_top = LayoutUnit::Max();
    LayoutUnit change_logical_bottom = LayoutUnit::Min();
    if (floating_objects_) {
      const FloatingObjectSet& floating_object_set = floating_objects_->Set();
      FloatingObjectSetIterator end = floating_object_set.end();
      for (FloatingObjectSetIterator it = floating_object_set.begin();
           it != end; ++it) {
        const FloatingObject& floating_object = *it->get();
        FloatingObject* old_floating_object =
            float_map.at(floating_object.GetLayoutObject());
        LayoutUnit logical_bottom = LogicalBottomForFloat(floating_object);
        if (old_floating_object) {
          LayoutUnit old_logical_bottom =
              LogicalBottomForFloat(*old_floating_object);
          if (LogicalWidthForFloat(floating_object) !=
                  LogicalWidthForFloat(*old_floating_object) ||
              LogicalLeftForFloat(floating_object) !=
                  LogicalLeftForFloat(*old_floating_object)) {
            change_logical_top = LayoutUnit();
            change_logical_bottom =
                std::max(change_logical_bottom,
                         std::max(logical_bottom, old_logical_bottom));
          } else {
            if (logical_bottom != old_logical_bottom) {
              change_logical_top =
                  std::min(change_logical_top,
                           std::min(logical_bottom, old_logical_bottom));
              change_logical_bottom =
                  std::max(change_logical_bottom,
                           std::max(logical_bottom, old_logical_bottom));
            }
            LayoutUnit logical_top = LogicalTopForFloat(floating_object);
            LayoutUnit old_logical_top =
                LogicalTopForFloat(*old_floating_object);
            if (logical_top != old_logical_top) {
              change_logical_top = std::min(
                  change_logical_top, std::min(logical_top, old_logical_top));
              change_logical_bottom =
                  std::max(change_logical_bottom,
                           std::max(logical_top, old_logical_top));
            }
          }

          if (old_floating_object->OriginatingLine() && !SelfNeedsLayout()) {
            DCHECK(old_floating_object->OriginatingLine()
                       ->GetLineLayoutItem()
                       .IsEqual(this));
            old_floating_object->OriginatingLine()->MarkDirty();
          }

          float_map.erase(floating_object.GetLayoutObject());
        } else {
          change_logical_top = LayoutUnit();
          change_logical_bottom =
              std::max(change_logical_bottom, logical_bottom);
        }
      }
    }

    LayoutBoxToFloatInfoMap::iterator end = float_map.end();
    for (LayoutBoxToFloatInfoMap::iterator it = float_map.begin(); it != end;
         ++it) {
      std::unique_ptr<FloatingObject>& floating_object = it->value;
      if (!floating_object->IsDescendant()) {
        change_logical_top = LayoutUnit();
        change_logical_bottom = std::max(
            change_logical_bottom, LogicalBottomForFloat(*floating_object));
      }
    }

    MarkLinesDirtyInBlockRange(change_logical_top, change_logical_bottom);
  } else if (!old_intruding_float_set.IsEmpty()) {
    // If there are previously intruding floats that no longer intrude, then
    // children with floats should also get layout because they might need their
    // floating object lists cleared.
    if (floating_objects_->Set().size() < old_intruding_float_set.size()) {
      MarkAllDescendantsWithFloatsForLayout();
    } else {
      const FloatingObjectSet& floating_object_set = floating_objects_->Set();
      FloatingObjectSetIterator end = floating_object_set.end();
      for (FloatingObjectSetIterator it = floating_object_set.begin();
           it != end && !old_intruding_float_set.IsEmpty(); ++it)
        old_intruding_float_set.erase((*it)->GetLayoutObject());
      if (!old_intruding_float_set.IsEmpty())
        MarkAllDescendantsWithFloatsForLayout();
    }
  }
}

void LayoutBlockFlow::LayoutBlockChildren(bool relayout_children,
                                          SubtreeLayoutScope& layout_scope,
                                          LayoutUnit before_edge,
                                          LayoutUnit after_edge) {
  DirtyForLayoutFromPercentageHeightDescendants(layout_scope);

  BlockChildrenLayoutInfo layout_info(this, before_edge, after_edge);
  MarginInfo& margin_info = layout_info.GetMarginInfo();

  // Fieldsets need to find their legend and position it inside the border of
  // the object.
  // The legend then gets skipped during normal layout. The same is true for
  // ruby text.
  // It doesn't get included in the normal layout process but is instead skipped
  LayoutObject* child_to_exclude =
      LayoutSpecialExcludedChild(relayout_children, layout_scope);

  // TODO(foolip): Speculative CHECKs to crash if any non-LayoutBox
  // children ever appear, the childrenInline() check at the call site
  // should make this impossible. crbug.com/632848
  LayoutObject* first_child = FirstChild();
  CHECK(!first_child || first_child->IsBox());
  LayoutBox* next = ToLayoutBox(first_child);
  LayoutBox* last_normal_flow_child = nullptr;

  while (next) {
    LayoutBox* child = next;
    LayoutObject* next_sibling = child->NextSibling();
    CHECK(!next_sibling || next_sibling->IsBox());
    next = ToLayoutBox(next_sibling);

    child->SetShouldCheckForPaintInvalidation();

    if (child_to_exclude == child)
      continue;  // Skip this child, since it will be positioned by the
                 // specialized subclass (fieldsets and ruby runs).

    UpdateBlockChildDirtyBitsBeforeLayout(relayout_children, *child);

    if (child->IsOutOfFlowPositioned()) {
      child->ContainingBlock()->InsertPositionedObject(child);
      AdjustPositionedBlock(*child, layout_info);
      continue;
    }
    if (child->IsFloating()) {
      InsertFloatingObject(*child);
      AdjustFloatingBlock(margin_info);
      continue;
    }
    if (child->IsColumnSpanAll()) {
      // This is not the containing block of the spanner. The spanner's
      // placeholder will lay it out in due course. For now we just need to
      // consult our flow thread, so that the columns (if any) preceding and
      // following the spanner are laid out correctly. But first we apply the
      // pending margin, so that it's taken into consideration and doesn't end
      // up on the other side of the spanner.
      SetLogicalHeight(LogicalHeight() + margin_info.Margin());
      margin_info.ClearMargin();

      child->SpannerPlaceholder()->FlowThread()->SkipColumnSpanner(
          child, OffsetFromLogicalTopOfFirstPage() + LogicalHeight());
      continue;
    }

    // Lay out the child.
    LayoutBlockChild(*child, layout_info);
    layout_info.ClearIsAtFirstInFlowChild();
    last_normal_flow_child = child;
  }

  // Now do the handling of the bottom of the block, adding in our bottom
  // border/padding and determining the correct collapsed bottom margin
  // information.
  HandleAfterSideOfBlock(last_normal_flow_child, before_edge, after_edge,
                         margin_info);
}

// Our MarginInfo state used when laying out block children.
MarginInfo::MarginInfo(LayoutBlockFlow* block_flow,
                       LayoutUnit before_border_padding,
                       LayoutUnit after_border_padding)
    : can_collapse_margin_after_with_last_child_(true),
      at_before_side_of_block_(true),
      at_after_side_of_block_(false),
      has_margin_before_quirk_(false),
      has_margin_after_quirk_(false),
      determined_margin_before_quirk_(false),
      discard_margin_(false),
      last_child_is_self_collapsing_block_with_clearance_(false) {
  const ComputedStyle& block_style = block_flow->StyleRef();
  DCHECK(block_flow->IsLayoutView() || block_flow->Parent());
  can_collapse_with_children_ = !block_flow->CreatesNewFormattingContext() &&
                                !block_flow->IsLayoutFlowThread() &&
                                !block_flow->IsLayoutView();

  can_collapse_margin_before_with_children_ =
      can_collapse_with_children_ && !before_border_padding &&
      block_style.MarginBeforeCollapse() != EMarginCollapse::kSeparate;

  // If any height other than auto is specified in CSS, then we don't collapse
  // our bottom margins with our children's margins. To do otherwise would be to
  // risk odd visual effects when the children overflow out of the parent block
  // and yet still collapse with it. We also don't collapse if we have any
  // bottom border/padding.
  can_collapse_margin_after_with_children_ =
      can_collapse_with_children_ && !after_border_padding &&
      (block_style.LogicalHeight().IsAuto() &&
       !block_style.LogicalHeight().Value()) &&
      block_style.MarginAfterCollapse() != EMarginCollapse::kSeparate;

  quirk_container_ = block_flow->IsTableCell() || block_flow->IsBody();

  discard_margin_ = can_collapse_margin_before_with_children_ &&
                    block_flow->MustDiscardMarginBefore();

  positive_margin_ = (can_collapse_margin_before_with_children_ &&
                      !block_flow->MustDiscardMarginBefore())
                         ? block_flow->MaxPositiveMarginBefore()
                         : LayoutUnit();
  negative_margin_ = (can_collapse_margin_before_with_children_ &&
                      !block_flow->MustDiscardMarginBefore())
                         ? block_flow->MaxNegativeMarginBefore()
                         : LayoutUnit();
}

LayoutBlockFlow::MarginValues LayoutBlockFlow::MarginValuesForChild(
    LayoutBox& child) const {
  LayoutUnit child_before_positive;
  LayoutUnit child_before_negative;
  LayoutUnit child_after_positive;
  LayoutUnit child_after_negative;

  LayoutUnit before_margin;
  LayoutUnit after_margin;

  LayoutBlockFlow* child_layout_block_flow =
      child.IsLayoutBlockFlow() ? ToLayoutBlockFlow(&child) : nullptr;

  // If the child has the same directionality as we do, then we can just return
  // its margins in the same direction.
  if (!child.IsWritingModeRoot()) {
    if (child_layout_block_flow) {
      child_before_positive =
          child_layout_block_flow->MaxPositiveMarginBefore();
      child_before_negative =
          child_layout_block_flow->MaxNegativeMarginBefore();
      child_after_positive = child_layout_block_flow->MaxPositiveMarginAfter();
      child_after_negative = child_layout_block_flow->MaxNegativeMarginAfter();
    } else {
      before_margin = child.MarginBefore();
      after_margin = child.MarginAfter();
    }
  } else if (child.IsHorizontalWritingMode() == IsHorizontalWritingMode()) {
    // The child has a different directionality. If the child is parallel, then
    // it's just flipped relative to us. We can use the margins for the opposite
    // edges.
    if (child_layout_block_flow) {
      child_before_positive = child_layout_block_flow->MaxPositiveMarginAfter();
      child_before_negative = child_layout_block_flow->MaxNegativeMarginAfter();
      child_after_positive = child_layout_block_flow->MaxPositiveMarginBefore();
      child_after_negative = child_layout_block_flow->MaxNegativeMarginBefore();
    } else {
      before_margin = child.MarginAfter();
      after_margin = child.MarginBefore();
    }
  } else {
    // The child is perpendicular to us, which means its margins don't collapse
    // but are on the "logical left/right" sides of the child box. We can just
    // return the raw margin in this case.
    before_margin = MarginBeforeForChild(child);
    after_margin = MarginAfterForChild(child);
  }

  // Resolve uncollapsing margins into their positive/negative buckets.
  if (before_margin) {
    if (before_margin > 0)
      child_before_positive = before_margin;
    else
      child_before_negative = -before_margin;
  }
  if (after_margin) {
    if (after_margin > 0)
      child_after_positive = after_margin;
    else
      child_after_negative = -after_margin;
  }

  return LayoutBlockFlow::MarginValues(
      child_before_positive, child_before_negative, child_after_positive,
      child_after_negative);
}

LayoutUnit LayoutBlockFlow::AdjustedMarginBeforeForPagination(
    const LayoutBox& child,
    LayoutUnit logical_top_margin_edge,
    LayoutUnit logical_top_border_edge,
    const BlockChildrenLayoutInfo& layout_info) const {
  LayoutUnit effective_margin =
      logical_top_border_edge - logical_top_margin_edge;
  DCHECK(IsPageLogicalHeightKnown());
  if (effective_margin <= LayoutUnit())
    return effective_margin;
  // If margins would pull us past the top of the next fragmentainer, then we
  // need to pull back and let the margins collapse into the fragmentainer
  // boundary. If we're at a fragmentainer boundary, and there's no forced break
  // involved, collapse the margin with the boundary we're at. Otherwise,
  // preserve the margin at the top of the fragmentainer, but collapse it with
  // the next fragmentainer boundary, since no margin should ever live in more
  // than one fragmentainer.
  PageBoundaryRule rule = kAssociateWithLatterPage;
  if (!child.NeedsForcedBreakBefore(layout_info.PreviousBreakAfterValue()) &&
      OffsetFromLogicalTopOfFirstPage() + logical_top_margin_edge >
          LayoutUnit())
    rule = kAssociateWithFormerPage;
  LayoutUnit remaining_space =
      PageRemainingLogicalHeightForOffset(logical_top_margin_edge, rule);
  return std::min(effective_margin, remaining_space);
}

static LayoutBlockFlow* PreviousBlockFlowInFormattingContext(
    const LayoutBox& child) {
  LayoutObject* prev = child.PreviousSibling();
  while (prev && (!prev->IsLayoutBlockFlow() ||
                  ToLayoutBlockFlow(prev)->CreatesNewFormattingContext())) {
    prev = prev->PreviousSibling();
  }
  if (prev)
    return ToLayoutBlockFlow(prev);
  return nullptr;
}

LayoutUnit LayoutBlockFlow::CollapseMargins(
    LayoutBox& child,
    BlockChildrenLayoutInfo& layout_info,
    bool child_is_self_collapsing,
    bool child_discard_margin_before,
    bool child_discard_margin_after) {
  MarginInfo& margin_info = layout_info.GetMarginInfo();

  // The child discards the before margin when the the after margin has discard
  // in the case of a self collapsing block.
  child_discard_margin_before =
      child_discard_margin_before ||
      (child_discard_margin_after && child_is_self_collapsing);

  // Get the four margin values for the child and cache them.
  const LayoutBlockFlow::MarginValues child_margins =
      MarginValuesForChild(child);

  // Get our max pos and neg top margins.
  LayoutUnit pos_top = child_margins.PositiveMarginBefore();
  LayoutUnit neg_top = child_margins.NegativeMarginBefore();

  // For self-collapsing blocks, collapse our bottom margins into our
  // top to get new posTop and negTop values.
  if (child_is_self_collapsing) {
    pos_top = std::max(pos_top, child_margins.PositiveMarginAfter());
    neg_top = std::max(neg_top, child_margins.NegativeMarginAfter());
  }

  // See if the top margin is quirky. We only care if this child has
  // margins that will collapse with us.
  bool top_quirk = HasMarginBeforeQuirk(&child);

  if (margin_info.CanCollapseWithMarginBefore()) {
    if (!child_discard_margin_before && !margin_info.DiscardMargin()) {
      // This child is collapsing with the top of the
      // block. If it has larger margin values, then we need to update
      // our own maximal values.
      if (!GetDocument().InQuirksMode() || !margin_info.QuirkContainer() ||
          !top_quirk)
        SetMaxMarginBeforeValues(std::max(pos_top, MaxPositiveMarginBefore()),
                                 std::max(neg_top, MaxNegativeMarginBefore()));

      // The minute any of the margins involved isn't a quirk, don't
      // collapse it away, even if the margin is smaller (www.webreference.com
      // has an example of this, a <dt> with 0.8em author-specified inside
      // a <dl> inside a <td>.
      if (!margin_info.DeterminedMarginBeforeQuirk() && !top_quirk &&
          (pos_top - neg_top)) {
        SetHasMarginBeforeQuirk(false);
        margin_info.SetDeterminedMarginBeforeQuirk(true);
      }

      if (!margin_info.DeterminedMarginBeforeQuirk() && top_quirk &&
          !MarginBefore()) {
        // We have no top margin and our top child has a quirky margin.
        // We will pick up this quirky margin and pass it through.
        // This deals with the <td><div><p> case.
        // Don't do this for a block that split two inlines though. You do
        // still apply margins in this case.
        SetHasMarginBeforeQuirk(true);
      }
    } else {
      // The before margin of the container will also discard all the margins it
      // is collapsing with.
      SetMustDiscardMarginBefore();
    }
  }

  // Once we find a child with discardMarginBefore all the margins collapsing
  // with us must also discard.
  if (child_discard_margin_before) {
    margin_info.SetDiscardMargin(true);
    margin_info.ClearMargin();
  }

  if (margin_info.QuirkContainer() && margin_info.AtBeforeSideOfBlock() &&
      (pos_top - neg_top))
    margin_info.SetHasMarginBeforeQuirk(top_quirk);

  LayoutUnit before_collapse_logical_top = LogicalHeight();
  LayoutUnit logical_top = before_collapse_logical_top;

  LayoutObject* prev = child.PreviousSibling();
  LayoutBlockFlow* previous_block_flow =
      prev && prev->IsLayoutBlockFlow() ? ToLayoutBlockFlow(prev) : nullptr;
  bool previous_block_flow_can_self_collapse =
      previous_block_flow &&
      !previous_block_flow->IsFloatingOrOutOfFlowPositioned();
  // If the child's previous sibling is a self-collapsing block that cleared a
  // float then its top border edge has been set at the bottom border edge of
  // the float. Since we want to collapse the child's top margin with the self-
  // collapsing block's top and bottom margins we need to adjust our parent's
  // height to match the margin top of the self-collapsing block. If the
  // resulting collapsed margin leaves the child still intruding into the float
  // then we will want to clear it.
  if (!margin_info.CanCollapseWithMarginBefore() &&
      previous_block_flow_can_self_collapse &&
      margin_info.LastChildIsSelfCollapsingBlockWithClearance())
    SetLogicalHeight(
        LogicalHeight() -
        MarginValuesForChild(*previous_block_flow).PositiveMarginBefore());

  if (child_is_self_collapsing) {
    // For a self collapsing block both the before and after margins get
    // discarded. The block doesn't contribute anything to the height of the
    // block. Also, the child's top position equals the logical height of the
    // container.
    if (!child_discard_margin_before && !margin_info.DiscardMargin()) {
      // This child has no height. We need to compute our
      // position before we collapse the child's margins together,
      // so that we can get an accurate position for the zero-height block.
      LayoutUnit collapsed_before_pos = std::max(
          margin_info.PositiveMargin(), child_margins.PositiveMarginBefore());
      LayoutUnit collapsed_before_neg = std::max(
          margin_info.NegativeMargin(), child_margins.NegativeMarginBefore());
      margin_info.SetMargin(collapsed_before_pos, collapsed_before_neg);

      // Now collapse the child's margins together, which means examining our
      // bottom margin values as well.
      margin_info.SetPositiveMarginIfLarger(
          child_margins.PositiveMarginAfter());
      margin_info.SetNegativeMarginIfLarger(
          child_margins.NegativeMarginAfter());

      if (!margin_info.CanCollapseWithMarginBefore()) {
        // We need to make sure that the position of the self-collapsing block
        // is correct, since it could have overflowing content
        // that needs to be positioned correctly (e.g., a block that
        // had a specified height of 0 but that actually had subcontent).
        logical_top =
            LogicalHeight() + collapsed_before_pos - collapsed_before_neg;
      }
    }
  } else {
    if (MustSeparateMarginBeforeForChild(child)) {
      DCHECK(!margin_info.DiscardMargin() ||
             (margin_info.DiscardMargin() && !margin_info.Margin()));
      // If we are at the before side of the block and we collapse, ignore the
      // computed margin and just add the child margin to the container height.
      // This will correctly position the child inside the container.
      LayoutUnit separate_margin = !margin_info.CanCollapseWithMarginBefore()
                                       ? margin_info.Margin()
                                       : LayoutUnit();
      SetLogicalHeight(LogicalHeight() + separate_margin +
                       MarginBeforeForChild(child));
      logical_top = LogicalHeight();
    } else if (!margin_info.DiscardMargin() &&
               (!margin_info.AtBeforeSideOfBlock() ||
                (!margin_info.CanCollapseMarginBeforeWithChildren() &&
                 (!GetDocument().InQuirksMode() ||
                  !margin_info.QuirkContainer() ||
                  !margin_info.HasMarginBeforeQuirk())))) {
      // We're collapsing with a previous sibling's margins and not
      // with the top of the block.
      SetLogicalHeight(LogicalHeight() +
                       std::max(margin_info.PositiveMargin(), pos_top) -
                       std::max(margin_info.NegativeMargin(), neg_top));
      logical_top = LogicalHeight();
    }

    margin_info.SetDiscardMargin(child_discard_margin_after);

    if (!margin_info.DiscardMargin()) {
      margin_info.SetPositiveMargin(child_margins.PositiveMarginAfter());
      margin_info.SetNegativeMargin(child_margins.NegativeMarginAfter());
    } else {
      margin_info.ClearMargin();
    }

    if (margin_info.Margin())
      margin_info.SetHasMarginAfterQuirk(HasMarginAfterQuirk(&child));
  }

  if (View()->GetLayoutState()->IsPaginated() && IsPageLogicalHeightKnown()) {
    LayoutUnit old_logical_top = logical_top;
    LayoutUnit margin = AdjustedMarginBeforeForPagination(
        child, before_collapse_logical_top, logical_top, layout_info);
    logical_top = before_collapse_logical_top + margin;
    SetLogicalHeight(LogicalHeight() + (logical_top - old_logical_top));
  }

  // If |child| has moved up into previous siblings it needs to avoid or clear
  // any floats they contain.
  if (logical_top < before_collapse_logical_top) {
    LayoutUnit old_logical_height = LogicalHeight();
    SetLogicalHeight(logical_top);
    LayoutBlockFlow* previous_block_flow =
        PreviousBlockFlowInFormattingContext(child);
    while (previous_block_flow) {
      auto lowest_float = previous_block_flow->LogicalTop() +
                          previous_block_flow->LowestFloatLogicalBottom();
      if (lowest_float <= logical_top)
        break;
      AddOverhangingFloats(previous_block_flow, false);
      previous_block_flow =
          PreviousBlockFlowInFormattingContext(*previous_block_flow);
    }
    SetLogicalHeight(old_logical_height);
  }

  if (previous_block_flow_can_self_collapse) {
    // If |child|'s previous sibling is or contains a self-collapsing block that
    // cleared a float and margin collapsing resulted in |child| moving up
    // into the margin area of the self-collapsing block then the float it
    // clears is now intruding into |child|. Layout again so that we can look
    // for floats in the parent that overhang |child|'s new logical top.
    bool logical_top_intrudes_into_float =
        logical_top < before_collapse_logical_top;
    if (logical_top_intrudes_into_float && ContainsFloats() &&
        !child.AvoidsFloats() && LowestFloatLogicalBottom() > logical_top) {
      child.SetNeedsLayoutAndFullPaintInvalidation(
          layout_invalidation_reason::kAncestorMarginCollapsing);
    }
  }

  return logical_top;
}

void LayoutBlockFlow::AdjustPositionedBlock(
    LayoutBox& child,
    const BlockChildrenLayoutInfo& layout_info) {
  LayoutUnit logical_top = LogicalHeight();

  // Forced breaks are only specified on in-flow objects, but auto-positioned
  // out-of-flow objects may be affected by a break-after value of the previous
  // in-flow object.
  if (View()->GetLayoutState()->IsPaginated())
    logical_top =
        ApplyForcedBreak(logical_top, layout_info.PreviousBreakAfterValue());

  UpdateStaticInlinePositionForChild(child, logical_top);

  const MarginInfo& margin_info = layout_info.GetMarginInfo();
  if (!margin_info.CanCollapseWithMarginBefore()) {
    // Positioned blocks don't collapse margins, so add the margin provided by
    // the container now. The child's own margin is added later when calculating
    // its logical top.
    LayoutUnit collapsed_before_pos = margin_info.PositiveMargin();
    LayoutUnit collapsed_before_neg = margin_info.NegativeMargin();
    logical_top += collapsed_before_pos - collapsed_before_neg;
  }

  PaintLayer* child_layer = child.Layer();
  if (child_layer->StaticBlockPosition() != logical_top)
    child_layer->SetStaticBlockPosition(logical_top);
}

LayoutUnit LayoutBlockFlow::ClearFloatsIfNeeded(LayoutBox& child,
                                                MarginInfo& margin_info,
                                                LayoutUnit old_top_pos_margin,
                                                LayoutUnit old_top_neg_margin,
                                                LayoutUnit y_pos,
                                                bool child_is_self_collapsing,
                                                bool child_discard_margin) {
  LayoutUnit height_increase = GetClearDelta(&child, y_pos);
  margin_info.SetLastChildIsSelfCollapsingBlockWithClearance(false);

  if (!height_increase)
    return y_pos;

  if (child_is_self_collapsing) {
    margin_info.SetLastChildIsSelfCollapsingBlockWithClearance(true);
    margin_info.SetDiscardMargin(child_discard_margin);

    // For self-collapsing blocks that clear, they can still collapse their
    // margins with following siblings. Reset the current margins to represent
    // the self-collapsing block's margins only.
    // If DISCARD is specified for -webkit-margin-collapse, reset the margin
    // values.
    LayoutBlockFlow::MarginValues child_margins = MarginValuesForChild(child);
    if (!child_discard_margin) {
      margin_info.SetPositiveMargin(
          std::max(child_margins.PositiveMarginBefore(),
                   child_margins.PositiveMarginAfter()));
      margin_info.SetNegativeMargin(
          std::max(child_margins.NegativeMarginBefore(),
                   child_margins.NegativeMarginAfter()));
    } else {
      margin_info.ClearMargin();
    }

    // CSS2.1 states:
    // "If the top and bottom margins of an element with clearance are
    // adjoining, its margins collapse with the adjoining margins of following
    // siblings but that resulting margin does not collapse with the bottom
    // margin of the parent block."
    // So the parent's bottom margin cannot collapse through this block or any
    // subsequent self-collapsing blocks. Set a bit to ensure this happens; it
    // will get reset if we encounter an in-flow sibling that is not
    // self-collapsing.
    margin_info.SetCanCollapseMarginAfterWithLastChild(false);

    // For now set the border-top of |child| flush with the bottom border-edge
    // of the float so it can layout any floating or positioned children of its
    // own at the correct vertical position. If subsequent siblings attempt to
    // collapse with |child|'s margins in |collapseMargins| we will adjust the
    // height of the parent to |child|'s margin top (which if it is positive
    // sits up 'inside' the float it's clearing) so that all three margins can
    // collapse at the correct vertical position.
    // Per CSS2.1 we need to ensure that any negative margin-top clears |child|
    // beyond the bottom border-edge of the float so that the top border edge of
    // the child (i.e. its clearance)  is at a position that satisfies the
    // equation: "the amount of clearance is set so that:
    //   clearance + margin-top = [height of float],
    // i.e., clearance = [height of float] - margin-top".
    SetLogicalHeight(child.LogicalTop() + child_margins.NegativeMarginBefore());
  } else {
    // Increase our height by the amount we had to clear.
    SetLogicalHeight(LogicalHeight() + height_increase);
  }

  if (margin_info.CanCollapseWithMarginBefore()) {
    // We can no longer collapse with the top of the block since a clear
    // occurred. The empty blocks collapse into the cleared block.
    SetMaxMarginBeforeValues(old_top_pos_margin, old_top_neg_margin);
    margin_info.SetAtBeforeSideOfBlock(false);

    // In case the child discarded the before margin of the block we need to
    // reset the mustDiscardMarginBefore flag to the initial value.
    SetMustDiscardMarginBefore(StyleRef().MarginBeforeCollapse() ==
                               EMarginCollapse::kDiscard);
  }

  return y_pos + height_increase;
}

void LayoutBlockFlow::SetCollapsedBottomMargin(const MarginInfo& margin_info) {
  if (margin_info.CanCollapseWithMarginAfter() &&
      !margin_info.CanCollapseWithMarginBefore()) {
    // Update the after side margin of the container to discard if the after
    // margin of the last child also discards and we collapse with it.
    // Don't update the max margin values because we won't need them anyway.
    if (margin_info.DiscardMargin()) {
      SetMustDiscardMarginAfter();
      return;
    }

    // Update our max pos/neg bottom margins, since we collapsed our bottom
    // margins with our children.
    SetMaxMarginAfterValues(
        std::max(MaxPositiveMarginAfter(), margin_info.PositiveMargin()),
        std::max(MaxNegativeMarginAfter(), margin_info.NegativeMargin()));

    if (!margin_info.HasMarginAfterQuirk())
      SetHasMarginAfterQuirk(false);

    if (margin_info.HasMarginAfterQuirk() && !MarginAfter()) {
      // We have no bottom margin and our last child has a quirky margin.
      // We will pick up this quirky margin and pass it through.
      // This deals with the <td><div><p> case.
      SetHasMarginAfterQuirk(true);
    }
  }
}

DISABLE_CFI_PERF
void LayoutBlockFlow::MarginBeforeEstimateForChild(
    LayoutBox& child,
    LayoutUnit& positive_margin_before,
    LayoutUnit& negative_margin_before,
    bool& discard_margin_before) const {
  // Give up if in quirks mode and we're a body/table cell and the top margin of
  // the child box is quirky.
  // Give up if the child specified -webkit-margin-collapse: separate that
  // prevents collapsing.
  // FIXME: Use writing mode independent accessor for marginBeforeCollapse.
  if ((GetDocument().InQuirksMode() && HasMarginBeforeQuirk(&child) &&
       (IsTableCell() || IsBody())) ||
      child.StyleRef().MarginBeforeCollapse() == EMarginCollapse::kSeparate)
    return;

  // The margins are discarded by a child that specified
  // -webkit-margin-collapse: discard.
  // FIXME: Use writing mode independent accessor for marginBeforeCollapse.
  if (child.StyleRef().MarginBeforeCollapse() == EMarginCollapse::kDiscard) {
    positive_margin_before = LayoutUnit();
    negative_margin_before = LayoutUnit();
    discard_margin_before = true;
    return;
  }

  LayoutUnit before_child_margin = MarginBeforeForChild(child);
  positive_margin_before =
      std::max(positive_margin_before, before_child_margin);
  negative_margin_before =
      std::max(negative_margin_before, -before_child_margin);

  if (!child.IsLayoutBlockFlow())
    return;

  LayoutBlockFlow* child_block_flow = ToLayoutBlockFlow(&child);
  if (child_block_flow->ChildrenInline() ||
      child_block_flow->IsWritingModeRoot())
    return;

  MarginInfo child_margin_info(
      child_block_flow,
      child_block_flow->BorderBefore() + child_block_flow->PaddingBefore(),
      child_block_flow->BorderAfter() + child_block_flow->PaddingAfter());
  if (!child_margin_info.CanCollapseMarginBeforeWithChildren())
    return;

  LayoutBox* grandchild_box = child_block_flow->FirstChildBox();
  for (; grandchild_box; grandchild_box = grandchild_box->NextSiblingBox()) {
    if (!grandchild_box->IsFloatingOrOutOfFlowPositioned() &&
        !grandchild_box->IsColumnSpanAll())
      break;
  }

  if (!grandchild_box)
    return;

  // Make sure to update the block margins now for the grandchild box so that
  // we're looking at current values.
  if (grandchild_box->NeedsLayout()) {
    grandchild_box->ComputeAndSetBlockDirectionMargins(this);
    if (grandchild_box->IsLayoutBlock()) {
      LayoutBlock* grandchild_block = ToLayoutBlock(grandchild_box);
      grandchild_block->SetHasMarginBeforeQuirk(
          grandchild_box->StyleRef().HasMarginBeforeQuirk());
      grandchild_block->SetHasMarginAfterQuirk(
          grandchild_box->StyleRef().HasMarginAfterQuirk());
    }
  }

  // If we have a 'clear' value but also have a margin we may not actually
  // require clearance to move past any floats. If that's the case we want to be
  // sure we estimate the correct position including margins after any floats
  // rather than use 'clearance' later which could give us the wrong position.
  if (grandchild_box->StyleRef().Clear() != EClear::kNone &&
      child_block_flow->MarginBeforeForChild(*grandchild_box) == 0)
    return;

  // Collapse the margin of the grandchild box with our own to produce an
  // estimate.
  child_block_flow->MarginBeforeEstimateForChild(
      *grandchild_box, positive_margin_before, negative_margin_before,
      discard_margin_before);
}

LayoutUnit LayoutBlockFlow::EstimateLogicalTopPosition(
    LayoutBox& child,
    const BlockChildrenLayoutInfo& layout_info,
    LayoutUnit& estimate_without_pagination) {
  const MarginInfo& margin_info = layout_info.GetMarginInfo();
  // FIXME: We need to eliminate the estimation of vertical position, because
  // when it's wrong we sometimes trigger a pathological
  // relayout if there are intruding floats.
  LayoutUnit logical_top_estimate = LogicalHeight();
  LayoutUnit positive_margin_before;
  LayoutUnit negative_margin_before;
  bool discard_margin_before = false;
  if (!margin_info.CanCollapseWithMarginBefore()) {
    if (child.SelfNeedsLayout()) {
      // Try to do a basic estimation of how the collapse is going to go.
      MarginBeforeEstimateForChild(child, positive_margin_before,
                                   negative_margin_before,
                                   discard_margin_before);
    } else {
      // Use the cached collapsed margin values from a previous layout. Most of
      // the time they will be right.
      LayoutBlockFlow::MarginValues margin_values = MarginValuesForChild(child);
      positive_margin_before = std::max(positive_margin_before,
                                        margin_values.PositiveMarginBefore());
      negative_margin_before = std::max(negative_margin_before,
                                        margin_values.NegativeMarginBefore());
      discard_margin_before = MustDiscardMarginBeforeForChild(child);
    }

    // Collapse the result with our current margins.
    if (!discard_margin_before)
      logical_top_estimate +=
          std::max(margin_info.PositiveMargin(), positive_margin_before) -
          std::max(margin_info.NegativeMargin(), negative_margin_before);
  }

  LayoutState* layout_state = View()->GetLayoutState();
  if (layout_state->IsPaginated() && IsPageLogicalHeightKnown()) {
    LayoutUnit margin = AdjustedMarginBeforeForPagination(
        child, LogicalHeight(), logical_top_estimate, layout_info);
    logical_top_estimate = LogicalHeight() + margin;
  }

  logical_top_estimate += GetClearDelta(&child, logical_top_estimate);

  estimate_without_pagination = logical_top_estimate;

  if (layout_state->IsPaginated()) {
    if (!layout_info.IsAtFirstInFlowChild()) {
      // Estimate the need for a forced break in front of this child. The final
      // break policy at this class A break point isn't known until we have laid
      // out the children of |child|. There may be forced break-before values
      // set on first-children inside that get propagated up to the child.
      // Just make an estimate with what we know so far.
      EBreakBetween break_value =
          child.ClassABreakPointValue(layout_info.PreviousBreakAfterValue());
      if (IsForcedFragmentainerBreakValue(break_value)) {
        logical_top_estimate = ApplyForcedBreak(LogicalHeight(), break_value);
        // Disregard previous margins, since they will collapse with the
        // fragmentainer boundary, due to the forced break. Only apply margins
        // that have been specified on the child or its descendants.
        if (!discard_margin_before)
          logical_top_estimate +=
              positive_margin_before - negative_margin_before;

        // Clearance may already have taken us past the beginning of the next
        // fragmentainer.
        return std::max(estimate_without_pagination, logical_top_estimate);
      }

      logical_top_estimate =
          AdjustForUnsplittableChild(child, logical_top_estimate);
    }
  }

  return logical_top_estimate;
}

void LayoutBlockFlow::AdjustFloatingBlock(const MarginInfo& margin_info) {
  // The float should be positioned taking into account the bottom margin
  // of the previous flow. We add that margin into the height, get the
  // float positioned properly, and then subtract the margin out of the
  // height again. In the case of self-collapsing blocks, we always just
  // use the top margins, since the self-collapsing block collapsed its
  // own bottom margin into its top margin.
  //
  // Note also that the previous flow may collapse its margin into the top of
  // our block. If this is the case, then we do not add the margin in to our
  // height when computing the position of the float. This condition can be
  // tested for by simply calling canCollapseWithMarginBefore. See
  // http://www.hixie.ch/tests/adhoc/css/box/block/margin-collapse/046.html for
  // an example of this scenario.
  LayoutUnit logical_top = LogicalHeight();
  if (!margin_info.CanCollapseWithMarginBefore())
    logical_top += margin_info.Margin();
  PlaceNewFloats(logical_top);
}

void LayoutBlockFlow::HandleAfterSideOfBlock(LayoutBox* last_child,
                                             LayoutUnit before_side,
                                             LayoutUnit after_side,
                                             MarginInfo& margin_info) {
  margin_info.SetAtAfterSideOfBlock(true);

  // If our last child was a self-collapsing block with clearance then our
  // logical height is flush with the bottom edge of the float that the child
  // clears. The correct vertical position for the margin-collapsing we want to
  // perform now is at the child's margin-top - so adjust our height to that
  // position.
  if (margin_info.LastChildIsSelfCollapsingBlockWithClearance()) {
    DCHECK(last_child);
    SetLogicalHeight(LogicalHeight() -
                     MarginValuesForChild(*last_child).PositiveMarginBefore());
  }

  if (margin_info.CanCollapseMarginAfterWithChildren() &&
      !margin_info.CanCollapseMarginAfterWithLastChild())
    margin_info.SetCanCollapseMarginAfterWithChildren(false);

  // If we can't collapse with children then go ahead and add in the bottom
  // margin.
  if (!margin_info.DiscardMargin() &&
      (!margin_info.CanCollapseWithMarginAfter() &&
       !margin_info.CanCollapseWithMarginBefore() &&
       (!GetDocument().InQuirksMode() || !margin_info.QuirkContainer() ||
        !margin_info.HasMarginAfterQuirk())))
    SetLogicalHeight(LogicalHeight() + margin_info.Margin());

  // Now add in our bottom border/padding.
  SetLogicalHeight(LogicalHeight() + after_side);

  // Negative margins can cause our height to shrink below our minimal height
  // (border/padding). If this happens, ensure that the computed height is
  // increased to the minimal height.
  SetLogicalHeight(std::max(LogicalHeight(), before_side + after_side));

  // Update our bottom collapsed margin info.
  SetCollapsedBottomMargin(margin_info);

  // There's no class A break point right after the last child, only *between*
  // siblings. So propagate the break-after value, and keep looking for a class
  // A break point (at the next in-flow block-level object), where we'll join
  // this break-after value with the break-before value there.
  if (View()->GetLayoutState()->IsPaginated() && last_child)
    SetBreakAfter(
        JoinFragmentainerBreakValues(BreakAfter(), last_child->BreakAfter()));
}

void LayoutBlockFlow::SetMustDiscardMarginBefore(bool value) {
  if (StyleRef().MarginBeforeCollapse() == EMarginCollapse::kDiscard) {
    DCHECK(value);
    return;
  }

  if (!rare_data_ && !value)
    return;

  if (!rare_data_)
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);

  rare_data_->discard_margin_before_ = value;
}

void LayoutBlockFlow::SetMustDiscardMarginAfter(bool value) {
  if (StyleRef().MarginAfterCollapse() == EMarginCollapse::kDiscard) {
    DCHECK(value);
    return;
  }

  if (!rare_data_ && !value)
    return;

  if (!rare_data_)
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);

  rare_data_->discard_margin_after_ = value;
}

bool LayoutBlockFlow::MustDiscardMarginBefore() const {
  return StyleRef().MarginBeforeCollapse() == EMarginCollapse::kDiscard ||
         (rare_data_ && rare_data_->discard_margin_before_);
}

bool LayoutBlockFlow::MustDiscardMarginAfter() const {
  return StyleRef().MarginAfterCollapse() == EMarginCollapse::kDiscard ||
         (rare_data_ && rare_data_->discard_margin_after_);
}

bool LayoutBlockFlow::MustDiscardMarginBeforeForChild(
    const LayoutBox& child) const {
  DCHECK(!child.SelfNeedsLayout() || child.LayoutBlockedByDisplayLock());
  if (!child.IsWritingModeRoot()) {
    return child.IsLayoutBlockFlow()
               ? ToLayoutBlockFlow(&child)->MustDiscardMarginBefore()
               : (child.StyleRef().MarginBeforeCollapse() ==
                  EMarginCollapse::kDiscard);
  }
  if (child.IsHorizontalWritingMode() == IsHorizontalWritingMode()) {
    return child.IsLayoutBlockFlow()
               ? ToLayoutBlockFlow(&child)->MustDiscardMarginAfter()
               : (child.StyleRef().MarginAfterCollapse() ==
                  EMarginCollapse::kDiscard);
  }

  // FIXME: We return false here because the implementation is not geometrically
  // complete. We have values only for before/after, not start/end.
  // In case the boxes are perpendicular we assume the property is not
  // specified.
  return false;
}

bool LayoutBlockFlow::MustDiscardMarginAfterForChild(
    const LayoutBox& child) const {
  DCHECK(!child.SelfNeedsLayout() || child.LayoutBlockedByDisplayLock());
  if (!child.IsWritingModeRoot()) {
    return child.IsLayoutBlockFlow()
               ? ToLayoutBlockFlow(&child)->MustDiscardMarginAfter()
               : (child.StyleRef().MarginAfterCollapse() ==
                  EMarginCollapse::kDiscard);
  }
  if (child.IsHorizontalWritingMode() == IsHorizontalWritingMode()) {
    return child.IsLayoutBlockFlow()
               ? ToLayoutBlockFlow(&child)->MustDiscardMarginBefore()
               : (child.StyleRef().MarginBeforeCollapse() ==
                  EMarginCollapse::kDiscard);
  }

  // FIXME: See |mustDiscardMarginBeforeForChild| above.
  return false;
}

void LayoutBlockFlow::SetMaxMarginBeforeValues(LayoutUnit pos, LayoutUnit neg) {
  if (!rare_data_) {
    if (pos == LayoutBlockFlowRareData::PositiveMarginBeforeDefault(this) &&
        neg == LayoutBlockFlowRareData::NegativeMarginBeforeDefault(this))
      return;
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);
  }
  rare_data_->margins_.SetPositiveMarginBefore(pos);
  rare_data_->margins_.SetNegativeMarginBefore(neg);
}

void LayoutBlockFlow::SetMaxMarginAfterValues(LayoutUnit pos, LayoutUnit neg) {
  if (!rare_data_) {
    if (pos == LayoutBlockFlowRareData::PositiveMarginAfterDefault(this) &&
        neg == LayoutBlockFlowRareData::NegativeMarginAfterDefault(this))
      return;
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);
  }
  rare_data_->margins_.SetPositiveMarginAfter(pos);
  rare_data_->margins_.SetNegativeMarginAfter(neg);
}

bool LayoutBlockFlow::MustSeparateMarginBeforeForChild(
    const LayoutBox& child) const {
  DCHECK(!child.SelfNeedsLayout() || child.LayoutBlockedByDisplayLock());
  const ComputedStyle& child_style = child.StyleRef();
  if (!child.IsWritingModeRoot())
    return child_style.MarginBeforeCollapse() == EMarginCollapse::kSeparate;
  if (child.IsHorizontalWritingMode() == IsHorizontalWritingMode())
    return child_style.MarginAfterCollapse() == EMarginCollapse::kSeparate;

  // FIXME: See |mustDiscardMarginBeforeForChild| above.
  return false;
}

bool LayoutBlockFlow::MustSeparateMarginAfterForChild(
    const LayoutBox& child) const {
  DCHECK(!child.SelfNeedsLayout() || child.LayoutBlockedByDisplayLock());
  const ComputedStyle& child_style = child.StyleRef();
  if (!child.IsWritingModeRoot())
    return child_style.MarginAfterCollapse() == EMarginCollapse::kSeparate;
  if (child.IsHorizontalWritingMode() == IsHorizontalWritingMode())
    return child_style.MarginBeforeCollapse() == EMarginCollapse::kSeparate;

  // FIXME: See |mustDiscardMarginBeforeForChild| above.
  return false;
}

LayoutUnit LayoutBlockFlow::ApplyForcedBreak(LayoutUnit logical_offset,
                                             EBreakBetween break_value) {
  if (!IsForcedFragmentainerBreakValue(break_value))
    return logical_offset;
  // TODO(mstensho): honor breakValue. There are different types of forced
  // breaks. We currently just assume that we want to break to the top of the
  // next fragmentainer of the fragmentation context we're in. However, we may
  // want to find the next left or right page - even if we're inside a multicol
  // container when printing.
  if (!IsPageLogicalHeightKnown()) {
    // Page height is still unknown, so we cannot insert forced breaks.
    return logical_offset;
  }
  LayoutUnit remaining_logical_height = PageRemainingLogicalHeightForOffset(
      logical_offset, kAssociateWithLatterPage);
  if (remaining_logical_height == PageLogicalHeightForOffset(logical_offset))
    return logical_offset;  // Don't break if we're already at the block start
                            // of a fragmentainer.

  // If this is the first forced break inside this object, store the
  // location. We need this information later if there's a break-inside:avoid
  // object further up. We need to know if there are any forced breaks inside
  // such objects, in order to determine whether we need to push it to the next
  // fragmentainer or not.
  if (!FirstForcedBreakOffset())
    SetFirstForcedBreakOffset(logical_offset);

  return logical_offset + remaining_logical_height;
}

void LayoutBlockFlow::SetBreakBefore(EBreakBetween break_value) {
  if (break_value != EBreakBetween::kAuto &&
      !IsBreakBetweenControllable(break_value))
    break_value = EBreakBetween::kAuto;
  if (break_value == EBreakBetween::kAuto && !rare_data_)
    return;
  EnsureRareData().break_before_ = static_cast<unsigned>(break_value);
}

void LayoutBlockFlow::SetBreakAfter(EBreakBetween break_value) {
  if (break_value != EBreakBetween::kAuto &&
      !IsBreakBetweenControllable(break_value))
    break_value = EBreakBetween::kAuto;
  if (break_value == EBreakBetween::kAuto && !rare_data_)
    return;
  EnsureRareData().break_after_ = static_cast<unsigned>(break_value);
}

EBreakBetween LayoutBlockFlow::BreakBefore() const {
  return rare_data_ ? static_cast<EBreakBetween>(rare_data_->break_before_)
                    : EBreakBetween::kAuto;
}

EBreakBetween LayoutBlockFlow::BreakAfter() const {
  return rare_data_ ? static_cast<EBreakBetween>(rare_data_->break_after_)
                    : EBreakBetween::kAuto;
}

void LayoutBlockFlow::AddVisualOverflowFromFloats() {
  if (!floating_objects_)
    return;

  for (auto& floating_object : floating_objects_->Set()) {
    if (floating_object->IsDescendant()) {
      AddVisualOverflowFromChild(
          *floating_object->GetLayoutObject(),
          LayoutSize(XPositionForFloatIncludingMargin(*floating_object),
                     YPositionForFloatIncludingMargin(*floating_object)));
    }
  }
}

void LayoutBlockFlow::AddLayoutOverflowFromFloats() {
  if (!floating_objects_)
    return;

  for (auto& floating_object : floating_objects_->Set()) {
    if (floating_object->IsDescendant()) {
      AddLayoutOverflowFromChild(
          *floating_object->GetLayoutObject(),
          LayoutSize(XPositionForFloatIncludingMargin(*floating_object),
                     YPositionForFloatIncludingMargin(*floating_object)));
    }
  }
}

scoped_refptr<NGLayoutResult> LayoutBlockFlow::CachedLayoutResult(
    const NGConstraintSpace&,
    const NGBreakToken*) {
  return nullptr;
}

scoped_refptr<const NGLayoutResult>
LayoutBlockFlow::CachedLayoutResultForTesting() {
  return nullptr;
}

void LayoutBlockFlow::SetCachedLayoutResult(const NGConstraintSpace&,
                                            const NGBreakToken*,
                                            const NGLayoutResult&) {}

void LayoutBlockFlow::ClearCachedLayoutResult() {}

bool LayoutBlockFlow::AreCachedLinesValidFor(const NGConstraintSpace&) const {
  return false;
}

void LayoutBlockFlow::SetPaintFragment(const NGBreakToken*,
                                       scoped_refptr<const NGPhysicalFragment>,
                                       NGPhysicalOffset) {}

void LayoutBlockFlow::UpdatePaintFragmentFromCachedLayoutResult(
    const NGBreakToken*,
    scoped_refptr<const NGPhysicalFragment>,
    NGPhysicalOffset) {}

void LayoutBlockFlow::ComputeVisualOverflow(
    const LayoutRect& previous_visual_overflow_rect,
    bool recompute_floats) {
  AddVisualOverflowFromChildren();

  AddVisualEffectOverflow();
  AddVisualOverflowFromTheme();

  if (recompute_floats || CreatesNewFormattingContext() ||
      HasSelfPaintingLayer())
    AddVisualOverflowFromFloats();

  if (VisualOverflowRect() != previous_visual_overflow_rect) {
    if (Layer())
      Layer()->SetNeedsCompositingInputsUpdate();
    GetFrameView()->SetIntersectionObservationState(LocalFrameView::kDesired);
  }
}

void LayoutBlockFlow::ComputeLayoutOverflow(LayoutUnit old_client_after_edge,
                                            bool recompute_floats) {
  LayoutBlock::ComputeLayoutOverflow(old_client_after_edge, recompute_floats);
  // TODO(chrishtr): why does it check for a self-painting layer? That should
  // only apply to visual overflow.
  if (recompute_floats || CreatesNewFormattingContext() ||
      HasSelfPaintingLayer())
    AddLayoutOverflowFromFloats();
}

void LayoutBlockFlow::ComputeSelfHitTestRects(
    Vector<LayoutRect>& rects,
    const LayoutPoint& layer_offset) const {
  LayoutBlock::ComputeSelfHitTestRects(rects, layer_offset);

  if (!HasHorizontalLayoutOverflow() && !HasVerticalLayoutOverflow())
    return;

  for (RootInlineBox* curr = FirstRootBox(); curr; curr = curr->NextRootBox()) {
    LayoutUnit top = std::max<LayoutUnit>(curr->LineTop(), curr->Y());
    LayoutUnit bottom =
        std::min<LayoutUnit>(curr->LineBottom(), curr->Y() + curr->Height());
    LayoutRect rect(layer_offset.X() + curr->X(), layer_offset.Y() + top,
                    curr->Width(), bottom - top);
    // It's common for this rect to be entirely contained in our box, so exclude
    // that simple case.
    if (!rect.IsEmpty() && (rects.IsEmpty() || !rects[0].Contains(rect)))
      rects.push_back(rect);
  }
}

void LayoutBlockFlow::AbsoluteRects(
    Vector<IntRect>& rects,
    const LayoutPoint& accumulated_offset) const {
  if (!IsAnonymousBlockContinuation()) {
    LayoutBlock::AbsoluteRects(rects, accumulated_offset);
    return;
  }
  // For blocks inside inlines, we go ahead and include margins so that we run
  // right up to the inline boxes above and below us (thus getting merged with
  // them to form a single irregular shape).
  // FIXME: This is wrong for vertical writing-modes.
  // https://bugs.webkit.org/show_bug.cgi?id=46781
  LayoutRect rect(accumulated_offset, Size());
  rect.Expand(CollapsedMarginBoxLogicalOutsets());
  rects.push_back(PixelSnappedIntRect(rect));
  Continuation()->AbsoluteRects(
      rects,
      accumulated_offset -
          ToLayoutSize(
              Location() +
              InlineElementContinuation()->ContainingBlock()->Location()));
}

void LayoutBlockFlow::AbsoluteQuads(Vector<FloatQuad>& quads,
                                    MapCoordinatesFlags mode) const {
  if (!IsAnonymousBlockContinuation()) {
    LayoutBlock::AbsoluteQuads(quads, mode);
    return;
  }
  LayoutBoxModelObject::AbsoluteQuads(quads, mode);
}

void LayoutBlockFlow::AbsoluteQuadsForSelf(Vector<FloatQuad>& quads,
                                           MapCoordinatesFlags mode) const {
  // For blocks inside inlines, we go ahead and include margins so that we run
  // right up to the inline boxes above and below us (thus getting merged with
  // them to form a single irregular shape).
  // FIXME: This is wrong for vertical writing-modes.
  // https://bugs.webkit.org/show_bug.cgi?id=46781
  LayoutRect local_rect(LayoutPoint(), Size());
  local_rect.Expand(CollapsedMarginBoxLogicalOutsets());
  quads.push_back(LocalToAbsoluteQuad(FloatRect(local_rect), mode));
}

LayoutObject* LayoutBlockFlow::HoverAncestor() const {
  return IsAnonymousBlockContinuation() ? Continuation()
                                        : LayoutBlock::HoverAncestor();
}

RootInlineBox* LayoutBlockFlow::CreateAndAppendRootInlineBox() {
  RootInlineBox* root_box = CreateRootInlineBox();
  line_boxes_.AppendLineBox(root_box);

  return root_box;
}

// Note: When this function is called from |LayoutInline::SplitFlow()|, some
// fragments point to destroyed |LayoutObject|.
void LayoutBlockFlow::DeleteLineBoxTree() {
  if (ContainsFloats())
    floating_objects_->ClearLineBoxTreePointers();

  line_boxes_.DeleteLineBoxTree();
}

int LayoutBlockFlow::LineCount(
    const RootInlineBox* stop_root_inline_box) const {
#ifndef NDEBUG
  DCHECK(!stop_root_inline_box ||
         stop_root_inline_box->Block().DebugPointer() == this);
#endif
  if (!ChildrenInline())
    return 0;

  int count = 0;
  for (const RootInlineBox* box = FirstRootBox(); box;
       box = box->NextRootBox()) {
    count++;
    if (box == stop_root_inline_box)
      break;
  }
  return count;
}

LayoutUnit LayoutBlockFlow::FirstLineBoxBaseline() const {
  if (ShouldApplyLayoutContainment())
    return LayoutUnit(-1);
  // Orthogonal grid items can participante in baseline alignment along column
  // axis.
  if (IsWritingModeRoot() && !IsRubyRun() && !IsGridItem())
    return LayoutUnit(-1);
  if (!ChildrenInline())
    return LayoutBlock::FirstLineBoxBaseline();
  if (FirstLineBox()) {
    const SimpleFontData* font_data = Style(true)->GetFont().PrimaryFont();
    DCHECK(font_data);
    if (!font_data)
      return LayoutUnit(-1);
    // fontMetrics 'ascent' is the distance above the baseline to the 'over'
    // edge, which is 'top' for horizontal and 'right' for vertical-lr and
    // vertical-rl. However, firstLineBox()->logicalTop() gives the offset from
    // the 'left' edge for vertical-lr, hence we need to use the Font Metrics
    // 'descent' instead. The result should be handled accordingly by the caller
    // as a 'descent' value, in order to compute properly the max baseline.
    if (StyleRef().IsFlippedLinesWritingMode()) {
      return FirstLineBox()->LogicalTop() + font_data->GetFontMetrics().Descent(
                                                FirstRootBox()->BaselineType());
    }
    return FirstLineBox()->LogicalTop() +
           font_data->GetFontMetrics().Ascent(FirstRootBox()->BaselineType());
  }
  if (RuntimeEnabledFeatures::LayoutNGEnabled()) {
    if (const NGPaintFragment* paint_fragment = PaintFragment()) {
      NGBoxFragment box_fragment(
          StyleRef().GetWritingMode(), StyleRef().Direction(),
          ToNGPhysicalBoxFragment(paint_fragment->PhysicalFragment()));
      NGLineHeightMetrics metrics =
          box_fragment.BaselineMetricsWithoutSynthesize(
              {NGBaselineAlgorithmType::kFirstLine,
               StyleRef().GetFontBaseline()});
      if (!metrics.IsEmpty())
        return metrics.ascent;
    }
  }
  return LayoutUnit(-1);
}

LayoutUnit LayoutBlockFlow::InlineBlockBaseline(
    LineDirectionMode line_direction) const {
  if (UseLogicalBottomMarginEdgeForInlineBlockBaseline()) {
    // We are not calling baselinePosition here because the caller should add
    // the margin-top/margin-right, not us.
    return line_direction == kHorizontalLine ? Size().Height() + MarginBottom()
                                             : Size().Width() + MarginLeft();
  }
  if (IsWritingModeRoot() && !IsRubyRun())
    return LayoutUnit(-1);
  if (!ChildrenInline())
    return LayoutBlock::InlineBlockBaseline(line_direction);
  if (LastLineBox()) {
    const SimpleFontData* font_data =
        Style(LastLineBox() == FirstLineBox())->GetFont().PrimaryFont();
    DCHECK(font_data);
    if (!font_data)
      return LayoutUnit(-1);
    // InlineFlowBox::placeBoxesInBlockDirection will flip lines in
    // case of verticalLR mode, so we can assume verticalRL for now.
    if (StyleRef().IsFlippedLinesWritingMode()) {
      return LogicalHeight() - LastLineBox()->LogicalBottom() +
             font_data->GetFontMetrics().Ascent(LastRootBox()->BaselineType());
    }
    return LastLineBox()->LogicalTop() +
           font_data->GetFontMetrics().Ascent(LastRootBox()->BaselineType());
  }
  if (!HasLineIfEmpty())
    return LayoutUnit(-1);

  const SimpleFontData* font_data = FirstLineStyle()->GetFont().PrimaryFont();
  DCHECK(font_data);
  if (!font_data)
    return LayoutUnit(-1);

  const FontMetrics& font_metrics = font_data->GetFontMetrics();
  return LayoutUnit(
      (font_metrics.Ascent() +
       (LineHeight(true, line_direction, kPositionOfInteriorLineBoxes) -
        font_metrics.Height()) /
           2 +
       (line_direction == kHorizontalLine ? BorderTop() + PaddingTop()
                                          : BorderRight() + PaddingRight()))
          .ToInt());
}

void LayoutBlockFlow::RemoveFloatingObjectsFromDescendants() {
  if (!ContainsFloats())
    return;
  RemoveFloatingObjects();
  SetChildNeedsLayout(kMarkOnlyThis);

  // If our children are inline, then the only boxes which could contain floats
  // are atomic inlines (e.g. inline-block, float etc.) and these create
  // formatting contexts, so can't pick up intruding floats from
  // ancestors/siblings - making them safe to skip. We do need to examine the
  // lines, though, as there may be pointers to the any of the objects that we
  // are going to remove. Mark those lines dirty, to avoid accessing dangling
  // pointers. Also, yikes!
  if (ChildrenInline()) {
    for (auto* line = FirstRootBox(); line; line = line->NextRootBox()) {
      if (!line->IsDirty()) {
        if (const auto* floats = line->FloatsPtr()) {
          if (floats->size())
            line->MarkDirty();
        }
      }
    }
    return;
  }
  for (LayoutObject* child = FirstChild(); child;
       child = child->NextSibling()) {
    // We don't skip blocks that create formatting contexts as they may have
    // only recently changed style and their float lists may still contain
    // floats from siblings and ancestors.
    if (child->IsLayoutBlockFlow())
      ToLayoutBlockFlow(child)->RemoveFloatingObjectsFromDescendants();
  }
}

void LayoutBlockFlow::MarkAllDescendantsWithFloatsForLayout(
    LayoutBox* float_to_remove,
    bool in_layout) {
  if (!EverHadLayout() && !ContainsFloats())
    return;

  if (descendants_with_floats_marked_for_layout_ && !float_to_remove)
    return;
  descendants_with_floats_marked_for_layout_ |= !float_to_remove;

  MarkingBehavior mark_parents =
      in_layout ? kMarkOnlyThis : kMarkContainerChain;
  SetChildNeedsLayout(mark_parents);

  if (float_to_remove)
    RemoveFloatingObject(float_to_remove);

  // Iterate over our children and mark them as needed. If our children are
  // inline, then the only boxes which could contain floats are atomic inlines
  // (e.g. inline-block, float etc.) and these create formatting contexts, so
  // can't pick up intruding floats from ancestors/siblings - making them safe
  // to skip.
  if (!ChildrenInline()) {
    for (LayoutObject* child = FirstChild(); child;
         child = child->NextSibling()) {
      if ((!float_to_remove && child->IsFloatingOrOutOfFlowPositioned()) ||
          !child->IsLayoutBlock())
        continue;
      if (!child->IsLayoutBlockFlow()) {
        LayoutBlock* child_block = ToLayoutBlock(child);
        if (child_block->ShrinkToAvoidFloats() && child_block->EverHadLayout())
          child_block->SetChildNeedsLayout(mark_parents);
        continue;
      }
      LayoutBlockFlow* child_block_flow = ToLayoutBlockFlow(child);
      if ((float_to_remove ? child_block_flow->ContainsFloat(float_to_remove)
                           : child_block_flow->ContainsFloats()) ||
          child_block_flow->ShrinkToAvoidFloats())
        child_block_flow->MarkAllDescendantsWithFloatsForLayout(float_to_remove,
                                                                in_layout);
    }
  }
}

void LayoutBlockFlow::MarkSiblingsWithFloatsForLayout(
    LayoutBox* float_to_remove) {
  if (!floating_objects_)
    return;

  const FloatingObjectSet& floating_object_set = floating_objects_->Set();
  FloatingObjectSetIterator end = floating_object_set.end();

  for (LayoutObject* next = NextSibling(); next; next = next->NextSibling()) {
    if (!next->IsLayoutBlockFlow() ||
        (!float_to_remove && (next->IsFloatingOrOutOfFlowPositioned() ||
                              ToLayoutBlockFlow(next)->AvoidsFloats())))
      continue;

    LayoutBlockFlow* next_block = ToLayoutBlockFlow(next);
    for (FloatingObjectSetIterator it = floating_object_set.begin(); it != end;
         ++it) {
      LayoutBox* floating_box = (*it)->GetLayoutObject();
      if (float_to_remove && floating_box != float_to_remove)
        continue;
      if (next_block->ContainsFloat(floating_box))
        next_block->MarkAllDescendantsWithFloatsForLayout(floating_box);
    }
  }
}

LayoutUnit LayoutBlockFlow::GetClearDelta(LayoutBox* child,
                                          LayoutUnit logical_top) {
  // There is no need to compute clearance if we have no floats.
  if (!ContainsFloats())
    return LayoutUnit();

  // At least one float is present. We need to perform the clearance
  // computation.
  EClear clear = ResolvedClear(child->StyleRef(), StyleRef());
  LayoutUnit logical_bottom = LowestFloatLogicalBottom(clear);

  // We also clear floats if we are too big to sit on the same line as a float
  // (and wish to avoid floats by default).
  LayoutUnit result = clear != EClear::kNone
                          ? (logical_bottom - logical_top).ClampNegativeToZero()
                          : LayoutUnit();
  if (!result && child->AvoidsFloats()) {
    LayoutUnit new_logical_top = logical_top;
    LayoutRect border_box = child->BorderBoxRect();
    LayoutUnit child_logical_width_at_old_logical_top_offset =
        IsHorizontalWritingMode() ? border_box.Width() : border_box.Height();
    while (true) {
      LayoutUnit available_logical_width_at_new_logical_top_offset =
          AvailableLogicalWidthForAvoidingFloats(new_logical_top,
                                                 LogicalHeightForChild(*child));
      if (available_logical_width_at_new_logical_top_offset ==
          AvailableLogicalWidthForContent())
        return new_logical_top - logical_top;

      LogicalExtentComputedValues computed_values;
      child->LogicalExtentAfterUpdatingLogicalWidth(new_logical_top,
                                                    computed_values);
      LayoutUnit child_logical_width_at_new_logical_top_offset =
          computed_values.extent_;

      if (child_logical_width_at_new_logical_top_offset <=
          available_logical_width_at_new_logical_top_offset) {
        // Even though we may not be moving, if the logical width did shrink
        // because of the presence of new floats, then we need to force a
        // relayout as though we shifted. This happens because of the dynamic
        // addition of overhanging floats from previous siblings when negative
        // margins exist on a child (see the addOverhangingFloats call at the
        // end of collapseMargins).
        if (child_logical_width_at_old_logical_top_offset !=
            child_logical_width_at_new_logical_top_offset)
          child->SetChildNeedsLayout(kMarkOnlyThis);
        return new_logical_top - logical_top;
      }

      new_logical_top = NextFloatLogicalBottomBelowForBlock(new_logical_top);
      DCHECK_GE(new_logical_top, logical_top);
      if (new_logical_top < logical_top)
        break;
    }
    NOTREACHED();
  }
  return result;
}

void LayoutBlockFlow::CreateFloatingObjects() {
  floating_objects_ =
      std::make_unique<FloatingObjects>(this, IsHorizontalWritingMode());
}

void LayoutBlockFlow::WillBeDestroyed() {
  // Mark as being destroyed to avoid trouble with merges in removeChild().
  being_destroyed_ = true;

  // Make sure to destroy anonymous children first while they are still
  // connected to the rest of the tree, so that they will properly dirty line
  // boxes that they are removed from. Effects that do :before/:after only on
  // hover could crash otherwise.
  Children()->DestroyLeftoverChildren();

  // Destroy our continuation before anything other than anonymous children.
  // The reason we don't destroy it before anonymous children is that they may
  // have continuations of their own that are anonymous children of our
  // continuation.
  LayoutBoxModelObject* continuation = Continuation();
  if (continuation) {
    continuation->Destroy();
    SetContinuation(nullptr);
  }

  if (!DocumentBeingDestroyed()) {
    // TODO(mstensho): figure out if we need this. We have no test coverage for
    // it. It looks like all line boxes have been removed at this point.
    if (FirstLineBox()) {
      // If we are an anonymous block, then our line boxes might have children
      // that will outlast this block. In the non-anonymous block case those
      // children will be destroyed by the time we return from this function.
      if (IsAnonymousBlock()) {
        for (InlineFlowBox* box : *LineBoxes()) {
          while (InlineBox* child_box = box->FirstChild())
            child_box->Remove();
        }
      }
    }
  }

  line_boxes_.DeleteLineBoxes();

  LayoutBlock::WillBeDestroyed();
}

void LayoutBlockFlow::StyleWillChange(StyleDifference diff,
                                      const ComputedStyle& new_style) {
  const ComputedStyle* old_style = Style();
  can_propagate_float_into_sibling_ =
      old_style ? !IsFloatingOrOutOfFlowPositioned() && !AvoidsFloats() : false;
  if (old_style && Parent() && diff.NeedsFullLayout() &&
      old_style->GetPosition() != new_style.GetPosition() && ContainsFloats() &&
      !IsFloating() && !IsOutOfFlowPositioned() &&
      new_style.HasOutOfFlowPosition())
    MarkAllDescendantsWithFloatsForLayout();

  LayoutBlock::StyleWillChange(diff, new_style);
}

DISABLE_CFI_PERF
void LayoutBlockFlow::StyleDidChange(StyleDifference diff,
                                     const ComputedStyle* old_style) {
  bool had_self_painting_layer = HasSelfPaintingLayer();
  LayoutBlock::StyleDidChange(diff, old_style);

  // After our style changed, if we lose our ability to propagate floats into
  // next sibling blocks, then we need to find the top most parent containing
  // that overhanging float and then mark its descendants with floats for layout
  // and clear all floats from its next sibling blocks that exist in our
  // floating objects list. See crbug.com/56299 and crbug.com/62875.
  bool can_propagate_float_into_sibling =
      !IsFloatingOrOutOfFlowPositioned() && !AvoidsFloats();
  bool sibling_float_propagation_changed =
      diff.NeedsFullLayout() && can_propagate_float_into_sibling_ &&
      !can_propagate_float_into_sibling && HasOverhangingFloats();

  // When this object's self-painting layer status changed, we should update
  // FloatingObjects::shouldPaint() flags for descendant overhanging floats in
  // ancestors.
  bool needs_update_ancestor_float_object_should_paint_flags = false;
  if (HasSelfPaintingLayer() != had_self_painting_layer &&
      HasOverhangingFloats()) {
    SetNeedsLayout(layout_invalidation_reason::kStyleChange);
    if (had_self_painting_layer)
      MarkAllDescendantsWithFloatsForLayout();
    else
      needs_update_ancestor_float_object_should_paint_flags = true;
  }

  if (sibling_float_propagation_changed ||
      needs_update_ancestor_float_object_should_paint_flags) {
    LayoutBlockFlow* parent_block_flow = this;
    const FloatingObjectSet& floating_object_set = floating_objects_->Set();
    FloatingObjectSetIterator end = floating_object_set.end();

    for (LayoutObject* curr = Parent(); curr && !curr->IsLayoutView();
         curr = curr->Parent()) {
      if (curr->IsLayoutBlockFlow()) {
        LayoutBlockFlow* curr_block = ToLayoutBlockFlow(curr);

        if (curr_block->HasOverhangingFloats()) {
          for (FloatingObjectSetIterator it = floating_object_set.begin();
               it != end; ++it) {
            LayoutBox* layout_box = (*it)->GetLayoutObject();
            if (curr_block->HasOverhangingFloat(layout_box)) {
              parent_block_flow = curr_block;
              break;
            }
          }
        }
      }
    }

    parent_block_flow->MarkAllDescendantsWithFloatsForLayout();
    if (sibling_float_propagation_changed)
      parent_block_flow->MarkSiblingsWithFloatsForLayout();
  }

  if (diff.NeedsFullLayout() || !old_style)
    CreateOrDestroyMultiColumnFlowThreadIfNeeded(old_style);
  if (old_style) {
    if (LayoutMultiColumnFlowThread* flow_thread = MultiColumnFlowThread()) {
      if (!StyleRef().ColumnRuleEquivalent(*old_style)) {
        // Column rules are painted by anonymous column set children of the
        // multicol container. We need to notify them.
        flow_thread->ColumnRuleStyleDidChange();
      }
    }
  }
}

void LayoutBlockFlow::UpdateBlockChildDirtyBitsBeforeLayout(
    bool relayout_children,
    LayoutBox& child) {
  if (child.IsLayoutMultiColumnSpannerPlaceholder())
    ToLayoutMultiColumnSpannerPlaceholder(child)
        .MarkForLayoutIfObjectInFlowThreadNeedsLayout();
  LayoutBlock::UpdateBlockChildDirtyBitsBeforeLayout(relayout_children, child);
}

void LayoutBlockFlow::UpdateStaticInlinePositionForChild(
    LayoutBox& child,
    LayoutUnit logical_top,
    IndentTextOrNot indent_text) {
  if (child.StyleRef().IsOriginalDisplayInlineType())
    SetStaticInlinePositionForChild(
        child, StartAlignedOffsetForLine(logical_top, indent_text));
  else
    SetStaticInlinePositionForChild(child, StartOffsetForContent());
}

void LayoutBlockFlow::SetStaticInlinePositionForChild(
    LayoutBox& child,
    LayoutUnit inline_position) {
  child.Layer()->SetStaticInlinePosition(inline_position);
}

LayoutInline* LayoutBlockFlow::InlineElementContinuation() const {
  LayoutBoxModelObject* continuation = Continuation();
  return continuation && continuation->IsInline() ? ToLayoutInline(continuation)
                                                  : nullptr;
}

bool LayoutBlockFlow::NeedsAnonymousInlineWrapper() const {
  // If ::first-line has background properties, create an anonymous inline
  // wrapper. This helps paint code to handle it.
  DCHECK(RuntimeEnabledFeatures::LayoutNGEnabled());
  if (!GetDocument().GetStyleEngine().UsesFirstLineRules())
    return false;
  const ComputedStyle& first_line_style = FirstLineStyleRef();
  const ComputedStyle& style = StyleRef();
  if (&first_line_style == &style)
    return false;
  // We need an anonymous inline wrapper only if ::first-line has different
  // background, but excessive anonymous inline will not harm.
  return first_line_style.HasBackground();
}

void LayoutBlockFlow::AddChild(LayoutObject* new_child,
                               LayoutObject* before_child) {
  if (LayoutMultiColumnFlowThread* flow_thread = MultiColumnFlowThread()) {
    if (before_child == flow_thread)
      before_child = flow_thread->FirstChild();
    DCHECK(!before_child || before_child->IsDescendantOf(flow_thread));
    flow_thread->AddChild(new_child, before_child);
    return;
  }

  if (before_child && before_child->Parent() != this) {
    AddChildBeforeDescendant(new_child, before_child);
    return;
  }

  bool made_boxes_non_inline = false;

  // A block has to either have all of its children inline, or all of its
  // children as blocks.
  // So, if our children are currently inline and a block child has to be
  // inserted, we move all our inline children into anonymous block boxes.
  bool child_is_block_level =
      !new_child->IsInline() && !new_child->IsFloatingOrOutOfFlowPositioned();

  if (ChildrenInline()) {
    if (child_is_block_level) {
      // Wrap the inline content in anonymous blocks, to allow for the new block
      // child to be inserted.
      MakeChildrenNonInline(before_child);
      made_boxes_non_inline = true;

      if (before_child && before_child->Parent() != this) {
        before_child = before_child->Parent();
        DCHECK(before_child->IsAnonymousBlock());
        DCHECK_EQ(before_child->Parent(), this);
      }
    } else if (UNLIKELY(RuntimeEnabledFeatures::LayoutNGEnabled() &&
                        IsLayoutNGContainingBlock(this) &&
                        NeedsAnonymousInlineWrapper())) {
      LayoutObject* after_child =
          before_child ? before_child->PreviousSibling() : LastChild();
      if (after_child && after_child->IsAnonymous() &&
          after_child->IsLayoutInline()) {
        after_child->AddChild(new_child);
        return;
      }
      LayoutInline* new_wrapper =
          LayoutInline::CreateAnonymousForFirstLine(&GetDocument());
      new_wrapper->SetStyle(ComputedStyle::CreateAnonymousStyleWithDisplay(
          StyleRef(), EDisplay::kInline));
      LayoutBox::AddChild(new_wrapper, before_child);
      new_wrapper->AddChild(new_child);
      return;
    }
  } else if (!child_is_block_level) {
    // This block has block children. We may want to put the new child into an
    // anomyous block. Floats and out-of-flow children may live among either
    // block or inline children, so for such children, only put them inside an
    // anonymous block if one already exists. If the child is inline, on the
    // other hand, we *have to* put it inside an anonymous block, so create a
    // new one if there is none for us there already.
    LayoutObject* after_child =
        before_child ? before_child->PreviousSibling() : LastChild();

    if (after_child && after_child->IsAnonymousBlock()) {
      after_child->AddChild(new_child);
      return;
    }

    // LayoutNGListMarker is out-of-flow for the tree building purpose, and that
    // is not inline level, but IsInline().
    if (new_child->IsInline() && !new_child->IsLayoutNGListMarker()) {
      // No suitable existing anonymous box - create a new one.
      LayoutBlockFlow* new_block = ToLayoutBlockFlow(CreateAnonymousBlock());
      LayoutBox::AddChild(new_block, before_child);
      // Reparent adjacent floating or out-of-flow siblings to the new box.
      new_block->ReparentPrecedingFloatingOrOutOfFlowSiblings();
      new_block->AddChild(new_child);
      new_block->ReparentSubsequentFloatingOrOutOfFlowSiblings();
      return;
    }
  }

  // Skip the LayoutBlock override, since that one deals with anonymous child
  // insertion in a way that isn't sufficient for us, and can only cause trouble
  // at this point.
  LayoutBox::AddChild(new_child, before_child);

  if (made_boxes_non_inline && Parent() && IsAnonymousBlock() &&
      Parent()->IsLayoutBlock()) {
    ToLayoutBlock(Parent())->RemoveLeftoverAnonymousBlock(this);
    // |this| may be dead now.
  }
}

static bool IsMergeableAnonymousBlock(const LayoutBlockFlow* block) {
  return block->IsAnonymousBlock() && !block->Continuation() &&
         !block->BeingDestroyed() && !block->IsRubyRun() &&
         !block->IsRubyBase();
}

void LayoutBlockFlow::RemoveChild(LayoutObject* old_child) {
  // No need to waste time in merging or removing empty anonymous blocks.
  // We can just bail out if our document is getting destroyed.
  if (DocumentBeingDestroyed()) {
    LayoutBox::RemoveChild(old_child);
    return;
  }

  // If this child is a block, and if our previous and next siblings are both
  // anonymous blocks with inline content, then we can go ahead and fold the
  // inline content back together. If only one of the siblings is such an
  // anonymous blocks, check if the other sibling (and any of *its* siblings)
  // are floating or out-of-flow positioned. In that case, they should be moved
  // into the anonymous block.
  LayoutObject* prev = old_child->PreviousSibling();
  LayoutObject* next = old_child->NextSibling();
  bool merged_anonymous_blocks = false;
  if (prev && next && !old_child->IsInline() &&
      !old_child->VirtualContinuation()) {
    if (prev->IsLayoutBlockFlow() && next->IsLayoutBlockFlow() &&
        ToLayoutBlockFlow(prev)->MergeSiblingContiguousAnonymousBlock(
            ToLayoutBlockFlow(next))) {
      merged_anonymous_blocks = true;
      next = nullptr;
    } else if (prev->IsLayoutBlockFlow() &&
               IsMergeableAnonymousBlock(ToLayoutBlockFlow(prev))) {
      // The previous sibling is anonymous. Scan the next siblings and reparent
      // any floating or out-of-flow positioned objects into the end of the
      // previous anonymous block.
      while (next && next->IsFloatingOrOutOfFlowPositioned()) {
        LayoutObject* sibling = next->NextSibling();
        MoveChildTo(ToLayoutBlockFlow(prev), next, nullptr, false);
        next = sibling;
      }
    } else if (next->IsLayoutBlockFlow() &&
               IsMergeableAnonymousBlock(ToLayoutBlockFlow(next))) {
      // The next sibling is anonymous. Scan the previous siblings and reparent
      // any floating or out-of-flow positioned objects into the start of the
      // next anonymous block.
      while (prev && prev->IsFloatingOrOutOfFlowPositioned()) {
        LayoutObject* sibling = prev->PreviousSibling();
        MoveChildTo(ToLayoutBlockFlow(next), prev,
                    ToLayoutBlockFlow(next)->FirstChild(), false);
        prev = sibling;
      }
    }
  }

  LayoutBlock::RemoveChild(old_child);

  LayoutObject* child = prev ? prev : next;
  if (child && child->IsLayoutBlockFlow() && !child->PreviousSibling() &&
      !child->NextSibling()) {
    // If the removal has knocked us down to containing only a single anonymous
    // box we can go ahead and pull the content right back up into our
    // box.
    if (merged_anonymous_blocks ||
        IsMergeableAnonymousBlock(ToLayoutBlockFlow(child)))
      CollapseAnonymousBlockChild(ToLayoutBlockFlow(child));
  }

  if (!FirstChild()) {
    // If this was our last child be sure to clear out our line boxes.
    if (ChildrenInline())
      DeleteLineBoxTree();

    // If we are an empty anonymous block in the continuation chain,
    // we need to remove ourself and fix the continuation chain.
    if (!BeingDestroyed() && IsAnonymousBlockContinuation() &&
        !old_child->IsListMarker()) {
      LayoutObject* containing_block_ignoring_anonymous = ContainingBlock();
      while (containing_block_ignoring_anonymous &&
             containing_block_ignoring_anonymous->IsAnonymous())
        containing_block_ignoring_anonymous =
            containing_block_ignoring_anonymous->ContainingBlock();
      for (LayoutObject* curr = this; curr;
           curr =
               curr->PreviousInPreOrder(containing_block_ignoring_anonymous)) {
        if (curr->VirtualContinuation() != this)
          continue;

        // Found our previous continuation. We just need to point it to
        // |this|'s next continuation.
        LayoutBoxModelObject* next_continuation = Continuation();
        if (curr->IsLayoutInline())
          ToLayoutInline(curr)->SetContinuation(next_continuation);
        else if (curr->IsLayoutBlockFlow())
          ToLayoutBlockFlow(curr)->SetContinuation(next_continuation);
        else
          NOTREACHED();

        break;
      }
      SetContinuation(nullptr);
      Destroy();
    }
  } else if (!BeingDestroyed() &&
             !old_child->IsFloatingOrOutOfFlowPositioned() &&
             !old_child->IsAnonymousBlock()) {
    // If the child we're removing means that we can now treat all children as
    // inline without the need for anonymous blocks, then do that.
    MakeChildrenInlineIfPossible();
  }
}

void LayoutBlockFlow::MoveAllChildrenIncludingFloatsTo(
    LayoutBlock* to_block,
    bool full_remove_insert) {
  LayoutBlockFlow* to_block_flow = ToLayoutBlockFlow(to_block);

  DCHECK(full_remove_insert ||
         to_block_flow->ChildrenInline() == ChildrenInline());

  // When a portion of the layout tree is being detached, anonymous blocks
  // will be combined as their children are deleted. In this process, the
  // anonymous block later in the tree is merged into the one preceding it.
  // It can happen that the later block (this) contains floats that the
  // previous block (toBlockFlow) did not contain, and thus are not in the
  // floating objects list for toBlockFlow. This can result in toBlockFlow
  // containing floats that are not in it's floating objects list, but are in
  // the floating objects lists of siblings and parents. This can cause problems
  // when the float itself is deleted, since the deletion code assumes that if a
  // float is not in it's containing block's floating objects list, it isn't in
  // any floating objects list. In order to preserve this condition (removing it
  // has serious performance implications), we need to copy the floating objects
  // from the old block (this) to the new block (toBlockFlow).
  // The float's metrics will likely all be wrong, but since toBlockFlow is
  // already marked for layout, this will get fixed before anything gets
  // displayed.
  // See bug https://code.google.com/p/chromium/issues/detail?id=230907
  if (floating_objects_) {
    if (!to_block_flow->floating_objects_)
      to_block_flow->CreateFloatingObjects();

    const FloatingObjectSet& from_floating_object_set =
        floating_objects_->Set();
    FloatingObjectSetIterator end = from_floating_object_set.end();

    for (FloatingObjectSetIterator it = from_floating_object_set.begin();
         it != end; ++it) {
      const FloatingObject& floating_object = *it->get();

      // Don't insert the object again if it's already in the list
      if (to_block_flow->ContainsFloat(floating_object.GetLayoutObject()))
        continue;

      to_block_flow->floating_objects_->Add(floating_object.UnsafeClone());
    }
  }
  MoveAllChildrenTo(to_block_flow, full_remove_insert);
}

void LayoutBlockFlow::ChildBecameFloatingOrOutOfFlow(LayoutBox* child) {
  MakeChildrenInlineIfPossible();

  // Reparent the child to an adjacent anonymous block if one is available.
  LayoutObject* prev = child->PreviousSibling();
  if (prev && prev->IsAnonymousBlock() && prev->IsLayoutBlockFlow()) {
    LayoutBlockFlow* new_container = ToLayoutBlockFlow(prev);
    MoveChildTo(new_container, child, nullptr, false);
    // The anonymous block we've moved to may now be adjacent to former siblings
    // of ours that it can contain also.
    new_container->ReparentSubsequentFloatingOrOutOfFlowSiblings();
    return;
  }
  LayoutObject* next = child->NextSibling();
  if (next && next->IsAnonymousBlock() && next->IsLayoutBlockFlow()) {
    LayoutBlockFlow* new_container = ToLayoutBlockFlow(next);
    MoveChildTo(new_container, child, new_container->FirstChild(), false);
  }
}

void LayoutBlockFlow::CollapseAnonymousBlockChild(LayoutBlockFlow* child) {
  // It's possible that this block's destruction may have been triggered by the
  // child's removal. Just bail if the anonymous child block is already being
  // destroyed. See crbug.com/282088
  if (child->BeingDestroyed())
    return;
  if (child->Continuation())
    return;
  // Ruby elements use anonymous wrappers for ruby runs and ruby bases by
  // design, so we don't remove them.
  if (child->IsRubyRun() || child->IsRubyBase())
    return;
  SetNeedsLayoutAndPrefWidthsRecalcAndFullPaintInvalidation(
      layout_invalidation_reason::kChildAnonymousBlockChanged);

  child->MoveAllChildrenTo(this, child->NextSibling(), child->HasLayer());
  // If we make an object's children inline we are going to frustrate any future
  // attempts to remove floats from its children's float-lists before the next
  // layout happens so clear down all the floatlists now - they will be rebuilt
  // at layout.
  if (child->ChildrenInline())
    RemoveFloatingObjectsFromDescendants();
  SetChildrenInline(child->ChildrenInline());

  Children()->RemoveChildNode(this, child, child->HasLayer());
  child->Destroy();
}

bool LayoutBlockFlow::MergeSiblingContiguousAnonymousBlock(
    LayoutBlockFlow* sibling_that_may_be_deleted) {
  // Note: |this| and |siblingThatMayBeDeleted| may not be adjacent siblings at
  // this point. There may be an object between them which is about to be
  // removed.

  if (!IsMergeableAnonymousBlock(this) ||
      !IsMergeableAnonymousBlock(sibling_that_may_be_deleted))
    return false;

  SetNeedsLayoutAndPrefWidthsRecalcAndFullPaintInvalidation(
      layout_invalidation_reason::kAnonymousBlockChange);

  // If the inlineness of children of the two block don't match, we'd need
  // special code here (but there should be no need for it).
  DCHECK_EQ(sibling_that_may_be_deleted->ChildrenInline(), ChildrenInline());
  // Take all the children out of the |next| block and put them in
  // the |prev| block.
  sibling_that_may_be_deleted->MoveAllChildrenIncludingFloatsTo(
      this, sibling_that_may_be_deleted->HasLayer() || HasLayer());
  // Delete the now-empty block's lines and nuke it.
  sibling_that_may_be_deleted->DeleteLineBoxTree();
  sibling_that_may_be_deleted->Destroy();
  return true;
}

void LayoutBlockFlow::ReparentSubsequentFloatingOrOutOfFlowSiblings() {
  if (!Parent() || !Parent()->IsLayoutBlockFlow())
    return;
  if (BeingDestroyed() || DocumentBeingDestroyed())
    return;
  LayoutBlockFlow* parent_block_flow = ToLayoutBlockFlow(Parent());
  LayoutObject* child = NextSibling();
  while (child && child->IsFloatingOrOutOfFlowPositioned()) {
    LayoutObject* sibling = child->NextSibling();
    parent_block_flow->MoveChildTo(this, child, nullptr, false);
    child = sibling;
  }

  if (LayoutObject* next = NextSibling()) {
    if (next->IsLayoutBlockFlow())
      MergeSiblingContiguousAnonymousBlock(ToLayoutBlockFlow(next));
  }
}

void LayoutBlockFlow::ReparentPrecedingFloatingOrOutOfFlowSiblings() {
  if (!Parent() || !Parent()->IsLayoutBlockFlow())
    return;
  if (BeingDestroyed() || DocumentBeingDestroyed())
    return;
  LayoutBlockFlow* parent_block_flow = ToLayoutBlockFlow(Parent());
  LayoutObject* child = PreviousSibling();
  while (child && child->IsFloatingOrOutOfFlowPositioned()) {
    LayoutObject* sibling = child->PreviousSibling();
    parent_block_flow->MoveChildTo(this, child, FirstChild(), false);
    child = sibling;
  }
}

void LayoutBlockFlow::MakeChildrenInlineIfPossible() {
  // Collapsing away anonymous wrappers isn't relevant for the children of
  // anonymous blocks, unless they are ruby bases.
  if (IsAnonymousBlock() && !IsRubyBase())
    return;

  Vector<LayoutBlockFlow*, 3> blocks_to_remove;
  for (LayoutObject* child = FirstChild(); child;
       child = child->NextSibling()) {
    if (child->IsFloating())
      continue;
    if (child->IsOutOfFlowPositioned())
      continue;

    // There are still block children in the container, so any anonymous
    // wrappers are still needed.
    if (!child->IsAnonymousBlock() || !child->IsLayoutBlockFlow())
      return;
    // If one of the children is being destroyed then it is unsafe to clean up
    // anonymous wrappers as the
    // entire branch may be being destroyed.
    if (ToLayoutBlockFlow(child)->BeingDestroyed())
      return;
    // We can't remove anonymous wrappers if they contain continuations as this
    // means there are block children present.
    if (ToLayoutBlockFlow(child)->Continuation())
      return;
    // We are only interested in removing anonymous wrappers if there are inline
    // siblings underneath them.
    if (!child->ChildrenInline())
      return;
    // Ruby elements use anonymous wrappers for ruby runs and ruby bases by
    // design, so we don't remove them.
    if (child->IsRubyRun() || child->IsRubyBase())
      return;

    blocks_to_remove.push_back(ToLayoutBlockFlow(child));
  }

  // If we make an object's children inline we are going to frustrate any future
  // attempts to remove floats from its children's float-lists before the next
  // layout happens so clear down all the floatlists now - they will be rebuilt
  // at layout.
  RemoveFloatingObjectsFromDescendants();

  for (LayoutBlockFlow* child : blocks_to_remove)
    CollapseAnonymousBlockChild(child);
  SetChildrenInline(true);
}

static void GetInlineRun(LayoutObject* start,
                         LayoutObject* boundary,
                         LayoutObject*& inline_run_start,
                         LayoutObject*& inline_run_end) {
  // Beginning at |start| we find the largest contiguous run of inlines that
  // we can.  We denote the run with start and end points, |inlineRunStart|
  // and |inlineRunEnd|.  Note that these two values may be the same if
  // we encounter only one inline.
  //
  // We skip any non-inlines we encounter as long as we haven't found any
  // inlines yet.
  //
  // |boundary| indicates a non-inclusive boundary point.  Regardless of whether
  // |boundary| is inline or not, we will not include it in a run with inlines
  // before it. It's as though we encountered a non-inline.

  // Start by skipping as many non-inlines as we can.
  LayoutObject* curr = start;

  // LayoutNGListMarker is out-of-flow for the tree building purpose. Skip here
  // because it's the first child.
  if (curr && curr->IsLayoutNGListMarker())
    curr = curr->NextSibling();

  bool saw_inline;
  do {
    while (curr &&
           !(curr->IsInline() || curr->IsFloatingOrOutOfFlowPositioned()))
      curr = curr->NextSibling();

    inline_run_start = inline_run_end = curr;

    if (!curr)
      return;  // No more inline children to be found.

    saw_inline = curr->IsInline();

    curr = curr->NextSibling();
    while (curr &&
           (curr->IsInline() || curr->IsFloatingOrOutOfFlowPositioned()) &&
           (curr != boundary)) {
      inline_run_end = curr;
      if (curr->IsInline())
        saw_inline = true;
      curr = curr->NextSibling();
    }
  } while (!saw_inline);
}

void LayoutBlockFlow::MakeChildrenNonInline(LayoutObject* insertion_point) {
  // makeChildrenNonInline takes a block whose children are *all* inline and it
  // makes sure that inline children are coalesced under anonymous blocks.
  // If |insertionPoint| is defined, then it represents the insertion point for
  // the new block child that is causing us to have to wrap all the inlines.
  // This means that we cannot coalesce inlines before |insertionPoint| with
  // inlines following |insertionPoint|, because the new child is going to be
  // inserted in between the inlines, splitting them.
  DCHECK(!IsInline() || IsAtomicInlineLevel());
  DCHECK(!insertion_point || insertion_point->Parent() == this);

  SetChildrenInline(false);

  LayoutObject* child = FirstChild();
  if (!child)
    return;

  DeleteLineBoxTree();

  while (child) {
    LayoutObject* inline_run_start;
    LayoutObject* inline_run_end;
    GetInlineRun(child, insertion_point, inline_run_start, inline_run_end);

    if (!inline_run_start)
      break;

    child = inline_run_end->NextSibling();

    LayoutBlock* block = CreateAnonymousBlock();
    Children()->InsertChildNode(this, block, inline_run_start);
    MoveChildrenTo(block, inline_run_start, child);
  }

#if DCHECK_IS_ON()
  for (LayoutObject* c = FirstChild(); c; c = c->NextSibling())
    DCHECK(!c->IsInline() || c->IsLayoutNGListMarker());
#endif

  SetShouldDoFullPaintInvalidation();
}

void LayoutBlockFlow::ChildBecameNonInline(LayoutObject*) {
  MakeChildrenNonInline();
  if (IsAnonymousBlock() && Parent() && Parent()->IsLayoutBlock())
    ToLayoutBlock(Parent())->RemoveLeftoverAnonymousBlock(this);
  // |this| may be dead here
}

void LayoutBlockFlow::ClearFloats(EClear clear) {
  PlaceNewFloats(LogicalHeight());
  // set y position
  LayoutUnit new_y = LowestFloatLogicalBottom(clear);
  if (Size().Height() < new_y)
    SetLogicalHeight(new_y);
}

bool LayoutBlockFlow::ContainsFloat(LayoutBox* layout_box) const {
  return floating_objects_ &&
         floating_objects_->Set().Contains<FloatingObjectHashTranslator>(
             layout_box);
}

void LayoutBlockFlow::RemoveFloatingObjects() {
  if (!floating_objects_)
    return;

  MarkSiblingsWithFloatsForLayout();

  floating_objects_->Clear();
}

LayoutPoint LayoutBlockFlow::FlipFloatForWritingModeForChild(
    const FloatingObject& child,
    const LayoutPoint& point) const {
  if (!StyleRef().IsFlippedBlocksWritingMode())
    return point;

  // This is similar to LayoutBox::flipForWritingModeForChild. We have to
  // subtract out our left offsets twice, since it's going to get added back in.
  // We hide this complication here so that the calling code looks normal for
  // the unflipped case.
  return LayoutPoint(point.X() + Size().Width() -
                         child.GetLayoutObject()->Size().Width() -
                         2 * XPositionForFloatIncludingMargin(child),
                     point.Y());
}

LayoutUnit LayoutBlockFlow::LogicalLeftOffsetForPositioningFloat(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit* height_remaining) const {
  LayoutUnit offset = fixed_offset;
  if (floating_objects_ && floating_objects_->HasLeftObjects())
    offset = floating_objects_->LogicalLeftOffsetForPositioningFloat(
        fixed_offset, logical_top, height_remaining);
  return AdjustLogicalLeftOffsetForLine(offset, kDoNotIndentText);
}

LayoutUnit LayoutBlockFlow::LogicalRightOffsetForPositioningFloat(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit* height_remaining) const {
  LayoutUnit offset = fixed_offset;
  if (floating_objects_ && floating_objects_->HasRightObjects())
    offset = floating_objects_->LogicalRightOffsetForPositioningFloat(
        fixed_offset, logical_top, height_remaining);
  return AdjustLogicalRightOffsetForLine(offset, kDoNotIndentText);
}

LayoutUnit LayoutBlockFlow::AdjustLogicalLeftOffsetForLine(
    LayoutUnit offset_from_floats,
    IndentTextOrNot apply_text_indent) const {
  LayoutUnit left = offset_from_floats;

  if (apply_text_indent == kIndentText && StyleRef().IsLeftToRightDirection())
    left += TextIndentOffset();

  return left;
}

LayoutUnit LayoutBlockFlow::AdjustLogicalRightOffsetForLine(
    LayoutUnit offset_from_floats,
    IndentTextOrNot apply_text_indent) const {
  LayoutUnit right = offset_from_floats;

  if (apply_text_indent == kIndentText && !StyleRef().IsLeftToRightDirection())
    right -= TextIndentOffset();

  return right;
}

LayoutPoint LayoutBlockFlow::ComputeLogicalLocationForFloat(
    const FloatingObject& floating_object,
    LayoutUnit logical_top_offset) const {
  LayoutBox* child_box = floating_object.GetLayoutObject();
  LayoutUnit logical_left_offset =
      LogicalLeftOffsetForContent();  // Constant part of left offset.
  LayoutUnit logical_right_offset;    // Constant part of right offset.
  logical_right_offset = LogicalRightOffsetForContent();

  LayoutUnit float_logical_width = std::min(
      LogicalWidthForFloat(floating_object),
      logical_right_offset - logical_left_offset);  // The width we look for.

  LayoutUnit float_logical_left;

  if (ResolvedFloating(child_box->StyleRef(), StyleRef()) == EFloat::kLeft) {
    LayoutUnit height_remaining_left = LayoutUnit(1);
    LayoutUnit height_remaining_right = LayoutUnit(1);
    float_logical_left = LogicalLeftOffsetForPositioningFloat(
        logical_top_offset, logical_left_offset, &height_remaining_left);
    while (LogicalRightOffsetForPositioningFloat(logical_top_offset,
                                                 logical_right_offset,
                                                 &height_remaining_right) -
               float_logical_left <
           float_logical_width) {
      logical_top_offset +=
          std::min<LayoutUnit>(height_remaining_left, height_remaining_right);
      float_logical_left = LogicalLeftOffsetForPositioningFloat(
          logical_top_offset, logical_left_offset, &height_remaining_left);
    }
    float_logical_left =
        std::max(logical_left_offset - BorderAndPaddingLogicalLeft(),
                 float_logical_left);
  } else {
    LayoutUnit height_remaining_left = LayoutUnit(1);
    LayoutUnit height_remaining_right = LayoutUnit(1);
    float_logical_left = LogicalRightOffsetForPositioningFloat(
        logical_top_offset, logical_right_offset, &height_remaining_right);
    while (float_logical_left - LogicalLeftOffsetForPositioningFloat(
                                    logical_top_offset, logical_left_offset,
                                    &height_remaining_left) <
           float_logical_width) {
      logical_top_offset +=
          std::min(height_remaining_left, height_remaining_right);
      float_logical_left = LogicalRightOffsetForPositioningFloat(
          logical_top_offset, logical_right_offset, &height_remaining_right);
    }
    // Use the original width of the float here, since the local variable
    // |floatLogicalWidth| was capped to the available line width. See
    // fast/block/float/clamped-right-float.html.
    float_logical_left -= LogicalWidthForFloat(floating_object);
  }

  return LayoutPoint(float_logical_left, logical_top_offset);
}

FloatingObject* LayoutBlockFlow::InsertFloatingObject(LayoutBox& float_box) {
  DCHECK(float_box.IsFloating());

  // Create the list of special objects if we don't aleady have one
  if (!floating_objects_) {
    CreateFloatingObjects();
  } else {
    // Don't insert the object again if it's already in the list
    const FloatingObjectSet& floating_object_set = floating_objects_->Set();
    FloatingObjectSetIterator it =
        floating_object_set.Find<FloatingObjectHashTranslator>(&float_box);
    if (it != floating_object_set.end())
      return it->get();
  }

  // Create the special object entry & append it to the list
  EFloat f = ResolvedFloating(float_box.StyleRef(), StyleRef());
  DCHECK(f == EFloat::kLeft || f == EFloat::kRight);
  FloatingObject::Type type = f == EFloat::kLeft ? FloatingObject::kFloatLeft
                                                 : FloatingObject::kFloatRight;
  std::unique_ptr<FloatingObject> new_obj =
      FloatingObject::Create(&float_box, type);
  return floating_objects_->Add(std::move(new_obj));
}

void LayoutBlockFlow::RemoveFloatingObject(LayoutBox* float_box) {
  if (floating_objects_) {
    const FloatingObjectSet& floating_object_set = floating_objects_->Set();
    FloatingObjectSetIterator it =
        floating_object_set.Find<FloatingObjectHashTranslator>(float_box);
    if (it != floating_object_set.end()) {
      FloatingObject& floating_object = *it->get();
      if (ChildrenInline()) {
        LayoutUnit logical_top = LogicalTopForFloat(floating_object);
        LayoutUnit logical_bottom = LogicalBottomForFloat(floating_object);

        // Fix for https://bugs.webkit.org/show_bug.cgi?id=54995.
        if (logical_bottom < 0 || logical_bottom < logical_top ||
            logical_top == LayoutUnit::Max()) {
          logical_bottom = LayoutUnit::Max();
        } else {
          // Special-case zero- and less-than-zero-height floats: those don't
          // touch the line that they're on, but it still needs to be dirtied.
          // This is accomplished by pretending they have a height of 1.
          logical_bottom = std::max(logical_bottom, logical_top + 1);
        }
        if (floating_object.OriginatingLine()) {
          if (!SelfNeedsLayout()) {
            DCHECK(
                floating_object.OriginatingLine()->GetLineLayoutItem().IsEqual(
                    this));
            floating_object.OriginatingLine()->MarkDirty();
          }
#if DCHECK_IS_ON()
          floating_object.SetOriginatingLine(nullptr);
#endif
        }
        MarkLinesDirtyInBlockRange(LayoutUnit(), logical_bottom);
      }
      floating_objects_->Remove(&floating_object);
    }
  }
}

void LayoutBlockFlow::RemoveFloatingObjectsBelow(FloatingObject* last_float,
                                                 LayoutUnit logical_offset) {
  if (!ContainsFloats())
    return;

  const FloatingObjectSet& floating_object_set = floating_objects_->Set();
  FloatingObject* curr = floating_object_set.back().get();
  while (curr != last_float &&
         (!curr->IsPlaced() || LogicalTopForFloat(*curr) >= logical_offset)) {
    floating_objects_->Remove(curr);
    if (floating_object_set.IsEmpty())
      break;
    curr = floating_object_set.back().get();
  }
}

bool LayoutBlockFlow::PlaceNewFloats(LayoutUnit logical_top_margin_edge,
                                     LineWidth* width) {
  if (!floating_objects_)
    return false;

  const FloatingObjectSet& floating_object_set = floating_objects_->Set();
  if (floating_object_set.IsEmpty())
    return false;

  // If all floats have already been positioned, then we have no work to do.
  if (floating_object_set.back()->IsPlaced())
    return false;

  // Move backwards through our floating object list until we find a float that
  // has already been positioned. Then we'll be able to move forward,
  // positioning all of the new floats that need it.
  FloatingObjectSetIterator it = floating_object_set.end();
  --it;  // Go to last item.
  FloatingObjectSetIterator begin = floating_object_set.begin();
  FloatingObject* last_placed_floating_object = nullptr;
  while (it != begin) {
    --it;
    if ((*it)->IsPlaced()) {
      last_placed_floating_object = it->get();
      ++it;
      break;
    }
  }

  // The float cannot start above the top position of the last positioned float.
  if (last_placed_floating_object) {
    logical_top_margin_edge =
        std::max(logical_top_margin_edge,
                 LogicalTopForFloat(*last_placed_floating_object));
  }

  FloatingObjectSetIterator end = floating_object_set.end();
  // Now walk through the set of unpositioned floats and place them.
  for (; it != end; ++it) {
    FloatingObject& floating_object = *it->get();
    // The containing block is responsible for positioning floats, so if we have
    // unplaced floats in our list that come from somewhere else, we have a bug.
    DCHECK_EQ(floating_object.GetLayoutObject()->ContainingBlock(), this);

    logical_top_margin_edge =
        PositionAndLayoutFloat(floating_object, logical_top_margin_edge);

    floating_objects_->AddPlacedObject(floating_object);

    if (width)
      width->ShrinkAvailableWidthForNewFloatIfNeeded(floating_object);
  }
  return true;
}

LayoutUnit LayoutBlockFlow::PositionAndLayoutFloat(
    FloatingObject& floating_object,
    LayoutUnit logical_top_margin_edge) {
  // Once a float has been placed, we cannot update its position, or the float
  // interval tree will be out of sync with reality. This may in turn lead to
  // objects being used after they have been deleted.
  CHECK(!floating_object.IsPlaced());

  LayoutBox& child = *floating_object.GetLayoutObject();

  // FIXME Investigate if this can be removed. crbug.com/370006
  child.SetShouldCheckForPaintInvalidation();

  logical_top_margin_edge = std::max(
      logical_top_margin_edge,
      LowestFloatLogicalBottom(ResolvedClear(child.StyleRef(), StyleRef())));

  bool is_paginated = View()->GetLayoutState()->IsPaginated();
  if (is_paginated && !ChildrenInline()) {
    // Forced breaks are inserted at class A break points. Floats may be
    // affected by a break-after value on the previous in-flow sibling.
    if (LayoutBox* previous_in_flow_box = child.PreviousInFlowSiblingBox()) {
      logical_top_margin_edge = ApplyForcedBreak(
          logical_top_margin_edge, previous_in_flow_box->BreakAfter());
    }
  }

  LayoutUnit old_logical_top = child.LogicalTop();
  if (child.NeedsLayout()) {
    if (is_paginated) {
      // Before we can lay out the float, we need to estimate a position for
      // it. In order to do that, we first need to know its block start margin.
      child.ComputeAndSetBlockDirectionMargins(this);
      LayoutUnit margin_before = MarginBeforeForChild(child);

      // We have found the highest possible position for the float, so we'll
      // lay out right there. Later on, we may be pushed further down by
      // adjacent floats which we don't fit beside, or pushed by fragmentation
      // if we need to break before the top margin edge of the float.
      SetLogicalTopForChild(child, logical_top_margin_edge + margin_before);
      child.UpdateLayout();

      // May need to push the float to the next fragmentainer before attempting
      // to place it.
      logical_top_margin_edge =
          AdjustFloatLogicalTopForPagination(child, logical_top_margin_edge);
    } else {
      child.UpdateLayout();
    }
  }

  LayoutUnit margin_start = MarginStartForChild(child);
  LayoutUnit margin_end = MarginEndForChild(child);
  SetLogicalWidthForFloat(
      floating_object, LogicalWidthForChild(child) + margin_start + margin_end);

  // We have determined the logical width of the float. This is enough
  // information to fit it among other floats according to float positioning
  // rules. Note that logical *height* doesn't really matter yet (until we're
  // going to place subsequent floats or other objects that are affected by
  // floats), since no float may be positioned above the outer logical top edge
  // of any other earlier float in the block formatting context.
  LayoutUnit margin_before = MarginBeforeForChild(child);
  LayoutUnit margin_after = MarginAfterForChild(child);
  LayoutPoint float_logical_location =
      ComputeLogicalLocationForFloat(floating_object, logical_top_margin_edge);
  logical_top_margin_edge = float_logical_location.Y();
  SetLogicalTopForChild(child, logical_top_margin_edge + margin_before);

  SubtreeLayoutScope layout_scope(child);

  // A new position may mean that we need to insert, move or remove breaks
  // inside the float. We may also need to lay out if we just ceased to be
  // fragmented, in order to remove pagination struts inside the child.
  MarkChildForPaginationRelayoutIfNeeded(child, layout_scope);
  child.LayoutIfNeeded();

  // If negative margin pushes the child completely out of its old position
  // mark for layout siblings that may have it in its float lists.
  if (child.LogicalBottom() <= old_logical_top) {
    LayoutObject* next = child.NextSibling();
    if (next && next->IsLayoutBlockFlow()) {
      LayoutBlockFlow* nextBlock = ToLayoutBlockFlow(next);
      if (!nextBlock->AvoidsFloats() || nextBlock->ShrinkToAvoidFloats())
        nextBlock->MarkAllDescendantsWithFloatsForLayout();
    }
  }

  if (is_paginated) {
    PaginatedContentWasLaidOut(child.LogicalBottom());

    // We may have to insert a break before the float.
    LayoutUnit new_logical_top_margin_edge =
        AdjustFloatLogicalTopForPagination(child, logical_top_margin_edge);
    if (logical_top_margin_edge != new_logical_top_margin_edge) {
      // We had already found a location for the float, but a soft
      // fragmentainer break then made us push it further down. This may affect
      // the inline position of the float (since we may no longer be beside the
      // same floats anymore). Block position will remain unaffected, though.
      float_logical_location = ComputeLogicalLocationForFloat(
          floating_object, new_logical_top_margin_edge);
      DCHECK_EQ(float_logical_location.Y(), new_logical_top_margin_edge);
      logical_top_margin_edge = new_logical_top_margin_edge;

      SetLogicalTopForChild(child, logical_top_margin_edge + margin_before);

      // Pushing the child to the next fragmentainer most likely means that we
      // need to recalculate pagination struts inside it.
      if (child.IsLayoutBlock())
        child.SetChildNeedsLayout(kMarkOnlyThis);
      child.LayoutIfNeeded();
      PaginatedContentWasLaidOut(child.LogicalBottom());
    }
  }

  LayoutUnit child_logical_left_margin =
      StyleRef().IsLeftToRightDirection() ? margin_start : margin_end;
  SetLogicalLeftForChild(
      child, float_logical_location.X() + child_logical_left_margin);
  SetLogicalLeftForFloat(floating_object, float_logical_location.X());
  SetLogicalTopForFloat(floating_object, logical_top_margin_edge);
  SetLogicalHeightForFloat(floating_object, LogicalHeightForChild(child) +
                                                margin_before + margin_after);

  if (ShapeOutsideInfo* shape_outside = child.GetShapeOutsideInfo())
    shape_outside->SetReferenceBoxLogicalSize(LogicalSizeForChild(child));

  return logical_top_margin_edge;
}

bool LayoutBlockFlow::HasOverhangingFloat(LayoutBox* layout_box) {
  if (!floating_objects_ || !Parent())
    return false;

  const FloatingObjectSet& floating_object_set = floating_objects_->Set();
  FloatingObjectSetIterator it =
      floating_object_set.Find<FloatingObjectHashTranslator>(layout_box);
  if (it == floating_object_set.end())
    return false;

  return IsOverhangingFloat(**it);
}

void LayoutBlockFlow::AddIntrudingFloats(LayoutBlockFlow* prev,
                                         LayoutUnit logical_left_offset,
                                         LayoutUnit logical_top_offset) {
  DCHECK(!AvoidsFloats());

  // If we create our own block formatting context then our contents don't
  // interact with floats outside it, even those from our parent.
  if (CreatesNewFormattingContext())
    return;

  // If the parent or previous sibling doesn't have any floats to add, don't
  // bother.
  if (!prev->floating_objects_)
    return;

  logical_left_offset += MarginLineLeft();

  const FloatingObjectSet& prev_set = prev->floating_objects_->Set();
  FloatingObjectSetIterator prev_end = prev_set.end();
  for (FloatingObjectSetIterator prev_it = prev_set.begin();
       prev_it != prev_end; ++prev_it) {
    FloatingObject& floating_object = *prev_it->get();
    if (LogicalBottomForFloat(floating_object) > logical_top_offset) {
      if (!floating_objects_ ||
          !floating_objects_->Set().Contains(&floating_object)) {
        // We create the floating object list lazily.
        if (!floating_objects_)
          CreateFloatingObjects();

        // Applying the child's margin makes no sense in the case where the
        // child was passed in since this margin was added already through the
        // modification of the |logicalLeftOffset| variable above.
        // |logicalLeftOffset| will equal the margin in this case, so it's
        // already been taken into account. Only apply this code if prev is the
        // parent, since otherwise the left margin will get applied twice.
        LayoutSize offset =
            IsHorizontalWritingMode()
                ? LayoutSize(logical_left_offset - (prev != Parent()
                                                        ? prev->MarginLeft()
                                                        : LayoutUnit()),
                             logical_top_offset)
                : LayoutSize(logical_top_offset,
                             logical_left_offset - (prev != Parent()
                                                        ? prev->MarginTop()
                                                        : LayoutUnit()));

        floating_objects_->Add(floating_object.CopyToNewContainer(offset));
      }
    }
  }
}

void LayoutBlockFlow::AddOverhangingFloats(LayoutBlockFlow* child,
                                           bool make_child_paint_other_floats) {
  // Prevent floats from being added to the canvas by the root element, e.g.,
  // <html>.
  if (!child->ContainsFloats() || child->CreatesNewFormattingContext())
    return;

  LayoutUnit child_logical_top = child->LogicalTop();
  LayoutUnit child_logical_left = child->LogicalLeft();

  // Floats that will remain the child's responsibility to paint should factor
  // into its overflow.
  FloatingObjectSetIterator child_end = child->floating_objects_->Set().end();
  for (FloatingObjectSetIterator child_it =
           child->floating_objects_->Set().begin();
       child_it != child_end; ++child_it) {
    FloatingObject& floating_object = *child_it->get();
    LayoutUnit logical_bottom_for_float =
        std::min(LogicalBottomForFloat(floating_object),
                 LayoutUnit::Max() - child_logical_top);
    LayoutUnit logical_bottom = child_logical_top + logical_bottom_for_float;

    if (logical_bottom > LogicalHeight()) {
      // If the object is not in the list, we add it now.
      if (!ContainsFloat(floating_object.GetLayoutObject())) {
        LayoutSize offset =
            IsHorizontalWritingMode()
                ? LayoutSize(-child_logical_left, -child_logical_top)
                : LayoutSize(-child_logical_top, -child_logical_left);
        bool should_paint = false;

        // The nearest enclosing layer always paints the float (so that zindex
        // and stacking behaves properly). We always want to propagate the
        // desire to paint the float as far out as we can, to the outermost
        // block that overlaps the float, stopping only if we hit a
        // self-painting layer boundary.
        if (floating_object.GetLayoutObject()->EnclosingFloatPaintingLayer() ==
                EnclosingFloatPaintingLayer() &&
            !floating_object.IsLowestNonOverhangingFloatInChild()) {
          floating_object.SetShouldPaint(false);
          should_paint = true;
        }
        // We create the floating object list lazily.
        if (!floating_objects_)
          CreateFloatingObjects();

        floating_objects_->Add(
            floating_object.CopyToNewContainer(offset, should_paint, true));
      }
    } else {
      if (make_child_paint_other_floats && !floating_object.ShouldPaint() &&
          !floating_object.GetLayoutObject()->HasSelfPaintingLayer() &&
          !floating_object.IsLowestNonOverhangingFloatInChild() &&
          floating_object.GetLayoutObject()->IsDescendantOf(child) &&
          floating_object.GetLayoutObject()->EnclosingFloatPaintingLayer() ==
              child->EnclosingFloatPaintingLayer()) {
        // The float is not overhanging from this block, so if it is a
        // descendant of the child, the child should paint it (the other case is
        // that it is intruding into the child), unless it has its own layer or
        // enclosing layer.
        // If makeChildPaintOtherFloats is false, it means that the child must
        // already know about all the floats it should paint.
        floating_object.SetShouldPaint(true);
      }

      // Since the float doesn't overhang, it didn't get put into our list. We
      // need to go ahead and add its overflow in to the child now.
      if (floating_object.IsDescendant()) {
        // TODO(chrishtr): this looks weird, is it correct? Also, do we need
        // both types of overflow?
        child->AddVisualOverflowFromChild(
            *floating_object.GetLayoutObject(),
            LayoutSize(XPositionForFloatIncludingMargin(floating_object),
                       YPositionForFloatIncludingMargin(floating_object)));
        child->AddLayoutOverflowFromChild(
            *floating_object.GetLayoutObject(),
            LayoutSize(XPositionForFloatIncludingMargin(floating_object),
                       YPositionForFloatIncludingMargin(floating_object)));
      }
    }
  }
}

LayoutUnit LayoutBlockFlow::LowestFloatLogicalBottom(EClear clear) const {
  if (clear == EClear::kNone || !floating_objects_)
    return LayoutUnit();

  FloatingObject::Type float_type = clear == EClear::kLeft
                                        ? FloatingObject::kFloatLeft
                                        : clear == EClear::kRight
                                              ? FloatingObject::kFloatRight
                                              : FloatingObject::kFloatLeftRight;
  return floating_objects_->LowestFloatLogicalBottom(float_type);
}

LayoutUnit LayoutBlockFlow::NextFloatLogicalBottomBelow(
    LayoutUnit logical_height) const {
  if (!floating_objects_)
    return logical_height;
  return floating_objects_->FindNextFloatLogicalBottomBelow(logical_height);
}

LayoutUnit LayoutBlockFlow::NextFloatLogicalBottomBelowForBlock(
    LayoutUnit logical_height) const {
  if (!floating_objects_)
    return logical_height;

  return floating_objects_->FindNextFloatLogicalBottomBelowForBlock(
      logical_height);
}

LayoutUnit LayoutBlockFlow::LogicalHeightWithVisibleOverflow() const {
  LayoutUnit logical_height = LayoutBlock::LogicalHeightWithVisibleOverflow();
  return std::max(logical_height, LowestFloatLogicalBottom());
}

Node* LayoutBlockFlow::NodeForHitTest() const {
  // If we are in the margins of block elements that are part of a
  // continuation we're actually still inside the enclosing element
  // that was split. Use the appropriate inner node.
  return IsAnonymousBlockContinuation() ? Continuation()->NodeForHitTest()
                                        : LayoutBlock::NodeForHitTest();
}

bool LayoutBlockFlow::HitTestChildren(
    HitTestResult& result,
    const HitTestLocation& location_in_container,
    const LayoutPoint& accumulated_offset,
    HitTestAction hit_test_action) {
  LayoutPoint scrolled_offset(HasOverflowClip()
                                  ? accumulated_offset - ScrolledContentOffset()
                                  : accumulated_offset);

  if (hit_test_action == kHitTestFloat && !IsLayoutNGObject()) {
    // Hit-test the floats using the FloatingObjects list if we're in legacy
    // layout. LayoutNG, on the other hand, just hit-tests floats in regular
    // tree order.
    if (HitTestFloats(result, location_in_container, scrolled_offset))
      return true;
  }

  if (ChildrenInline()) {
    if (line_boxes_.HitTest(LineLayoutBoxModel(this), result,
                            location_in_container, scrolled_offset,
                            hit_test_action)) {
      UpdateHitTestResult(
          result, FlipForWritingMode(ToLayoutPoint(
                      location_in_container.Point() - accumulated_offset)));
      return true;
    }
  } else if (LayoutBlock::HitTestChildren(result, location_in_container,
                                          accumulated_offset,
                                          hit_test_action)) {
    return true;
  }

  return false;
}

bool LayoutBlockFlow::HitTestFloats(
    HitTestResult& result,
    const HitTestLocation& location_in_container,
    const LayoutPoint& accumulated_offset) {
  if (!floating_objects_)
    return false;

  const FloatingObjectSet& floating_object_set = floating_objects_->Set();
  FloatingObjectSetIterator begin = floating_object_set.begin();
  for (FloatingObjectSetIterator it = floating_object_set.end(); it != begin;) {
    --it;
    const FloatingObject& floating_object = *it->get();
    if (floating_object.ShouldPaint() &&
        // TODO(wangxianzhu): Should this be a DCHECK?
        !floating_object.GetLayoutObject()->HasSelfPaintingLayer()) {
      LayoutUnit x_offset = XPositionForFloatIncludingMargin(floating_object) -
                            floating_object.GetLayoutObject()->Location().X();
      LayoutUnit y_offset = YPositionForFloatIncludingMargin(floating_object) -
                            floating_object.GetLayoutObject()->Location().Y();
      LayoutPoint child_point = FlipFloatForWritingModeForChild(
          floating_object, accumulated_offset + LayoutSize(x_offset, y_offset));
      if (floating_object.GetLayoutObject()->HitTestAllPhases(
              result, location_in_container, child_point)) {
        UpdateHitTestResult(
            result, location_in_container.Point() - ToLayoutSize(child_point));
        return true;
      }
    }
  }

  return false;
}

LayoutSize LayoutBlockFlow::AccumulateInFlowPositionOffsets() const {
  if (!IsAnonymousBlock() || !IsInFlowPositioned())
    return LayoutSize();
  LayoutSize offset;
  for (const LayoutObject* p = InlineElementContinuation();
       p && p->IsLayoutInline(); p = p->Parent()) {
    if (p->IsInFlowPositioned())
      offset += ToLayoutInline(p)->OffsetForInFlowPosition();
  }
  return offset;
}

LayoutUnit LayoutBlockFlow::LogicalLeftFloatOffsetForLine(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit logical_height) const {
  if (floating_objects_ && floating_objects_->HasLeftObjects())
    return floating_objects_->LogicalLeftOffset(fixed_offset, logical_top,
                                                logical_height);

  return fixed_offset;
}

LayoutUnit LayoutBlockFlow::LogicalRightFloatOffsetForLine(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit logical_height) const {
  if (floating_objects_ && floating_objects_->HasRightObjects())
    return floating_objects_->LogicalRightOffset(fixed_offset, logical_top,
                                                 logical_height);

  return fixed_offset;
}

LayoutUnit LayoutBlockFlow::LogicalLeftFloatOffsetForAvoidingFloats(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit logical_height) const {
  if (floating_objects_ && floating_objects_->HasLeftObjects()) {
    return floating_objects_->LogicalLeftOffsetForAvoidingFloats(
        fixed_offset, logical_top, logical_height);
  }

  return fixed_offset;
}

LayoutUnit LayoutBlockFlow::LogicalRightFloatOffsetForAvoidingFloats(
    LayoutUnit logical_top,
    LayoutUnit fixed_offset,
    LayoutUnit logical_height) const {
  if (floating_objects_ && floating_objects_->HasRightObjects()) {
    return floating_objects_->LogicalRightOffsetForAvoidingFloats(
        fixed_offset, logical_top, logical_height);
  }

  return fixed_offset;
}

void LayoutBlockFlow::UpdateAncestorShouldPaintFloatingObject(
    const LayoutBox& float_box) {
  // Normally, the ShouldPaint flags of FloatingObjects should have been set
  // during layout, based on overhaning, intruding, self-painting status, etc.
  // However, sometimes a layer's self painting status is affected by its
  // compositing status, so we need to call this method during compositing
  // update when we find a layer changes self painting status. This doesn't
  // apply to SPv2 in which a layer's self painting status no longer depends on
  // compositing status.
  DCHECK(!RuntimeEnabledFeatures::SlimmingPaintV2Enabled());
  DCHECK(float_box.IsFloating());
  bool float_box_is_self_painting_layer =
      float_box.HasLayer() && float_box.Layer()->IsSelfPaintingLayer();
  bool found_painting_ancestor = false;
  for (LayoutObject* ancestor = float_box.ContainingBlock(); ancestor;
       ancestor = ancestor->ContainingBlock()) {
    if (!ancestor->IsLayoutBlockFlow())
      continue;

    LayoutBlockFlow* ancestor_block = ToLayoutBlockFlow(ancestor);
    FloatingObjects* ancestor_floating_objects =
        ancestor_block->floating_objects_.get();
    if (!ancestor_floating_objects)
      break;
    FloatingObjectSet::iterator it =
        ancestor_floating_objects->MutableSet()
            .Find<FloatingObjectHashTranslator>(
                const_cast<LayoutBox*>(&float_box));
    if (it == ancestor_floating_objects->MutableSet().end())
      break;

    FloatingObject& floating_object = **it;
    if (!found_painting_ancestor && !float_box_is_self_painting_layer) {
      // This tries to repeat the logic in AddOverhangingFloats() about
      // ShouldPaint flag with the following rules:
      // - The nearest enclosing block in which the float doesn't overhang
      //   paints the float;
      // - Or even if the float overhangs, if the ancestor block has
      //   self-painting layer, it paints the float.
      // However it is not fully consistent with AddOverhangingFloats() when
      // a float doesn't overhang in an ancestor but overhangs in an ancestor
      // of the ancestor. This results different ancestor painting the float,
      // but there seems no problem for now.
      if (ancestor_block->HasSelfPaintingLayer() ||
          !ancestor_block->IsOverhangingFloat(floating_object)) {
        floating_object.SetShouldPaint(true);
        found_painting_ancestor = true;
      }
    } else {
      floating_object.SetShouldPaint(false);
    }
  }
}

bool LayoutBlockFlow::AllowsPaginationStrut() const {
  // The block needs to be contained by a LayoutBlockFlow (and not by e.g. a
  // flexbox, grid, or a table (the latter being the case for table cell or
  // table caption)). The reason for this limitation is simply that
  // LayoutBlockFlow child layout code is the only place where we pick up the
  // struts and handle them. We handle floats and regular in-flow children, and
  // that's all. We could handle this in other layout modes as well (and even
  // for out-of-flow children), but currently we don't.
  // TODO(mstensho): But we *should*.
  if (IsOutOfFlowPositioned())
    return false;
  if (IsLayoutFlowThread()) {
    // Don't let the strut escape the fragmentation context and get lost.
    // TODO(mstensho): If we're in a nested fragmentation context, we should
    // ideally convert and propagate the strut to the outer fragmentation
    // context, so that the inner one is fully pushed to the next outer
    // fragmentainer, instead of taking up unusable space in the previous one.
    // But currently we have no mechanism in place to handle this.
    return false;
  }
  const LayoutBlock* containing_block = ContainingBlock();
  if (!containing_block || !containing_block->IsLayoutBlockFlow())
    return false;
  const LayoutBlockFlow* containing_block_flow =
      ToLayoutBlockFlow(containing_block);
  // If children are inline, allow the strut. We are probably a float.
  if (containing_block_flow->ChildrenInline())
    return true;
  for (LayoutBox* sibling = PreviousSiblingBox(); sibling;
       sibling = sibling->PreviousSiblingBox()) {
    // What happens on the other side of a spanner is none of our concern, so
    // stop here. Since there's no in-flow box between the previous spanner and
    // us, there's no class A break point in front of us. We cannot even
    // re-propagate pagination struts to our containing block, since the
    // containing block starts in a different column row.
    if (sibling->IsColumnSpanAll())
      return false;
    // If this isn't the first in-flow object, there's a break opportunity
    // before us, which means that we can allow the strut.
    if (!sibling->IsFloatingOrOutOfFlowPositioned())
      return true;
  }
  // This is a first in-flow child. We'll still allow the strut if it can be
  // re-propagated to our containing block.
  return containing_block_flow->AllowsPaginationStrut();
}

void LayoutBlockFlow::SetPaginationStrutPropagatedFromChild(LayoutUnit strut) {
  strut = std::max(strut, LayoutUnit());
  if (!rare_data_) {
    if (!strut)
      return;
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);
  }
  rare_data_->pagination_strut_propagated_from_child_ = strut;
}

void LayoutBlockFlow::SetFirstForcedBreakOffset(LayoutUnit block_offset) {
  if (!rare_data_) {
    if (!block_offset)
      return;
    rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);
  }
  rare_data_->first_forced_break_offset_ = block_offset;
}

void LayoutBlockFlow::PositionSpannerDescendant(
    LayoutMultiColumnSpannerPlaceholder& child) {
  LayoutBox& spanner = *child.LayoutObjectInFlowThread();
  // FIXME: |spanner| is a descendant, but never a direct child, so the names
  // here are bad, if nothing else.
  SetLogicalTopForChild(spanner, child.LogicalTop());
  DetermineLogicalLeftPositionForChild(spanner);
}

DISABLE_CFI_PERF
bool LayoutBlockFlow::CreatesNewFormattingContext() const {
  if (IsInline() || IsFloatingOrOutOfFlowPositioned() || HasOverflowClip() ||
      IsFlexItemIncludingDeprecated() || IsCustomItem() ||
      IsDocumentElement() || IsGridItem() || IsWritingModeRoot() ||
      StyleRef().Display() == EDisplay::kFlowRoot ||
      ShouldApplyPaintContainment() || ShouldApplyLayoutContainment() ||
      StyleRef().SpecifiesColumns() ||
      StyleRef().GetColumnSpan() == EColumnSpan::kAll) {
    // The specs require this object to establish a new formatting context.
    return true;
  }

  if (IsRenderedLegend())
    return true;

  return false;
}

bool LayoutBlockFlow::AvoidsFloats() const {
  return ShouldBeConsideredAsReplaced() || CreatesNewFormattingContext();
}

void LayoutBlockFlow::MoveChildrenTo(LayoutBoxModelObject* to_box_model_object,
                                     LayoutObject* start_child,
                                     LayoutObject* end_child,
                                     LayoutObject* before_child,
                                     bool full_remove_insert) {
  if (ChildrenInline())
    DeleteLineBoxTree();
  LayoutBoxModelObject::MoveChildrenTo(to_box_model_object, start_child,
                                       end_child, before_child,
                                       full_remove_insert);
}

RootInlineBox* LayoutBlockFlow::CreateRootInlineBox() {
  return new RootInlineBox(LineLayoutItem(this));
}

bool LayoutBlockFlow::IsPagedOverflow(const ComputedStyle& style) {
  return style.IsOverflowPaged() &&
         GetNode() != GetDocument().ViewportDefiningElement();
}

LayoutBlockFlow::FlowThreadType LayoutBlockFlow::GetFlowThreadType(
    const ComputedStyle& style) {
  if (IsPagedOverflow(style))
    return kPagedFlowThread;
  if (style.SpecifiesColumns())
    return kMultiColumnFlowThread;
  return kNoFlowThread;
}

LayoutMultiColumnFlowThread* LayoutBlockFlow::CreateMultiColumnFlowThread(
    FlowThreadType type) {
  switch (type) {
    case kMultiColumnFlowThread:
      return LayoutMultiColumnFlowThread::CreateAnonymous(GetDocument(),
                                                          StyleRef());
    case kPagedFlowThread:
      // Paged overflow is currently done using the multicol implementation.
      UseCounter::Count(GetDocument(), WebFeature::kCSSOverflowPaged);
      return LayoutPagedFlowThread::CreateAnonymous(GetDocument(), StyleRef());
    default:
      NOTREACHED();
      return nullptr;
  }
}

void LayoutBlockFlow::CreateOrDestroyMultiColumnFlowThreadIfNeeded(
    const ComputedStyle* old_style) {
  // Paged overflow trumps multicol in this implementation. Ideally, it should
  // be possible to have both paged overflow and multicol on the same element,
  // but then we need two flow threads. Anyway, this is nothing to worry about
  // until we can actually nest multicol properly inside other fragmentation
  // contexts.
  FlowThreadType type = GetFlowThreadType(StyleRef());

  if (MultiColumnFlowThread()) {
    DCHECK(old_style);
    if (type != GetFlowThreadType(*old_style)) {
      // If we're no longer to be multicol/paged, destroy the flow thread. Also
      // destroy it when switching between multicol and paged, since that
      // affects the column set structure (multicol containers may have
      // spanners, paged containers may not).
      MultiColumnFlowThread()->EvacuateAndDestroy();
      DCHECK(!MultiColumnFlowThread());
      pagination_state_changed_ = true;
    }
  }

  if (type == kNoFlowThread || MultiColumnFlowThread())
    return;

  // Ruby elements manage child insertion in a special way, and would mess up
  // insertion of the flow thread. The flow thread needs to be a direct child of
  // the multicol block (|this|).
  if (IsRuby())
    return;

  // Fieldsets look for a legend special child (layoutSpecialExcludedChild()).
  // We currently only support one special child per layout object, and the
  // flow thread would make for a second one.
  if (IsFieldset())
    return;

  // Form controls are replaced content, and are therefore not supposed to
  // support multicol.
  if (IsFileUploadControl() || IsTextControl() || IsListBox())
    return;

  LayoutMultiColumnFlowThread* flow_thread = CreateMultiColumnFlowThread(type);
  AddChild(flow_thread);
  pagination_state_changed_ = true;

  // Check that addChild() put the flow thread as a direct child, and didn't do
  // fancy things.
  DCHECK_EQ(flow_thread->Parent(), this);

  flow_thread->Populate();
  LayoutBlockFlowRareData& rare_data = EnsureRareData();
  DCHECK(!rare_data.multi_column_flow_thread_);
  rare_data.multi_column_flow_thread_ = flow_thread;
}

LayoutBlockFlow::LayoutBlockFlowRareData& LayoutBlockFlow::EnsureRareData() {
  if (rare_data_)
    return *rare_data_;

  rare_data_ = std::make_unique<LayoutBlockFlowRareData>(this);
  return *rare_data_;
}

void LayoutBlockFlow::PositionDialog() {
  base::Optional<LayoutUnit> y =
      ComputeAbsoluteDialogYPosition(*this, Size().Height());
  if (y.has_value())
    SetY(y.value());
}

void LayoutBlockFlow::SimplifiedNormalFlowInlineLayout() {
  DCHECK(ChildrenInline());
  ListHashSet<RootInlineBox*> line_boxes;
  for (InlineWalker walker(LineLayoutBlockFlow(this)); !walker.AtEnd();
       walker.Advance()) {
    LayoutObject* o = walker.Current().GetLayoutObject();
    if (!o->IsOutOfFlowPositioned() &&
        (o->IsAtomicInlineLevel() || o->IsFloating())) {
      o->LayoutIfNeeded();
      if (ToLayoutBox(o)->InlineBoxWrapper()) {
        RootInlineBox& box = ToLayoutBox(o)->InlineBoxWrapper()->Root();
        line_boxes.insert(&box);
      }
    } else if (o->IsText() ||
               (o->IsLayoutInline() && !walker.AtEndOfInline())) {
      o->ClearNeedsLayout();
    }
  }

  // FIXME: Glyph overflow will get lost in this case, but not really a big
  // deal.
  GlyphOverflowAndFallbackFontsMap text_box_data_map;
  for (ListHashSet<RootInlineBox*>::const_iterator it = line_boxes.begin();
       it != line_boxes.end(); ++it) {
    RootInlineBox* box = *it;
    box->ComputeOverflow(box->LineTop(), box->LineBottom(), text_box_data_map);
  }
}

bool LayoutBlockFlow::RecalcInlineChildrenOverflow() {
  DCHECK(ChildrenInline());
  bool children_overflow_changed = false;
  ListHashSet<RootInlineBox*> line_boxes;
  for (InlineWalker walker(LineLayoutBlockFlow(this)); !walker.AtEnd();
       walker.Advance()) {
    LayoutObject* layout_object = walker.Current().GetLayoutObject();
    if (RecalcNormalFlowChildOverflowIfNeeded(layout_object)) {
      children_overflow_changed = true;
      if (layout_object->IsLayoutBlock()) {
        if (InlineBox* inline_box_wrapper =
                ToLayoutBlock(layout_object)->InlineBoxWrapper())
          line_boxes.insert(&inline_box_wrapper->Root());
      }
    }
  }

  // FIXME: Glyph overflow will get lost in this case, but not really a big
  // deal.
  GlyphOverflowAndFallbackFontsMap text_box_data_map;
  for (ListHashSet<RootInlineBox*>::const_iterator it = line_boxes.begin();
       it != line_boxes.end(); ++it) {
    RootInlineBox* box = *it;
    box->ClearKnownToHaveNoOverflow();
    box->ComputeOverflow(box->LineTop(), box->LineBottom(), text_box_data_map);
  }
  return children_overflow_changed;
}

PositionWithAffinity LayoutBlockFlow::PositionForPoint(
    const LayoutPoint& point) const {
  if (IsAtomicInlineLevel()) {
    PositionWithAffinity position =
        PositionForPointIfOutsideAtomicInlineLevel(point);
    if (!position.IsNull())
      return position;
  }
  if (!ChildrenInline())
    return LayoutBlock::PositionForPoint(point);

  LayoutPoint point_in_contents = point;
  OffsetForContents(point_in_contents);
  LayoutPoint point_in_logical_contents(point_in_contents);
  if (!IsHorizontalWritingMode())
    point_in_logical_contents = point_in_logical_contents.TransposedPoint();

  if (!FirstRootBox())
    return CreatePositionWithAffinity(0);

  bool lines_are_flipped = StyleRef().IsFlippedLinesWritingMode();
  bool blocks_are_flipped = StyleRef().IsFlippedBlocksWritingMode();

  // look for the closest line box in the root box which is at the passed-in y
  // coordinate
  InlineBox* closest_box = nullptr;
  RootInlineBox* first_root_box_with_children = nullptr;
  RootInlineBox* last_root_box_with_children = nullptr;
  for (RootInlineBox* root = FirstRootBox(); root; root = root->NextRootBox()) {
    if (!root->FirstLeafChild())
      continue;
    if (!first_root_box_with_children)
      first_root_box_with_children = root;

    if (!lines_are_flipped && root->IsFirstAfterPageBreak() &&
        (point_in_logical_contents.Y() < root->LineTopWithLeading() ||
         (blocks_are_flipped &&
          point_in_logical_contents.Y() == root->LineTopWithLeading())))
      break;

    last_root_box_with_children = root;

    // check if this root line box is located at this y coordinate
    if (point_in_logical_contents.Y() < root->SelectionBottom() ||
        (blocks_are_flipped &&
         point_in_logical_contents.Y() == root->SelectionBottom())) {
      if (lines_are_flipped) {
        RootInlineBox* next_root_box_with_children = root->NextRootBox();
        while (next_root_box_with_children &&
               !next_root_box_with_children->FirstLeafChild())
          next_root_box_with_children =
              next_root_box_with_children->NextRootBox();

        if (next_root_box_with_children &&
            next_root_box_with_children->IsFirstAfterPageBreak() &&
            (point_in_logical_contents.Y() >
                 next_root_box_with_children->LineTopWithLeading() ||
             (!blocks_are_flipped &&
              point_in_logical_contents.Y() ==
                  next_root_box_with_children->LineTopWithLeading())))
          continue;
      }
      closest_box = root->ClosestLeafChildForLogicalLeftPosition(
          point_in_logical_contents.X());
      if (closest_box)
        break;
    }
  }

  bool move_caret_to_boundary =
      GetDocument()
          .GetFrame()
          ->GetEditor()
          .Behavior()
          .ShouldMoveCaretToHorizontalBoundaryWhenPastTopOrBottom();

  if (!move_caret_to_boundary && !closest_box && last_root_box_with_children) {
    // y coordinate is below last root line box, pretend we hit it
    closest_box =
        last_root_box_with_children->ClosestLeafChildForLogicalLeftPosition(
            point_in_logical_contents.X());
  }

  if (closest_box) {
    if (move_caret_to_boundary) {
      LayoutUnit first_root_box_with_children_top =
          std::min<LayoutUnit>(first_root_box_with_children->SelectionTop(),
                               first_root_box_with_children->LogicalTop());
      if (point_in_logical_contents.Y() < first_root_box_with_children_top ||
          (blocks_are_flipped &&
           point_in_logical_contents.Y() == first_root_box_with_children_top)) {
        InlineBox* box = first_root_box_with_children->FirstLeafChild();
        if (box->IsLineBreak()) {
          if (InlineBox* new_box = box->NextLeafChildIgnoringLineBreak())
            box = new_box;
        }
        // y coordinate is above first root line box, so return the start of the
        // first
        return PositionWithAffinity(PositionForBox(box, true));
      }
    }

    if (closest_box->GetLineLayoutItem().IsAtomicInlineLevel()) {
      // We want to pass the original point other than a corrected one.
      LayoutPoint point(point_in_logical_contents);
      if (!IsHorizontalWritingMode())
        point = point.TransposedPoint();
      return PositionForPointRespectingEditingBoundaries(
          LineLayoutBox(closest_box->GetLineLayoutItem()), point);
    }

    // pass the box a top position that is inside it
    LayoutPoint point(point_in_logical_contents.X(),
                      closest_box->Root().BlockDirectionPointInLine());
    if (!IsHorizontalWritingMode())
      point = point.TransposedPoint();
    return closest_box->GetLineLayoutItem().PositionForPoint(point);
  }

  if (last_root_box_with_children) {
    // We hit this case for Mac behavior when the Y coordinate is below the last
    // box.
    DCHECK(move_caret_to_boundary);
    if (const InlineBox* logically_last_box =
            last_root_box_with_children->GetLogicalEndNonPseudoBox()) {
      // TODO(layout-dev): Change |PositionForBox()| to take |const InlineBox*|.
      return PositionWithAffinity(
          PositionForBox(const_cast<InlineBox*>(logically_last_box), false));
    }
  }

  // Can't reach this. We have a root line box, but it has no kids.
  // FIXME: This should NOTREACHED(), but clicking on placeholder text
  // seems to hit this code path.
  return CreatePositionWithAffinity(0);
}

#ifndef NDEBUG

void LayoutBlockFlow::ShowLineTreeAndMark(const InlineBox* marked_box1,
                                          const char* marked_label1,
                                          const InlineBox* marked_box2,
                                          const char* marked_label2,
                                          const LayoutObject* obj) const {
  StringBuilder string_blockflow;
  DumpLayoutObject(string_blockflow, true, kShowTreeCharacterOffset);
  for (const RootInlineBox* root = FirstRootBox(); root;
       root = root->NextRootBox()) {
    root->DumpLineTreeAndMark(string_blockflow, marked_box1, marked_label1,
                              marked_box2, marked_label2, obj, 1);
  }
  DLOG(INFO) << "\n" << string_blockflow.ToString().Utf8().data();
}

#endif

void LayoutBlockFlow::AddOutlineRects(
    Vector<LayoutRect>& rects,
    const LayoutPoint& additional_offset,
    NGOutlineType include_block_overflows) const {
  // For blocks inside inlines, we go ahead and include margins so that we run
  // right up to the inline boxes above and below us (thus getting merged with
  // them to form a single irregular shape).
  const LayoutInline* inline_element_continuation = InlineElementContinuation();
  if (inline_element_continuation) {
    // FIXME: This check really isn't accurate.
    bool next_inline_has_line_box = inline_element_continuation->FirstLineBox();
    // FIXME: This is wrong. The principal layoutObject may not be the
    // continuation preceding this block.
    // FIXME: This is wrong for vertical writing-modes.
    // https://bugs.webkit.org/show_bug.cgi?id=46781
    bool prev_inline_has_line_box =
        ToLayoutInline(
            inline_element_continuation->GetNode()->GetLayoutObject())
            ->FirstLineBox();
    LayoutUnit top_margin =
        prev_inline_has_line_box ? CollapsedMarginBefore() : LayoutUnit();
    LayoutUnit bottom_margin =
        next_inline_has_line_box ? CollapsedMarginAfter() : LayoutUnit();
    if (top_margin || bottom_margin) {
      LayoutRect rect(additional_offset, Size());
      rect.ExpandEdges(top_margin, LayoutUnit(), bottom_margin, LayoutUnit());
      rects.push_back(rect);
    }
  }

  LayoutBlock::AddOutlineRects(rects, additional_offset,
                               include_block_overflows);

  if (include_block_overflows == NGOutlineType::kIncludeBlockVisualOverflow &&
      !HasOverflowClip() && !HasControlClip()) {
    for (RootInlineBox* curr = FirstRootBox(); curr;
         curr = curr->NextRootBox()) {
      LayoutUnit top = std::max<LayoutUnit>(curr->LineTop(), curr->Y());
      LayoutUnit bottom =
          std::min<LayoutUnit>(curr->LineBottom(), curr->Y() + curr->Height());
      LayoutRect rect(additional_offset.X() + curr->X(),
                      additional_offset.Y() + top, curr->Width(), bottom - top);
      if (!rect.IsEmpty())
        rects.push_back(rect);
    }
  }

  if (inline_element_continuation)
    inline_element_continuation->AddOutlineRects(
        rects,
        additional_offset +
            (inline_element_continuation->ContainingBlock()->Location() -
             Location()),
        include_block_overflows);
}

void LayoutBlockFlow::InvalidateDisplayItemClients(
    PaintInvalidationReason invalidation_reason) const {
  BlockFlowPaintInvalidator(*this).InvalidateDisplayItemClients(
      invalidation_reason);
}

void LayoutBlockFlow::IncrementLayoutPassCount() {
  int layout_pass_count = 0;
  HashMap<LayoutBlockFlow*, int>::iterator layout_count_iterator =
      GetLayoutPassCountMap().find(this);
  if (layout_count_iterator != GetLayoutPassCountMap().end())
    layout_pass_count = layout_count_iterator->value;
  GetLayoutPassCountMap().Set(this, ++layout_pass_count);
}

int LayoutBlockFlow::GetLayoutPassCountForTesting() {
  return GetLayoutPassCountMap().find(this)->value;
}

}  // namespace blink
