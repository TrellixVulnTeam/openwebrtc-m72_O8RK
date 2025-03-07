/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Apple Inc.
 * All rights reserved.
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "third_party/blink/renderer/core/css/resolver/element_style_resources.h"

#include "third_party/blink/renderer/core/css/css_gradient_value.h"
#include "third_party/blink/renderer/core/css/css_image_value.h"
#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/css/css_uri_value.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/tree_scope.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/html/lazy_load_image_observer.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/content_data.h"
#include "third_party/blink/renderer/core/style/cursor_data.h"
#include "third_party/blink/renderer/core/style/fill_layer.h"
#include "third_party/blink/renderer/core/style/filter_operation.h"
#include "third_party/blink/renderer/core/style/style_fetched_image.h"
#include "third_party/blink/renderer/core/style/style_fetched_image_set.h"
#include "third_party/blink/renderer/core/style/style_generated_image.h"
#include "third_party/blink/renderer/core/style/style_image.h"
#include "third_party/blink/renderer/core/style/style_pending_image.h"
#include "third_party/blink/renderer/core/svg/svg_resource.h"
#include "third_party/blink/renderer/core/svg/svg_tree_scope_resources.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_parameters.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"

namespace blink {

ElementStyleResources::ElementStyleResources(Element& element,
                                             float device_scale_factor)
    : element_(&element), device_scale_factor_(device_scale_factor) {}

StyleImage* ElementStyleResources::GetStyleImage(CSSPropertyID property,
                                                 const CSSValue& value) {
  if (value.IsImageValue())
    return CachedOrPendingFromValue(property, ToCSSImageValue(value));

  if (value.IsImageGeneratorValue())
    return GeneratedOrPendingFromValue(property,
                                       ToCSSImageGeneratorValue(value));

  if (value.IsImageSetValue())
    return SetOrPendingFromValue(property, ToCSSImageSetValue(value));

  return nullptr;
}

StyleImage* ElementStyleResources::GeneratedOrPendingFromValue(
    CSSPropertyID property,
    const CSSImageGeneratorValue& value) {
  if (value.IsPending()) {
    pending_image_properties_.insert(property);
    return StylePendingImage::Create(value);
  }
  return StyleGeneratedImage::Create(value);
}

StyleImage* ElementStyleResources::SetOrPendingFromValue(
    CSSPropertyID property,
    const CSSImageSetValue& value) {
  if (value.IsCachePending(device_scale_factor_)) {
    pending_image_properties_.insert(property);
    return StylePendingImage::Create(value);
  }
  return value.CachedImage(device_scale_factor_);
}

StyleImage* ElementStyleResources::CachedOrPendingFromValue(
    CSSPropertyID property,
    const CSSImageValue& value) {
  if (value.IsCachePending()) {
    pending_image_properties_.insert(property);
    return StylePendingImage::Create(value);
  }
  value.RestoreCachedResourceIfNeeded(element_->GetDocument());
  return value.CachedImage();
}

SVGResource* ElementStyleResources::GetSVGResourceFromValue(
    TreeScope& tree_scope,
    const CSSURIValue& value,
    AllowExternal allow_external) const {
  if (value.IsLocal(element_->GetDocument())) {
    SVGTreeScopeResources& tree_scope_resources =
        tree_scope.EnsureSVGTreeScopedResources();
    AtomicString decoded_fragment(
        DecodeURLEscapeSequences(value.FragmentIdentifier()));
    return tree_scope_resources.ResourceForId(decoded_fragment);
  }
  if (allow_external == kAllowExternalResource)
    return value.EnsureResourceReference();
  return nullptr;
}

void ElementStyleResources::LoadPendingSVGResources(
    ComputedStyle* computed_style) {
  if (!computed_style->HasFilter())
    return;
  FilterOperations::FilterOperationVector& filter_operations =
      computed_style->MutableFilter().Operations();
  for (auto& filter_operation : filter_operations) {
    if (filter_operation->GetType() != FilterOperation::REFERENCE)
      continue;
    ReferenceFilterOperation& reference_operation =
        ToReferenceFilterOperation(*filter_operation);
    if (SVGResource* resource = reference_operation.Resource())
      resource->Load(element_->GetDocument());
  }
}

static bool BackgroundLayerMayBeSprite(const FillLayer& background_layer) {
  // Simple heuristic to guess if a CSS background image layer is used to
  // create CSS sprites. For a legit background image it's very likely the X
  // and the Y position will not be explicitly specifed. For CSS sprite image,
  // background X or Y position will probably be specified.
  DCHECK(background_layer.GetImage());
  return background_layer.PositionX().IsFixed() ||
         background_layer.PositionY().IsFixed();
}

StyleImage* ElementStyleResources::LoadPendingImage(
    ComputedStyle* style,
    StylePendingImage* pending_image,
    FetchParameters::ImageRequestOptimization image_request_optimization,
    CrossOriginAttributeValue cross_origin) {
  if (CSSImageValue* image_value = pending_image->CssImageValue()) {
    return image_value->CacheImage(element_->GetDocument(),
                                   image_request_optimization, cross_origin);
  }

  if (CSSPaintValue* paint_value = pending_image->CssPaintValue()) {
    StyleGeneratedImage* image = StyleGeneratedImage::Create(*paint_value);
    style->AddPaintImage(image);
    return image;
  }

  if (CSSImageGeneratorValue* image_generator_value =
          pending_image->CssImageGeneratorValue()) {
    image_generator_value->LoadSubimages(element_->GetDocument());
    return StyleGeneratedImage::Create(*image_generator_value);
  }

  if (CSSImageSetValue* image_set_value = pending_image->CssImageSetValue()) {
    return image_set_value->CacheImage(
        element_->GetDocument(), device_scale_factor_,
        image_request_optimization, cross_origin);
  }

  NOTREACHED();
  return nullptr;
}

void ElementStyleResources::LoadPendingImages(ComputedStyle* style) {
  // We must loop over the properties and then look at the style to see if
  // a pending image exists, and only load that image. For example:
  //
  // <style>
  //    div { background-image: url(a.png); }
  //    div { background-image: url(b.png); }
  //    div { background-image: none; }
  // </style>
  // <div></div>
  //
  // We call styleImage() for both a.png and b.png adding the
  // CSSPropertyBackgroundImage property to the pending_image_properties_ set,
  // then we null out the background image because of the "none".
  //
  // If we eagerly loaded the images we'd fetch a.png, even though it's not
  // used. If we didn't null check below we'd crash since the none actually
  // removed all background images.

  for (CSSPropertyID property : pending_image_properties_) {
    switch (property) {
      case CSSPropertyBackgroundImage: {
        for (FillLayer* background_layer = &style->AccessBackgroundLayers();
             background_layer; background_layer = background_layer->Next()) {
          StyleImage* background_image = background_layer->GetImage();
          if (background_image && background_image->IsPendingImage()) {
            FetchParameters::ImageRequestOptimization
                image_request_optimization = FetchParameters::kNone;
            if (!BackgroundLayerMayBeSprite(*background_layer)) {
              if (element_->GetDocument()
                      .GetFrame()
                      ->IsLazyLoadingImageAllowed()) {
                image_request_optimization = FetchParameters::kDeferImageLoad;
              } else {
                image_request_optimization = FetchParameters::kAllowPlaceholder;
              }
            }
            StyleImage* new_image =
                LoadPendingImage(style, ToStylePendingImage(background_image),
                                 image_request_optimization);
            if (new_image && new_image->IsLazyloadPossiblyDeferred())
              LazyLoadImageObserver::StartMonitoring(element_);
            background_layer->SetImage(new_image);
          }
        }
        break;
      }
      case CSSPropertyContent: {
        for (ContentData* content_data =
                 const_cast<ContentData*>(style->GetContentData());
             content_data; content_data = content_data->Next()) {
          if (content_data->IsImage()) {
            StyleImage* image = ToImageContentData(content_data)->GetImage();
            if (image->IsPendingImage()) {
              ToImageContentData(content_data)
                  ->SetImage(
                      LoadPendingImage(style, ToStylePendingImage(image),
                                       FetchParameters::kAllowPlaceholder));
            }
          }
        }
        break;
      }
      case CSSPropertyCursor: {
        if (CursorList* cursor_list = style->Cursors()) {
          for (wtf_size_t i = 0; i < cursor_list->size(); ++i) {
            CursorData& current_cursor = cursor_list->at(i);
            if (StyleImage* image = current_cursor.GetImage()) {
              if (image->IsPendingImage()) {
                // cursor images shouldn't be replaced with placeholders
                current_cursor.SetImage(LoadPendingImage(
                    style, ToStylePendingImage(image), FetchParameters::kNone));
              }
            }
          }
        }
        break;
      }
      case CSSPropertyListStyleImage: {
        if (style->ListStyleImage() &&
            style->ListStyleImage()->IsPendingImage()) {
          // List style images shouldn't be replaced with placeholders
          style->SetListStyleImage(LoadPendingImage(
              style, ToStylePendingImage(style->ListStyleImage()),
              FetchParameters::kNone));
        }
        break;
      }
      case CSSPropertyBorderImageSource: {
        if (style->BorderImageSource() &&
            style->BorderImageSource()->IsPendingImage()) {
          // Border images shouldn't be replaced with placeholders
          style->SetBorderImageSource(LoadPendingImage(
              style, ToStylePendingImage(style->BorderImageSource()),
              FetchParameters::kNone));
        }
        break;
      }
      case CSSPropertyWebkitBoxReflect: {
        if (StyleReflection* reflection = style->BoxReflect()) {
          const NinePieceImage& mask_image = reflection->Mask();
          if (mask_image.GetImage() &&
              mask_image.GetImage()->IsPendingImage()) {
            StyleImage* loaded_image = LoadPendingImage(
                style, ToStylePendingImage(mask_image.GetImage()),
                FetchParameters::kAllowPlaceholder);
            reflection->SetMask(NinePieceImage(
                loaded_image, mask_image.ImageSlices(), mask_image.Fill(),
                mask_image.BorderSlices(), mask_image.Outset(),
                mask_image.HorizontalRule(), mask_image.VerticalRule()));
          }
        }
        break;
      }
      case CSSPropertyWebkitMaskBoxImageSource: {
        if (style->MaskBoxImageSource() &&
            style->MaskBoxImageSource()->IsPendingImage()) {
          style->SetMaskBoxImageSource(LoadPendingImage(
              style, ToStylePendingImage(style->MaskBoxImageSource()),
              FetchParameters::kAllowPlaceholder));
        }
        break;
      }
      case CSSPropertyWebkitMaskImage: {
        for (FillLayer* mask_layer = &style->AccessMaskLayers(); mask_layer;
             mask_layer = mask_layer->Next()) {
          if (mask_layer->GetImage() &&
              mask_layer->GetImage()->IsPendingImage()) {
            mask_layer->SetImage(LoadPendingImage(
                style, ToStylePendingImage(mask_layer->GetImage()),
                FetchParameters::kAllowPlaceholder));
          }
        }
        break;
      }
      case CSSPropertyShapeOutside:
        if (style->ShapeOutside() && style->ShapeOutside()->GetImage() &&
            style->ShapeOutside()->GetImage()->IsPendingImage()) {
          style->ShapeOutside()->SetImage(LoadPendingImage(
              style, ToStylePendingImage(style->ShapeOutside()->GetImage()),
              FetchParameters::kAllowPlaceholder,
              kCrossOriginAttributeAnonymous));
        }
        break;
      default:
        NOTREACHED();
    }
  }
}

void ElementStyleResources::LoadPendingResources(
    ComputedStyle* computed_style) {
  LoadPendingImages(computed_style);
  LoadPendingSVGResources(computed_style);
}

}  // namespace blink
