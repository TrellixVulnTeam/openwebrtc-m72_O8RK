// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated from the Jinja2 template
// third_party/blink/renderer/bindings/templates/interface.cc.tmpl
// by the script code_generator_v8.py.
// DO NOT MODIFY!

// clang-format off
#include "third_party/blink/renderer/bindings/tests/results/core/v8_test_interface.h"

#include "base/memory/scoped_refptr.h"
#include "third_party/blink/renderer/bindings/core/v8/idl_types.h"
#include "third_party/blink/renderer/bindings/core/v8/native_value_traits_impl.h"
#include "third_party/blink/renderer/bindings/core/v8/script_promise.h"
#include "third_party/blink/renderer/bindings/core/v8/script_value.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_dom_configuration.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_element.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_event_listener_helper.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_iterator.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_node.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_test_interface.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_test_interface_2.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_test_interface_empty.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_window.h"
#include "third_party/blink/renderer/bindings/tests/idls/core/test_implements_2.h"
#include "third_party/blink/renderer/bindings/tests/idls/core/test_implements_3_implementation.h"
#include "third_party/blink/renderer/bindings/tests/idls/core/test_interface_partial.h"
#include "third_party/blink/renderer/bindings/tests/idls/core/test_interface_partial_2_implementation.h"
#include "third_party/blink/renderer/bindings/tests/idls/core/test_interface_partial_secure_context.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/frame/use_counter.h"
#include "third_party/blink/renderer/core/inspector/console_message.h"
#include "third_party/blink/renderer/platform/bindings/exception_messages.h"
#include "third_party/blink/renderer/platform/bindings/exception_state.h"
#include "third_party/blink/renderer/platform/bindings/runtime_call_stats.h"
#include "third_party/blink/renderer/platform/bindings/script_state.h"
#include "third_party/blink/renderer/platform/bindings/v8_object_constructor.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/get_ptr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
WrapperTypeInfo V8TestInterface::wrapperTypeInfo = {
    gin::kEmbedderBlink,
    V8TestInterface::DomTemplate,
    V8TestInterface::InstallConditionalFeatures,
    "TestInterface",
    &V8TestInterfaceEmpty::wrapperTypeInfo,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kObjectClassId,
    WrapperTypeInfo::kInheritFromActiveScriptWrappable,
};
#if defined(COMPONENT_BUILD) && defined(WIN32) && defined(__clang__)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestInterfaceImplementation.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// platform/bindings/ScriptWrappable.h.
const WrapperTypeInfo& TestInterfaceImplementation::wrapper_type_info_ = V8TestInterface::wrapperTypeInfo;

// [ActiveScriptWrappable]
static_assert(
    std::is_base_of<ActiveScriptWrappableBase, TestInterfaceImplementation>::value,
    "TestInterfaceImplementation does not inherit from ActiveScriptWrappable<>, but specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    !std::is_same<decltype(&TestInterfaceImplementation::HasPendingActivity),
                  decltype(&ScriptWrappable::HasPendingActivity)>::value,
    "TestInterfaceImplementation is not overriding hasPendingActivity(), but is specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace test_interface_implementation_v8_internal {
static void (*voidMethodPartialOverloadMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;
static void (*staticVoidMethodPartialOverloadMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;
static void (*promiseMethodPartialOverloadMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;
static void (*staticPromiseMethodPartialOverloadMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;
static void (*partial2VoidMethodMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;
static void (*partial2StaticVoidMethodMethodForPartialInterface)(const v8::FunctionCallbackInfo<v8::Value>&) = 0;

static void TestInterfaceAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->testInterfaceAttribute()), impl);
}

static void TestInterfaceAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "testInterfaceAttribute");

  // Prepare the value to be set.
  TestInterfaceImplementation* cppValue = V8TestInterface::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  // Type check per: http://heycam.github.io/webidl/#es-interface
  if (!cppValue) {
    exceptionState.ThrowTypeError("The provided value is not of type 'TestInterface'.");
    return;
  }

  impl->setTestInterfaceAttribute(cppValue);
}

static void DoubleAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValue(info, impl->doubleAttribute());
}

static void DoubleAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "doubleAttribute");

  // Prepare the value to be set.
  double cppValue = NativeValueTraits<IDLDouble>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setDoubleAttribute(cppValue);
}

static void FloatAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValue(info, impl->floatAttribute());
}

static void FloatAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "floatAttribute");

  // Prepare the value to be set.
  float cppValue = NativeValueTraits<IDLFloat>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setFloatAttribute(cppValue);
}

static void UnrestrictedDoubleAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValue(info, impl->unrestrictedDoubleAttribute());
}

static void UnrestrictedDoubleAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "unrestrictedDoubleAttribute");

  // Prepare the value to be set.
  double cppValue = NativeValueTraits<IDLUnrestrictedDouble>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setUnrestrictedDoubleAttribute(cppValue);
}

static void UnrestrictedFloatAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValue(info, impl->unrestrictedFloatAttribute());
}

static void UnrestrictedFloatAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "unrestrictedFloatAttribute");

  // Prepare the value to be set.
  float cppValue = NativeValueTraits<IDLUnrestrictedFloat>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setUnrestrictedFloatAttribute(cppValue);
}

static void TestEnumAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, impl->testEnumAttribute(), info.GetIsolate());
}

static void TestEnumAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "testEnumAttribute");

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  // Type check per: http://heycam.github.io/webidl/#dfn-attribute-setter
  // Returns undefined without setting the value if the value is invalid.
  DummyExceptionStateForTesting dummyExceptionState;
  const char* validValues[] = {
      "",
      "EnumValue1",
      "EnumValue2",
      "EnumValue3",
  };
  if (!IsValidEnum(cppValue, validValues, base::size(validValues), "TestEnum", dummyExceptionState)) {
    ExecutionContext::ForCurrentRealm(info)->AddConsoleMessage(
        ConsoleMessage::Create(kJSMessageSource, kWarningMessageLevel,
                               dummyExceptionState.Message()));
    return;
  }

  impl->setTestEnumAttribute(cppValue);
}

static void TestEnumOrNullAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueStringOrNull(info, impl->testEnumOrNullAttribute(), info.GetIsolate());
}

static void TestEnumOrNullAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "testEnumOrNullAttribute");

  // Prepare the value to be set.
  V8StringResource<kTreatNullAndUndefinedAsNullString> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  // Type check per: http://heycam.github.io/webidl/#dfn-attribute-setter
  // Returns undefined without setting the value if the value is invalid.
  DummyExceptionStateForTesting dummyExceptionState;
  const char* validValues[] = {
      nullptr,
      "",
      "EnumValue1",
      "EnumValue2",
      "EnumValue3",
  };
  if (!IsValidEnum(cppValue, validValues, base::size(validValues), "TestEnum", dummyExceptionState)) {
    ExecutionContext::ForCurrentRealm(info)->AddConsoleMessage(
        ConsoleMessage::Create(kJSMessageSource, kWarningMessageLevel,
                               dummyExceptionState.Message()));
    return;
  }

  impl->setTestEnumOrNullAttribute(cppValue);
}

static void StringOrDoubleAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  StringOrDouble result;
  impl->stringOrDoubleAttribute(result);

  V8SetReturnValue(info, result);
}

static void StringOrDoubleAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "stringOrDoubleAttribute");

  // Prepare the value to be set.
  StringOrDouble cppValue;
  V8StringOrDouble::ToImpl(info.GetIsolate(), v8Value, cppValue, UnionTypeConversionMode::kNotNullable, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setStringOrDoubleAttribute(cppValue);
}

static void WithExtendedAttributeStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->withExtendedAttributeStringAttribute());
}

static void WithExtendedAttributeStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "withExtendedAttributeStringAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLongEnforceRange>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setWithExtendedAttributeStringAttribute(cppValue);
}

static void UncapitalAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->CapitalImplementation()), impl);
}

static void UncapitalAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "uncapitalAttribute");

  // Prepare the value to be set.
  Implementation* cppValue = V8Implementation::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  // Type check per: http://heycam.github.io/webidl/#es-interface
  if (!cppValue) {
    exceptionState.ThrowTypeError("The provided value is not of type 'Implementation'.");
    return;
  }

  impl->setCapitalImplementation(cppValue);
}

static void ConditionalLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->conditionalLongAttribute());
}

static void ConditionalLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "conditionalLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setConditionalLongAttribute(cppValue);
}

static void ConditionalReadOnlyLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->conditionalReadOnlyLongAttribute());
}

static void StaticStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueString(info, TestInterfaceImplementation::staticStringAttribute(), info.GetIsolate());
}

static void StaticStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestInterfaceImplementation::setStaticStringAttribute(cppValue);
}

static void StaticReturnDOMWrapperAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValue(info, WTF::GetPtr(TestInterfaceImplementation::staticReturnDOMWrapperAttribute()), info.GetIsolate()->GetCurrentContext()->Global());
}

static void StaticReturnDOMWrapperAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "staticReturnDOMWrapperAttribute");

  // Prepare the value to be set.
  TestInterfaceImplementation* cppValue = V8TestInterface::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  // Type check per: http://heycam.github.io/webidl/#es-interface
  if (!cppValue) {
    exceptionState.ThrowTypeError("The provided value is not of type 'TestInterface'.");
    return;
  }

  TestInterfaceImplementation::setStaticReturnDOMWrapperAttribute(cppValue);
}

static void StaticReadOnlyStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueString(info, TestInterfaceImplementation::staticReadOnlyStringAttribute(), info.GetIsolate());
}

static void StaticReadOnlyReturnDOMWrapperAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValue(info, WTF::GetPtr(TestInterfaceImplementation::staticReadOnlyReturnDOMWrapperAttribute()), info.GetIsolate()->GetCurrentContext()->Global());
}

static void StaticConditionalReadOnlyLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueInt(info, TestInterfaceImplementation::staticConditionalReadOnlyLongAttribute());
}

static void LegacyInterfaceTypeCheckingAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->legacyInterfaceTypeCheckingAttribute()), impl);
}

static void LegacyInterfaceTypeCheckingAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  TestInterfaceEmpty* cppValue = V8TestInterfaceEmpty::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  impl->setLegacyInterfaceTypeCheckingAttribute(cppValue);
}

static void StringNullAsEmptyAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, impl->stringNullAsEmptyAttribute(), info.GetIsolate());
}

static void StringNullAsEmptyAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  V8StringResource<kTreatNullAsEmptyString> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  impl->setStringNullAsEmptyAttribute(cppValue);
}

static void UsvStringOrNullAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueStringOrNull(info, impl->usvStringOrNullAttribute(), info.GetIsolate());
}

static void UsvStringOrNullAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "usvStringOrNullAttribute");

  // Prepare the value to be set.
  V8StringResource<kTreatNullAndUndefinedAsNullString> cppValue = NativeValueTraits<IDLUSVStringOrNull>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setUsvStringOrNullAttribute(cppValue);
}

static void AlwaysExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->alwaysExposedAttribute());
}

static void AlwaysExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "alwaysExposedAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setAlwaysExposedAttribute(cppValue);
}

static void WorkerExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->workerExposedAttribute());
}

static void WorkerExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "workerExposedAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setWorkerExposedAttribute(cppValue);
}

static void WindowExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, impl->windowExposedAttribute());
}

static void WindowExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "windowExposedAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setWindowExposedAttribute(cppValue);
}

static void LenientThisAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  // [LenientThis]
  // Make sure that info.Holder() really points to an instance if [LenientThis].
  if (!V8TestInterface::HasInstance(info.Holder(), info.GetIsolate()))
    return; // Return silently because of [LenientThis].

  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValue(info, impl->lenientThisAttribute().V8Value());
}

static void LenientThisAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  // [LenientThis]
  // Make sure that info.Holder() really points to an instance if [LenientThis].
  if (!V8TestInterface::HasInstance(holder, isolate))
    return; // Return silently because of [LenientThis].

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  ScriptValue cppValue = ScriptValue(ScriptState::Current(info.GetIsolate()), v8Value);

  impl->setLenientThisAttribute(cppValue);
}

static void AttributeWithSideEffectFreeGetterAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->attributeWithSideEffectFreeGetter());
}

static void AttributeWithSideEffectFreeGetterAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "attributeWithSideEffectFreeGetter");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setAttributeWithSideEffectFreeGetter(cppValue);
}

static void SecureContextAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextAttribute());
}

static void SecureContextAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextAttribute(cppValue);
}

static void SecureContextRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextRuntimeEnabledAttribute());
}

static void SecureContextRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextRuntimeEnabledAttribute(cppValue);
}

static void SecureContextnessRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextnessRuntimeEnabledAttribute());
}

static void SecureContextnessRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextnessRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextnessRuntimeEnabledAttribute(cppValue);
}

static void SecureContextWindowExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextWindowExposedAttribute());
}

static void SecureContextWindowExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextWindowExposedAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextWindowExposedAttribute(cppValue);
}

static void SecureContextWorkerExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextWorkerExposedAttribute());
}

static void SecureContextWorkerExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextWorkerExposedAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextWorkerExposedAttribute(cppValue);
}

static void SecureContextWindowExposedRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextWindowExposedRuntimeEnabledAttribute());
}

static void SecureContextWindowExposedRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextWindowExposedRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextWindowExposedRuntimeEnabledAttribute(cppValue);
}

static void SecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, impl->secureContextWorkerExposedRuntimeEnabledAttribute());
}

static void SecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "secureContextWorkerExposedRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->setSecureContextWorkerExposedRuntimeEnabledAttribute(cppValue);
}

static void ImplementsStaticReadOnlyLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueInt(info, TestInterfaceImplementation::implementsStaticReadOnlyLongAttribute());
}

static void ImplementsStaticStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueString(info, TestInterfaceImplementation::implementsStaticStringAttribute(), info.GetIsolate());
}

static void ImplementsStaticStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestInterfaceImplementation::setImplementsStaticStringAttribute(cppValue);
}

static void ImplementsReadonlyStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, impl->implementsReadonlyStringAttribute(), info.GetIsolate());
}

static void ImplementsStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, impl->implementsStringAttribute(), info.GetIsolate());
}

static void ImplementsStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  impl->setImplementsStringAttribute(cppValue);
}

static void ImplementsNodeAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->implementsNodeAttribute()), impl);
}

static void ImplementsNodeAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "implementsNodeAttribute");

  // Prepare the value to be set.
  Node* cppValue = V8Node::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  // Type check per: http://heycam.github.io/webidl/#es-interface
  if (!cppValue) {
    exceptionState.ThrowTypeError("The provided value is not of type 'Node'.");
    return;
  }

  impl->setImplementsNodeAttribute(cppValue);
}

static void ImplementsEventHandlerAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  EventListener* cppValue(WTF::GetPtr(impl->implementsEventHandlerAttribute()));

  V8SetReturnValue(info, JSBasedEventListener::GetListenerOrNull(info.GetIsolate(), impl, cppValue));
}

static void ImplementsEventHandlerAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.

  impl->setImplementsEventHandlerAttribute(V8EventListenerHelper::GetEventHandler(ScriptState::ForRelevantRealm(info), v8Value, JSEventHandler::HandlerType::kEventHandler, kListenerFindOrCreate));
}

static void ImplementsRuntimeEnabledNodeAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->implementsRuntimeEnabledNodeAttribute()), impl);
}

static void ImplementsRuntimeEnabledNodeAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "implementsRuntimeEnabledNodeAttribute");

  // Prepare the value to be set.
  Node* cppValue = V8Node::ToImplWithTypeCheck(info.GetIsolate(), v8Value);

  // Type check per: http://heycam.github.io/webidl/#es-interface
  if (!cppValue) {
    exceptionState.ThrowTypeError("The provided value is not of type 'Node'.");
    return;
  }

  impl->setImplementsRuntimeEnabledNodeAttribute(cppValue);
}

static void Implements2StaticStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueString(info, TestImplements2::implements2StaticStringAttribute(), info.GetIsolate());
}

static void Implements2StaticStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestImplements2::setImplements2StaticStringAttribute(cppValue);
}

static void Implements2StringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, TestImplements2::implements2StringAttribute(*impl), info.GetIsolate());
}

static void Implements2StringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestImplements2::setImplements2StringAttribute(*impl, cppValue);
}

static void Implements3StringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, TestImplements3Implementation::implements3StringAttribute(*impl), info.GetIsolate());
}

static void Implements3StringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestImplements3Implementation::setImplements3StringAttribute(*impl, cppValue);
}

static void Implements3StaticStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueString(info, TestImplements3Implementation::implements3StaticStringAttribute(), info.GetIsolate());
}

static void Implements3StaticStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  TestImplements3Implementation::setImplements3StaticStringAttribute(cppValue);
}

static void PartialLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, TestInterfacePartial::partialLongAttribute(*impl));
}

static void PartialLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial::setPartialLongAttribute(*impl, cppValue);
}

static void PartialStaticLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueInt(info, TestInterfacePartial::partialStaticLongAttribute());
}

static void PartialStaticLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialStaticLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial::setPartialStaticLongAttribute(cppValue);
}

static void PartialCallWithExecutionContextLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExecutionContext* executionContext = ExecutionContext::ForRelevantRealm(info);

  V8SetReturnValueInt(info, TestInterfacePartial::partialCallWithExecutionContextLongAttribute(executionContext, *impl));
}

static void PartialCallWithExecutionContextLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialCallWithExecutionContextLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  ExecutionContext* executionContext = ExecutionContext::ForRelevantRealm(info);

  TestInterfacePartial::setPartialCallWithExecutionContextLongAttribute(executionContext, *impl, cppValue);
}

static void PartialPartialEnumTypeAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueString(info, TestInterfacePartial::partialPartialEnumTypeAttribute(*impl), info.GetIsolate());
}

static void PartialPartialEnumTypeAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialPartialEnumTypeAttribute");

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.Prepare())
    return;

  // Type check per: http://heycam.github.io/webidl/#dfn-attribute-setter
  // Returns undefined without setting the value if the value is invalid.
  DummyExceptionStateForTesting dummyExceptionState;
  const char* validValues[] = {
      "foo",
      "bar",
  };
  if (!IsValidEnum(cppValue, validValues, base::size(validValues), "PartialEnumType", dummyExceptionState)) {
    ExecutionContext::ForCurrentRealm(info)->AddConsoleMessage(
        ConsoleMessage::Create(kJSMessageSource, kWarningMessageLevel,
                               dummyExceptionState.Message()));
    return;
  }

  TestInterfacePartial::setPartialPartialEnumTypeAttribute(*impl, cppValue);
}

static void PartialSecureContextLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, TestInterfacePartial::partialSecureContextLongAttribute(*impl));
}

static void PartialSecureContextLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial::setPartialSecureContextLongAttribute(*impl, cppValue);
}

static void Partial2LongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueInt(info, TestInterfacePartial2Implementation::partial2LongAttribute(*impl));
}

static void Partial2LongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partial2LongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial2Implementation::setPartial2LongAttribute(*impl, cppValue);
}

static void Partial2StaticLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValueInt(info, TestInterfacePartial2Implementation::partial2StaticLongAttribute());
}

static void Partial2StaticLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partial2StaticLongAttribute");

  // Prepare the value to be set.
  int32_t cppValue = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial2Implementation::setPartial2StaticLongAttribute(cppValue);
}

static void Partial2SecureContextAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartial2Implementation::partial2SecureContextAttribute(*impl));
}

static void Partial2SecureContextAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partial2SecureContextAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial2Implementation::setPartial2SecureContextAttribute(*impl, cppValue);
}

static void PartialSecureContextAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextAttribute(*impl));
}

static void PartialSecureContextAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextAttribute(*impl, cppValue);
}

static void PartialSecureContextRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextRuntimeEnabledAttribute(*impl));
}

static void PartialSecureContextRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextRuntimeEnabledAttribute(*impl, cppValue);
}

static void PartialSecureContextWindowExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextWindowExposedAttribute(*impl));
}

static void PartialSecureContextWindowExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextWindowExposedAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextWindowExposedAttribute(*impl, cppValue);
}

static void PartialSecureContextWorkerExposedAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextWorkerExposedAttribute(*impl));
}

static void PartialSecureContextWorkerExposedAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextWorkerExposedAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextWorkerExposedAttribute(*impl, cppValue);
}

static void PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextWindowExposedRuntimeEnabledAttribute(*impl));
}

static void PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextWindowExposedRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextWindowExposedRuntimeEnabledAttribute(*impl, cppValue);
}

static void PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  V8SetReturnValueBool(info, TestInterfacePartialSecureContext::partialSecureContextWorkerExposedRuntimeEnabledAttribute(*impl));
}

static void PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(holder);

  ExceptionState exceptionState(isolate, ExceptionState::kSetterContext, "TestInterface", "partialSecureContextWorkerExposedRuntimeEnabledAttribute");

  // Prepare the value to be set.
  bool cppValue = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), v8Value, exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartialSecureContext::setPartialSecureContextWorkerExposedRuntimeEnabledAttribute(*impl, cppValue);
}

static void VoidMethodTestInterfaceEmptyArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodTestInterfaceEmptyArg", "TestInterface", ExceptionMessages::NotEnoughArguments(1, info.Length())));
    return;
  }

  TestInterfaceEmpty* testInterfaceEmptyArg;
  testInterfaceEmptyArg = V8TestInterfaceEmpty::ToImplWithTypeCheck(info.GetIsolate(), info[0]);
  if (!testInterfaceEmptyArg) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodTestInterfaceEmptyArg", "TestInterface", "parameter 1 is not of type 'TestInterfaceEmpty'."));
    return;
  }

  impl->voidMethodTestInterfaceEmptyArg(testInterfaceEmptyArg);
}

static void VoidMethodDoubleArgFloatArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "voidMethodDoubleArgFloatArg");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 2)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(2, info.Length()));
    return;
  }

  double doubleArg;
  float floatArg;
  doubleArg = NativeValueTraits<IDLDouble>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  floatArg = NativeValueTraits<IDLFloat>::NativeValue(info.GetIsolate(), info[1], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->voidMethodDoubleArgFloatArg(doubleArg, floatArg);
}

static void VoidMethodNullableAndOptionalObjectArgsMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 2)) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodNullableAndOptionalObjectArgs", "TestInterface", ExceptionMessages::NotEnoughArguments(2, info.Length())));
    return;
  }

  ScriptValue objectArg;
  ScriptValue nullableObjectArg;
  ScriptValue optionalObjectArg;
  int numArgsPassed = info.Length();
  while (numArgsPassed > 0) {
    if (!info[numArgsPassed - 1]->IsUndefined())
      break;
    --numArgsPassed;
  }
  if (info[0]->IsObject()) {
    objectArg = ScriptValue(ScriptState::Current(info.GetIsolate()), info[0]);
  } else {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodNullableAndOptionalObjectArgs", "TestInterface", "parameter 1 ('objectArg') is not an object."));
    return;
  }

  if (info[1]->IsObject()) {
    nullableObjectArg = ScriptValue(ScriptState::Current(info.GetIsolate()), info[1]);
  } else if (info[1]->IsNullOrUndefined()) {
    nullableObjectArg = ScriptValue(ScriptState::Current(info.GetIsolate()), v8::Null(info.GetIsolate()));
  } else {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodNullableAndOptionalObjectArgs", "TestInterface", "parameter 2 ('nullableObjectArg') is not an object."));
    return;
  }

  if (UNLIKELY(numArgsPassed <= 2)) {
    impl->voidMethodNullableAndOptionalObjectArgs(objectArg, nullableObjectArg);
    return;
  }
  if (info[2]->IsObject()) {
    optionalObjectArg = ScriptValue(ScriptState::Current(info.GetIsolate()), info[2]);
  } else if (info[2]->IsUndefined()) {
    optionalObjectArg = ScriptValue(ScriptState::Current(info.GetIsolate()), v8::Undefined(info.GetIsolate()));
  } else {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodNullableAndOptionalObjectArgs", "TestInterface", "parameter 3 ('optionalObjectArg') is not an object."));
    return;
  }

  impl->voidMethodNullableAndOptionalObjectArgs(objectArg, nullableObjectArg, optionalObjectArg);
}

static void VoidMethodUnrestrictedDoubleArgUnrestrictedFloatArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "voidMethodUnrestrictedDoubleArgUnrestrictedFloatArg");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 2)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(2, info.Length()));
    return;
  }

  double unrestrictedDoubleArg;
  float unrestrictedFloatArg;
  unrestrictedDoubleArg = NativeValueTraits<IDLUnrestrictedDouble>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  unrestrictedFloatArg = NativeValueTraits<IDLUnrestrictedFloat>::NativeValue(info.GetIsolate(), info[1], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->voidMethodUnrestrictedDoubleArgUnrestrictedFloatArg(unrestrictedDoubleArg, unrestrictedFloatArg);
}

static void VoidMethodTestEnumArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "voidMethodTestEnumArg");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  V8StringResource<> testEnumArg;
  testEnumArg = info[0];
  if (!testEnumArg.Prepare())
    return;
  const char* validTestEnumArgValues[] = {
      "",
      "EnumValue1",
      "EnumValue2",
      "EnumValue3",
  };
  if (!IsValidEnum(testEnumArg, validTestEnumArgValues, base::size(validTestEnumArgValues), "TestEnum", exceptionState)) {
    return;
  }

  impl->voidMethodTestEnumArg(testEnumArg);
}

static void VoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->voidMethod();
}

static void VoidMethodMethodForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->voidMethod();
}

static void AlwaysExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->alwaysExposedMethod();
}

static void WorkerExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->workerExposedMethod();
}

static void WindowExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->windowExposedMethod();
}

static void AlwaysExposedStaticMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation::alwaysExposedStaticMethod();
}

static void WorkerExposedStaticMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation::workerExposedStaticMethod();
}

static void WindowExposedStaticMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation::windowExposedStaticMethod();
}

static void StaticReturnDOMWrapperMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValue(info, TestInterfaceImplementation::staticReturnDOMWrapperMethod(), info.GetIsolate()->GetCurrentContext()->Global());
}

static void MethodWithExposedAndRuntimeEnabledFlagMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->methodWithExposedAndRuntimeEnabledFlag();
}

static void OverloadMethodWithExposedAndRuntimeEnabledFlag1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "overloadMethodWithExposedAndRuntimeEnabledFlag");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  int32_t longArg;
  longArg = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->overloadMethodWithExposedAndRuntimeEnabledFlag(longArg);
}

static void OverloadMethodWithExposedAndRuntimeEnabledFlag2Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  V8StringResource<> string;
  string = info[0];
  if (!string.Prepare())
    return;

  impl->overloadMethodWithExposedAndRuntimeEnabledFlag(string);
}

static void OverloadMethodWithExposedAndRuntimeEnabledFlag3Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  DOMWindow* window;
  window = ToDOMWindow(info.GetIsolate(), info[0]);
  if (!window) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("overloadMethodWithExposedAndRuntimeEnabledFlag", "TestInterface", "parameter 1 is not of type 'Window'."));
    return;
  }

  impl->overloadMethodWithExposedAndRuntimeEnabledFlag(window);
}

static void OverloadMethodWithExposedAndRuntimeEnabledFlagMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  bool isArityError = false;

  switch (std::min(1, info.Length())) {
    case 1:
      if (RuntimeEnabledFeatures::FeatureName2Enabled()) {
        if (V8Window::HasInstance(info[0], info.GetIsolate())) {
          OverloadMethodWithExposedAndRuntimeEnabledFlag3Method(info);
          return;
        }
      }
      if (info[0]->IsNumber()) {
        OverloadMethodWithExposedAndRuntimeEnabledFlag1Method(info);
        return;
      }
      if (RuntimeEnabledFeatures::FeatureNameEnabled()) {
        if (true) {
          OverloadMethodWithExposedAndRuntimeEnabledFlag2Method(info);
          return;
        }
      }
      if (true) {
        OverloadMethodWithExposedAndRuntimeEnabledFlag1Method(info);
        return;
      }
      break;
    default:
      isArityError = true;
  }

  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "overloadMethodWithExposedAndRuntimeEnabledFlag");
  if (isArityError) {
    if (info.Length() < 1) {
      exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
      return;
    }
  }
  exceptionState.ThrowTypeError("No function was found that matched the signature provided.");
}

static void MethodWithExposedHavingRuntimeEnabldFlagMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->methodWithExposedHavingRuntimeEnabldFlag();
}

static void WindowAndServiceWorkerExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->windowAndServiceWorkerExposedMethod();
}

static void VoidMethodPartialOverload1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->voidMethodPartialOverload();
}

static void VoidMethodPartialOverload2Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "voidMethodPartialOverload");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  double doubleArg;
  doubleArg = NativeValueTraits<IDLDouble>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->voidMethodPartialOverload(doubleArg);
}

static void StaticVoidMethodPartialOverload1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation::staticVoidMethodPartialOverload();
}

static void PromiseMethodPartialOverload1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "promiseMethodPartialOverload");
  ExceptionToRejectPromiseScope rejectPromiseScope(info, exceptionState);

  // V8DOMConfiguration::kDoNotCheckHolder
  // Make sure that info.Holder() really points to an instance of the type.
  if (!V8TestInterface::HasInstance(info.Holder(), info.GetIsolate())) {
    exceptionState.ThrowTypeError("Illegal invocation");
    return;
  }
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  V8SetReturnValue(info, impl->promiseMethodPartialOverload().V8Value());
}

static void PromiseMethodPartialOverload2Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "promiseMethodPartialOverload");
  ExceptionToRejectPromiseScope rejectPromiseScope(info, exceptionState);

  // V8DOMConfiguration::kDoNotCheckHolder
  // Make sure that info.Holder() really points to an instance of the type.
  if (!V8TestInterface::HasInstance(info.Holder(), info.GetIsolate())) {
    exceptionState.ThrowTypeError("Illegal invocation");
    return;
  }
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  DOMWindow* window;
  window = ToDOMWindow(info.GetIsolate(), info[0]);
  if (!window) {
    exceptionState.ThrowTypeError("parameter 1 is not of type 'Window'.");
    return;
  }

  V8SetReturnValue(info, impl->promiseMethodPartialOverload(window).V8Value());
}

static void StaticPromiseMethodPartialOverload1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  V8SetReturnValue(info, TestInterfaceImplementation::staticPromiseMethodPartialOverload().V8Value());
}

static void OverloadMethodWithUnionTypeWithStringMember1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "overloadMethodWithUnionTypeWithStringMember");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  DoubleOrString unionArg;
  V8DoubleOrString::ToImpl(info.GetIsolate(), info[0], unionArg, UnionTypeConversionMode::kNotNullable, exceptionState);
  if (exceptionState.HadException())
    return;

  impl->overloadMethodWithUnionTypeWithStringMember(unionArg);
}

static void OverloadMethodWithUnionTypeWithStringMember2Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "overloadMethodWithUnionTypeWithStringMember");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  bool boolArg;
  boolArg = NativeValueTraits<IDLBoolean>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->overloadMethodWithUnionTypeWithStringMember(boolArg);
}

static void OverloadMethodWithUnionTypeWithStringMemberMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  bool isArityError = false;

  switch (std::min(1, info.Length())) {
    case 1:
      if (info[0]->IsBoolean()) {
        OverloadMethodWithUnionTypeWithStringMember2Method(info);
        return;
      }
      if (true) {
        OverloadMethodWithUnionTypeWithStringMember1Method(info);
        return;
      }
      if (true) {
        OverloadMethodWithUnionTypeWithStringMember2Method(info);
        return;
      }
      break;
    default:
      isArityError = true;
  }

  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "overloadMethodWithUnionTypeWithStringMember");
  if (isArityError) {
    if (info.Length() < 1) {
      exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
      return;
    }
  }
  exceptionState.ThrowTypeError("No function was found that matched the signature provided.");
}

static void LegacyInterfaceTypeCheckingMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("legacyInterfaceTypeCheckingMethod", "TestInterface", ExceptionMessages::NotEnoughArguments(1, info.Length())));
    return;
  }

  TestInterfaceEmpty* testInterfaceEmptyArg;
  testInterfaceEmptyArg = V8TestInterfaceEmpty::ToImplWithTypeCheck(info.GetIsolate(), info[0]);

  impl->legacyInterfaceTypeCheckingMethod(testInterfaceEmptyArg);
}

static void SideEffectFreeMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->sideEffectFreeMethod();
}

static void SecureContextMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextMethod();
}

static void SecureContextRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextRuntimeEnabledMethod();
}

static void SecureContextnessRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextnessRuntimeEnabledMethod();
}

static void SecureContextWindowExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextWindowExposedMethod();
}

static void SecureContextWorkerExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextWorkerExposedMethod();
}

static void SecureContextWindowExposedRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextWindowExposedRuntimeEnabledMethod();
}

static void SecureContextWorkerExposedRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->secureContextWorkerExposedRuntimeEnabledMethod();
}

static void MethodWithNullableSequencesMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "methodWithNullableSequences");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 4)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(4, info.Length()));
    return;
  }

  Vector<base::Optional<double>> numbers;
  Vector<String> strings;
  HeapVector<Member<Element>> elements;
  HeapVector<DoubleOrString> unions;
  numbers = NativeValueTraits<IDLSequence<IDLNullable<IDLDouble>>>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  strings = NativeValueTraits<IDLSequence<IDLStringOrNull>>::NativeValue(info.GetIsolate(), info[1], exceptionState);
  if (exceptionState.HadException())
    return;

  elements = NativeValueTraits<IDLSequence<IDLNullable<Element>>>::NativeValue(info.GetIsolate(), info[2], exceptionState);
  if (exceptionState.HadException())
    return;

  unions = NativeValueTraits<IDLSequence<IDLNullable<DoubleOrString>>>::NativeValue(info.GetIsolate(), info[3], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->methodWithNullableSequences(numbers, strings, elements, unions);
}

static void MethodWithNullableRecordsMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "methodWithNullableRecords");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 4)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(4, info.Length()));
    return;
  }

  Vector<std::pair<String, base::Optional<double>>> numbers;
  Vector<std::pair<String, String>> strings;
  HeapVector<std::pair<String, Member<Element>>> elements;
  HeapVector<std::pair<String, DoubleOrString>> unions;
  numbers = NativeValueTraits<IDLRecord<IDLString, IDLNullable<IDLDouble>>>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  strings = NativeValueTraits<IDLRecord<IDLString, IDLStringOrNull>>::NativeValue(info.GetIsolate(), info[1], exceptionState);
  if (exceptionState.HadException())
    return;

  elements = NativeValueTraits<IDLRecord<IDLString, IDLNullable<Element>>>::NativeValue(info.GetIsolate(), info[2], exceptionState);
  if (exceptionState.HadException())
    return;

  unions = NativeValueTraits<IDLRecord<IDLString, IDLNullable<DoubleOrString>>>::NativeValue(info.GetIsolate(), info[3], exceptionState);
  if (exceptionState.HadException())
    return;

  impl->methodWithNullableRecords(numbers, strings, elements, unions);
}

static void ImplementsVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  impl->implementsVoidMethod();
}

static void ImplementsComplexMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "implementsComplexMethod");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 2)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(2, info.Length()));
    return;
  }

  V8StringResource<> strArg;
  TestInterfaceEmpty* testInterfaceEmptyArg;
  strArg = info[0];
  if (!strArg.Prepare())
    return;

  testInterfaceEmptyArg = V8TestInterfaceEmpty::ToImplWithTypeCheck(info.GetIsolate(), info[1]);
  if (!testInterfaceEmptyArg) {
    exceptionState.ThrowTypeError("parameter 2 is not of type 'TestInterfaceEmpty'.");
    return;
  }

  ExecutionContext* executionContext = ExecutionContext::ForRelevantRealm(info);
  TestInterfaceEmpty* result = impl->implementsComplexMethod(executionContext, strArg, testInterfaceEmptyArg, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
  V8SetReturnValue(info, result);
}

static void ImplementsStaticVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation::implementsStaticVoidMethod();
}

static void Implements2VoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestImplements2::implements2VoidMethod(*impl);
}

static void Implements3VoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestImplements3Implementation::implements3VoidMethod(*impl);
}

static void Implements3StaticVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestImplements3Implementation::implements3StaticVoidMethod();
}

static void PartialVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartial::partialVoidMethod(*impl);
}

static void PartialStaticVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfacePartial::partialStaticVoidMethod();
}

static void PartialVoidMethodLongArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "partialVoidMethodLongArg");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  int32_t longArg;
  longArg = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.HadException())
    return;

  TestInterfacePartial::partialVoidMethodLongArg(*impl, longArg);
}

static void PartialCallWithExecutionContextRaisesExceptionVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "partialCallWithExecutionContextRaisesExceptionVoidMethod");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ExecutionContext* executionContext = ExecutionContext::ForRelevantRealm(info);
  TestInterfacePartial::partialCallWithExecutionContextRaisesExceptionVoidMethod(executionContext, *impl, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
}

static void PartialVoidMethodPartialCallbackTypeArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("partialVoidMethodPartialCallbackTypeArg", "TestInterface", ExceptionMessages::NotEnoughArguments(1, info.Length())));
    return;
  }

  ScriptValue partialCallbackTypeArg;
  if (info[0]->IsFunction()) {
    partialCallbackTypeArg = ScriptValue(ScriptState::Current(info.GetIsolate()), info[0]);
  } else {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("partialVoidMethodPartialCallbackTypeArg", "TestInterface", "The callback provided as parameter 1 is not a function."));
    return;
  }

  TestInterfacePartial::partialVoidMethodPartialCallbackTypeArg(*impl, partialCallbackTypeArg);
}

static void Partial2VoidMethod1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartial2Implementation::partial2VoidMethod(*impl);
}

static void Partial2StaticVoidMethod1Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfacePartial2Implementation::partial2StaticVoidMethod();
}

static void Partial2SecureContextMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartial2Implementation::partial2SecureContextMethod(*impl);
}

static void PartialSecureContextMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextMethod(*impl);
}

static void PartialSecureContextRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextRuntimeEnabledMethod(*impl);
}

static void PartialSecureContextWindowExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextWindowExposedMethod(*impl);
}

static void PartialSecureContextWorkerExposedMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextWorkerExposedMethod(*impl);
}

static void PartialSecureContextWindowExposedRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextWindowExposedRuntimeEnabledMethod(*impl);
}

static void PartialSecureContextWorkerExposedRuntimeEnabledMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  TestInterfacePartialSecureContext::partialSecureContextWorkerExposedRuntimeEnabledMethod(*impl);
}

static void VoidMethodPartialOverloadMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        VoidMethodPartialOverload1Method(info);
        return;
      }
      break;
    case 1:
      if (info[0]->IsNumber()) {
        VoidMethodPartialOverload2Method(info);
        return;
      }
      if (true) {
        VoidMethodPartialOverload2Method(info);
        return;
      }
      break;
  }

  DCHECK(voidMethodPartialOverloadMethodForPartialInterface);
  (voidMethodPartialOverloadMethodForPartialInterface)(info);
}

static void StaticVoidMethodPartialOverloadMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        StaticVoidMethodPartialOverload1Method(info);
        return;
      }
      break;
    case 1:
      break;
  }

  DCHECK(staticVoidMethodPartialOverloadMethodForPartialInterface);
  (staticVoidMethodPartialOverloadMethodForPartialInterface)(info);
}

static void PromiseMethodPartialOverloadMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        PromiseMethodPartialOverload1Method(info);
        return;
      }
      break;
    case 1:
      if (V8Window::HasInstance(info[0], info.GetIsolate())) {
        PromiseMethodPartialOverload2Method(info);
        return;
      }
      break;
  }

  DCHECK(promiseMethodPartialOverloadMethodForPartialInterface);
  (promiseMethodPartialOverloadMethodForPartialInterface)(info);
}

static void StaticPromiseMethodPartialOverloadMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        StaticPromiseMethodPartialOverload1Method(info);
        return;
      }
      break;
    case 1:
      break;
  }

  DCHECK(staticPromiseMethodPartialOverloadMethodForPartialInterface);
  (staticPromiseMethodPartialOverloadMethodForPartialInterface)(info);
}

static void Partial2VoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        Partial2VoidMethod1Method(info);
        return;
      }
      break;
    case 1:
      break;
  }

  DCHECK(partial2VoidMethodMethodForPartialInterface);
  (partial2VoidMethodMethodForPartialInterface)(info);
}

static void Partial2StaticVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  switch (std::min(1, info.Length())) {
    case 0:
      if (true) {
        Partial2StaticVoidMethod1Method(info);
        return;
      }
      break;
    case 1:
      break;
  }

  DCHECK(partial2StaticVoidMethodMethodForPartialInterface);
  (partial2StaticVoidMethodMethodForPartialInterface)(info);
}

static void KeysMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "keys");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ScriptState* scriptState = ScriptState::ForRelevantRealm(info);

  Iterator* result = impl->keysForBinding(scriptState, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
  V8SetReturnValue(info, result);
}

static void ValuesMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "values");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ScriptState* scriptState = ScriptState::ForRelevantRealm(info);

  Iterator* result = impl->valuesForBinding(scriptState, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
  V8SetReturnValue(info, result);
}

static void ForEachMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "forEach");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ScriptState* scriptState = ScriptState::ForRelevantRealm(info);

  if (UNLIKELY(info.Length() < 1)) {
    exceptionState.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  ScriptValue callback;
  ScriptValue thisArg;
  if (info[0]->IsFunction()) {
    callback = ScriptValue(ScriptState::Current(info.GetIsolate()), info[0]);
  } else {
    exceptionState.ThrowTypeError("The callback provided as parameter 1 is not a function.");
    return;
  }

  thisArg = ScriptValue(ScriptState::Current(info.GetIsolate()), info[1]);

  impl->forEachForBinding(scriptState, ScriptValue(scriptState, info.Holder()), callback, thisArg, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
}

static void ToJSONMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ScriptState* scriptState = ScriptState::ForRelevantRealm(info);

  ScriptValue result = impl->toJSONForBinding(scriptState);
  V8SetReturnValue(info, result.V8Value());
}

static void ToStringMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  V8SetReturnValueString(info, impl->toString(), info.GetIsolate());
}

static void IteratorMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kExecutionContext, "TestInterface", "iterator");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  ScriptState* scriptState = ScriptState::ForRelevantRealm(info);

  Iterator* result = impl->GetIterator(scriptState, exceptionState);
  if (exceptionState.HadException()) {
    return;
  }
  V8SetReturnValue(info, result);
}

static void NamedPropertyGetter(const AtomicString& name, const v8::PropertyCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());
  String result = impl->AnonymousNamedGetter(name);
  if (result.IsNull())
    return;
  V8SetReturnValueString(info, result, info.GetIsolate());
}

static void NamedPropertySetter(const AtomicString& name, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());
  V8StringResource<> propertyValue = v8Value;
  if (!propertyValue.Prepare())
    return;

  bool result = impl->AnonymousNamedSetter(name, propertyValue);
  if (!result)
    return;
  V8SetReturnValue(info, v8Value);
}

static void NamedPropertyDeleter(const AtomicString& name, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  DeleteResult result = impl->AnonymousNamedDeleter(name);
  if (result == kDeleteUnknownProperty)
    return;
  V8SetReturnValue(info, result == kDeleteSuccess);
}

static void NamedPropertyQuery(const AtomicString& name, const v8::PropertyCallbackInfo<v8::Integer>& info) {
  const CString& nameInUtf8 = name.Utf8();
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kGetterContext, "TestInterface", nameInUtf8.data());

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  bool result = impl->NamedPropertyQuery(name, exceptionState);
  if (!result)
    return;
  // https://heycam.github.io/webidl/#LegacyPlatformObjectGetOwnProperty
  // 2.7. If |O| implements an interface with a named property setter, then set
  //      desc.[[Writable]] to true, otherwise set it to false.
  // 2.8. If |O| implements an interface with the
  //      [LegacyUnenumerableNamedProperties] extended attribute, then set
  //      desc.[[Enumerable]] to false, otherwise set it to true.
  V8SetReturnValueInt(info, v8::None);
}

static void NamedPropertyEnumerator(const v8::PropertyCallbackInfo<v8::Array>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::kEnumerationContext, "TestInterface");

  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  Vector<String> names;
  impl->NamedPropertyEnumerator(names, exceptionState);
  if (exceptionState.HadException())
    return;
  V8SetReturnValue(info, ToV8(names, info.Holder(), info.GetIsolate()).As<v8::Array>());
}

static void IndexedPropertyGetter(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  // We assume that all the implementations support length() method, although
  // the spec doesn't require that length() must exist.  It's okay that
  // the interface does not have length attribute as long as the
  // implementation supports length() member function.
  if (index >= impl->length())
    return;  // Returns undefined due to out-of-range.

  String result = impl->AnonymousIndexedGetter(index);
  V8SetReturnValueString(info, result, info.GetIsolate());
}

static void IndexedPropertyDescriptor(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
  // https://heycam.github.io/webidl/#LegacyPlatformObjectGetOwnProperty
  // Steps 1.1 to 1.2.4 are covered here: we rely on indexedPropertyGetter() to
  // call the getter function and check that |index| is a valid property index,
  // in which case it will have set info.GetReturnValue() to something other
  // than undefined.
  V8TestInterface::IndexedPropertyGetterCallback(index, info);
  v8::Local<v8::Value> getterValue = info.GetReturnValue().Get();
  if (!getterValue->IsUndefined()) {
    // 1.2.5. Let |desc| be a newly created Property Descriptor with no fields.
    // 1.2.6. Set desc.[[Value]] to the result of converting value to an
    //        ECMAScript value.
    // 1.2.7. If O implements an interface with an indexed property setter,
    //        then set desc.[[Writable]] to true, otherwise set it to false.
    v8::PropertyDescriptor desc(getterValue, true);
    // 1.2.8. Set desc.[[Enumerable]] and desc.[[Configurable]] to true.
    desc.set_enumerable(true);
    desc.set_configurable(true);
    // 1.2.9. Return |desc|.
    V8SetReturnValue(info, desc);
  }
}

static void IndexedPropertySetter(uint32_t index, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());
  V8StringResource<> propertyValue = v8Value;
  if (!propertyValue.Prepare())
    return;

  bool result = impl->AnonymousIndexedSetter(index, propertyValue);
  if (!result)
    return;
  V8SetReturnValue(info, v8Value);
}

static void IndexedPropertyDeleter(uint32_t index, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  TestInterfaceImplementation* impl = V8TestInterface::ToImpl(info.Holder());

  DeleteResult result = impl->AnonymousIndexedDeleter(index);
  if (result == kDeleteUnknownProperty)
    return;
  V8SetReturnValue(info, result == kDeleteSuccess);
}

}  // namespace test_interface_implementation_v8_internal

void V8TestInterface::TestInterfaceAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testInterfaceAttribute_Getter");

  UseCounter::Count(CurrentExecutionContext(info.GetIsolate()), WebFeature::kV8TestInterface_TestInterfaceAttribute_AttributeGetter);

  test_interface_implementation_v8_internal::TestInterfaceAttributeAttributeGetter(info);
}

void V8TestInterface::TestInterfaceAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testInterfaceAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  UseCounter::Count(CurrentExecutionContext(info.GetIsolate()), WebFeature::kV8TestInterface_TestInterfaceAttribute_AttributeSetter);

  test_interface_implementation_v8_internal::TestInterfaceAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::TestInterfaceConstructorAttributeConstructorGetterCallback(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testInterfaceConstructorAttribute_ConstructorGetterCallback");

  V8ConstructorAttributeGetter(property, info, &V8TestInterface::wrapperTypeInfo);
}

void V8TestInterface::TestInterfaceConstructorGetterCallback(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_TestInterface_ConstructorGetterCallback");

  V8ConstructorAttributeGetter(property, info, &V8TestInterface::wrapperTypeInfo);
}

void V8TestInterface::TestInterface2ConstructorGetterCallback(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_TestInterface2_ConstructorGetterCallback");

  V8ConstructorAttributeGetter(property, info, &V8TestInterface2::wrapperTypeInfo);
}

void V8TestInterface::DoubleAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_doubleAttribute_Getter");

  test_interface_implementation_v8_internal::DoubleAttributeAttributeGetter(info);
}

void V8TestInterface::DoubleAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_doubleAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::DoubleAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::FloatAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_floatAttribute_Getter");

  test_interface_implementation_v8_internal::FloatAttributeAttributeGetter(info);
}

void V8TestInterface::FloatAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_floatAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::FloatAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::UnrestrictedDoubleAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_unrestrictedDoubleAttribute_Getter");

  test_interface_implementation_v8_internal::UnrestrictedDoubleAttributeAttributeGetter(info);
}

void V8TestInterface::UnrestrictedDoubleAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_unrestrictedDoubleAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::UnrestrictedDoubleAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::UnrestrictedFloatAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_unrestrictedFloatAttribute_Getter");

  test_interface_implementation_v8_internal::UnrestrictedFloatAttributeAttributeGetter(info);
}

void V8TestInterface::UnrestrictedFloatAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_unrestrictedFloatAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::UnrestrictedFloatAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::TestEnumAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testEnumAttribute_Getter");

  test_interface_implementation_v8_internal::TestEnumAttributeAttributeGetter(info);
}

void V8TestInterface::TestEnumAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testEnumAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::TestEnumAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::TestEnumOrNullAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testEnumOrNullAttribute_Getter");

  test_interface_implementation_v8_internal::TestEnumOrNullAttributeAttributeGetter(info);
}

void V8TestInterface::TestEnumOrNullAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_testEnumOrNullAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::TestEnumOrNullAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::StringOrDoubleAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_stringOrDoubleAttribute_Getter");

  test_interface_implementation_v8_internal::StringOrDoubleAttributeAttributeGetter(info);
}

void V8TestInterface::StringOrDoubleAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_stringOrDoubleAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::StringOrDoubleAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::WithExtendedAttributeStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_withExtendedAttributeStringAttribute_Getter");

  test_interface_implementation_v8_internal::WithExtendedAttributeStringAttributeAttributeGetter(info);
}

void V8TestInterface::WithExtendedAttributeStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_withExtendedAttributeStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::WithExtendedAttributeStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::UncapitalAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_uncapitalAttribute_Getter");

  test_interface_implementation_v8_internal::UncapitalAttributeAttributeGetter(info);
}

void V8TestInterface::UncapitalAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_uncapitalAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::UncapitalAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ConditionalLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_conditionalLongAttribute_Getter");

  test_interface_implementation_v8_internal::ConditionalLongAttributeAttributeGetter(info);
}

void V8TestInterface::ConditionalLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_conditionalLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ConditionalLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ConditionalReadOnlyLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_conditionalReadOnlyLongAttribute_Getter");

  test_interface_implementation_v8_internal::ConditionalReadOnlyLongAttributeAttributeGetter(info);
}

void V8TestInterface::StaticStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticStringAttribute_Getter");

  test_interface_implementation_v8_internal::StaticStringAttributeAttributeGetter(info);
}

void V8TestInterface::StaticStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::StaticStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::StaticReturnDOMWrapperAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticReturnDOMWrapperAttribute_Getter");

  test_interface_implementation_v8_internal::StaticReturnDOMWrapperAttributeAttributeGetter(info);
}

void V8TestInterface::StaticReturnDOMWrapperAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticReturnDOMWrapperAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::StaticReturnDOMWrapperAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::StaticReadOnlyStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticReadOnlyStringAttribute_Getter");

  test_interface_implementation_v8_internal::StaticReadOnlyStringAttributeAttributeGetter(info);
}

void V8TestInterface::StaticReadOnlyReturnDOMWrapperAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticReadOnlyReturnDOMWrapperAttribute_Getter");

  test_interface_implementation_v8_internal::StaticReadOnlyReturnDOMWrapperAttributeAttributeGetter(info);
}

void V8TestInterface::StaticConditionalReadOnlyLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticConditionalReadOnlyLongAttribute_Getter");

  test_interface_implementation_v8_internal::StaticConditionalReadOnlyLongAttributeAttributeGetter(info);
}

void V8TestInterface::LegacyInterfaceTypeCheckingAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_legacyInterfaceTypeCheckingAttribute_Getter");

  test_interface_implementation_v8_internal::LegacyInterfaceTypeCheckingAttributeAttributeGetter(info);
}

void V8TestInterface::LegacyInterfaceTypeCheckingAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_legacyInterfaceTypeCheckingAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::LegacyInterfaceTypeCheckingAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::StringNullAsEmptyAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_stringNullAsEmptyAttribute_Getter");

  test_interface_implementation_v8_internal::StringNullAsEmptyAttributeAttributeGetter(info);
}

void V8TestInterface::StringNullAsEmptyAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_stringNullAsEmptyAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::StringNullAsEmptyAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::UsvStringOrNullAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_usvStringOrNullAttribute_Getter");

  test_interface_implementation_v8_internal::UsvStringOrNullAttributeAttributeGetter(info);
}

void V8TestInterface::UsvStringOrNullAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_usvStringOrNullAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::UsvStringOrNullAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::AlwaysExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_alwaysExposedAttribute_Getter");

  test_interface_implementation_v8_internal::AlwaysExposedAttributeAttributeGetter(info);
}

void V8TestInterface::AlwaysExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_alwaysExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::AlwaysExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::WorkerExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_workerExposedAttribute_Getter");

  test_interface_implementation_v8_internal::WorkerExposedAttributeAttributeGetter(info);
}

void V8TestInterface::WorkerExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_workerExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::WorkerExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::WindowExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_windowExposedAttribute_Getter");

  test_interface_implementation_v8_internal::WindowExposedAttributeAttributeGetter(info);
}

void V8TestInterface::WindowExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_windowExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::WindowExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::LenientThisAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_lenientThisAttribute_Getter");

  test_interface_implementation_v8_internal::LenientThisAttributeAttributeGetter(info);
}

void V8TestInterface::LenientThisAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_lenientThisAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::LenientThisAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::AttributeWithSideEffectFreeGetterAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_attributeWithSideEffectFreeGetter_Getter");

  test_interface_implementation_v8_internal::AttributeWithSideEffectFreeGetterAttributeGetter(info);
}

void V8TestInterface::AttributeWithSideEffectFreeGetterAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_attributeWithSideEffectFreeGetter_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::AttributeWithSideEffectFreeGetterAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextnessRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextnessRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextnessRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextnessRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextnessRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextnessRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextWindowExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextWindowExposedAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextWindowExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextWindowExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextWorkerExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextWorkerExposedAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextWorkerExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextWorkerExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextWindowExposedRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextWindowExposedRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextWindowExposedRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextWindowExposedRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ImplementsStaticReadOnlyLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStaticReadOnlyLongAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsStaticReadOnlyLongAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsStaticStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStaticStringAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsStaticStringAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsStaticStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStaticStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ImplementsStaticStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ImplementsReadonlyStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsReadonlyStringAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsReadonlyStringAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStringAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsStringAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ImplementsStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ImplementsNodeAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsNodeAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsNodeAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsNodeAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsNodeAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ImplementsNodeAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ImplementsEventHandlerAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsEventHandlerAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsEventHandlerAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsEventHandlerAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsEventHandlerAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ImplementsEventHandlerAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::ImplementsRuntimeEnabledNodeAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsRuntimeEnabledNodeAttribute_Getter");

  test_interface_implementation_v8_internal::ImplementsRuntimeEnabledNodeAttributeAttributeGetter(info);
}

void V8TestInterface::ImplementsRuntimeEnabledNodeAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsRuntimeEnabledNodeAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::ImplementsRuntimeEnabledNodeAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Implements2StaticStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements2StaticStringAttribute_Getter");

  test_interface_implementation_v8_internal::Implements2StaticStringAttributeAttributeGetter(info);
}

void V8TestInterface::Implements2StaticStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements2StaticStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Implements2StaticStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Implements2StringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements2StringAttribute_Getter");

  test_interface_implementation_v8_internal::Implements2StringAttributeAttributeGetter(info);
}

void V8TestInterface::Implements2StringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements2StringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Implements2StringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Implements3StringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3StringAttribute_Getter");

  test_interface_implementation_v8_internal::Implements3StringAttributeAttributeGetter(info);
}

void V8TestInterface::Implements3StringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3StringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Implements3StringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Implements3StaticStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3StaticStringAttribute_Getter");

  test_interface_implementation_v8_internal::Implements3StaticStringAttributeAttributeGetter(info);
}

void V8TestInterface::Implements3StaticStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3StaticStringAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Implements3StaticStringAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialLongAttribute_Getter");

  test_interface_implementation_v8_internal::PartialLongAttributeAttributeGetter(info);
}

void V8TestInterface::PartialLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialStaticLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialStaticLongAttribute_Getter");

  test_interface_implementation_v8_internal::PartialStaticLongAttributeAttributeGetter(info);
}

void V8TestInterface::PartialStaticLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialStaticLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialStaticLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialCallWithExecutionContextLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialCallWithExecutionContextLongAttribute_Getter");

  test_interface_implementation_v8_internal::PartialCallWithExecutionContextLongAttributeAttributeGetter(info);
}

void V8TestInterface::PartialCallWithExecutionContextLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialCallWithExecutionContextLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialCallWithExecutionContextLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialPartialEnumTypeAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialPartialEnumTypeAttribute_Getter");

  test_interface_implementation_v8_internal::PartialPartialEnumTypeAttributeAttributeGetter(info);
}

void V8TestInterface::PartialPartialEnumTypeAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialPartialEnumTypeAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialPartialEnumTypeAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextLongAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextLongAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Partial2LongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2LongAttribute_Getter");

  test_interface_implementation_v8_internal::Partial2LongAttributeAttributeGetter(info);
}

void V8TestInterface::Partial2LongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2LongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Partial2LongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Partial2StaticLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2StaticLongAttribute_Getter");

  test_interface_implementation_v8_internal::Partial2StaticLongAttributeAttributeGetter(info);
}

void V8TestInterface::Partial2StaticLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2StaticLongAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Partial2StaticLongAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::Partial2SecureContextAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2SecureContextAttribute_Getter");

  test_interface_implementation_v8_internal::Partial2SecureContextAttributeAttributeGetter(info);
}

void V8TestInterface::Partial2SecureContextAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2SecureContextAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::Partial2SecureContextAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextWindowExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextWindowExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextWorkerExposedAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextWorkerExposedAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedRuntimeEnabledAttribute_Getter");

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetter(info);
}

void V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedRuntimeEnabledAttribute_Setter");

  v8::Local<v8::Value> v8Value = info[0];

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetter(v8Value, info);
}

void V8TestInterface::VoidMethodTestInterfaceEmptyArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodTestInterfaceEmptyArg");

  test_interface_implementation_v8_internal::VoidMethodTestInterfaceEmptyArgMethod(info);
}

void V8TestInterface::VoidMethodDoubleArgFloatArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodDoubleArgFloatArg");

  test_interface_implementation_v8_internal::VoidMethodDoubleArgFloatArgMethod(info);
}

void V8TestInterface::VoidMethodNullableAndOptionalObjectArgsMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodNullableAndOptionalObjectArgs");

  test_interface_implementation_v8_internal::VoidMethodNullableAndOptionalObjectArgsMethod(info);
}

void V8TestInterface::VoidMethodUnrestrictedDoubleArgUnrestrictedFloatArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodUnrestrictedDoubleArgUnrestrictedFloatArg");

  test_interface_implementation_v8_internal::VoidMethodUnrestrictedDoubleArgUnrestrictedFloatArgMethod(info);
}

void V8TestInterface::VoidMethodTestEnumArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodTestEnumArg");

  test_interface_implementation_v8_internal::VoidMethodTestEnumArgMethod(info);
}

void V8TestInterface::VoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethod");

  test_interface_implementation_v8_internal::VoidMethodMethod(info);
}

void V8TestInterface::VoidMethodMethodCallbackForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethod");

  test_interface_implementation_v8_internal::VoidMethodMethodForMainWorld(info);
}

void V8TestInterface::AlwaysExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_alwaysExposedMethod");

  test_interface_implementation_v8_internal::AlwaysExposedMethodMethod(info);
}

void V8TestInterface::WorkerExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_workerExposedMethod");

  test_interface_implementation_v8_internal::WorkerExposedMethodMethod(info);
}

void V8TestInterface::WindowExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_windowExposedMethod");

  test_interface_implementation_v8_internal::WindowExposedMethodMethod(info);
}

void V8TestInterface::AlwaysExposedStaticMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_alwaysExposedStaticMethod");

  test_interface_implementation_v8_internal::AlwaysExposedStaticMethodMethod(info);
}

void V8TestInterface::WorkerExposedStaticMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_workerExposedStaticMethod");

  test_interface_implementation_v8_internal::WorkerExposedStaticMethodMethod(info);
}

void V8TestInterface::WindowExposedStaticMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_windowExposedStaticMethod");

  test_interface_implementation_v8_internal::WindowExposedStaticMethodMethod(info);
}

void V8TestInterface::StaticReturnDOMWrapperMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticReturnDOMWrapperMethod");

  test_interface_implementation_v8_internal::StaticReturnDOMWrapperMethodMethod(info);
}

void V8TestInterface::MethodWithExposedAndRuntimeEnabledFlagMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_methodWithExposedAndRuntimeEnabledFlag");

  test_interface_implementation_v8_internal::MethodWithExposedAndRuntimeEnabledFlagMethod(info);
}

void V8TestInterface::OverloadMethodWithExposedAndRuntimeEnabledFlagMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_overloadMethodWithExposedAndRuntimeEnabledFlag");

  test_interface_implementation_v8_internal::OverloadMethodWithExposedAndRuntimeEnabledFlagMethod(info);
}

void V8TestInterface::MethodWithExposedHavingRuntimeEnabldFlagMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_methodWithExposedHavingRuntimeEnabldFlag");

  test_interface_implementation_v8_internal::MethodWithExposedHavingRuntimeEnabldFlagMethod(info);
}

void V8TestInterface::WindowAndServiceWorkerExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_windowAndServiceWorkerExposedMethod");

  test_interface_implementation_v8_internal::WindowAndServiceWorkerExposedMethodMethod(info);
}

void V8TestInterface::OverloadMethodWithUnionTypeWithStringMemberMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_overloadMethodWithUnionTypeWithStringMember");

  test_interface_implementation_v8_internal::OverloadMethodWithUnionTypeWithStringMemberMethod(info);
}

void V8TestInterface::LegacyInterfaceTypeCheckingMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_legacyInterfaceTypeCheckingMethod");

  test_interface_implementation_v8_internal::LegacyInterfaceTypeCheckingMethodMethod(info);
}

void V8TestInterface::SideEffectFreeMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_sideEffectFreeMethod");

  test_interface_implementation_v8_internal::SideEffectFreeMethodMethod(info);
}

void V8TestInterface::SecureContextMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextMethod");

  test_interface_implementation_v8_internal::SecureContextMethodMethod(info);
}

void V8TestInterface::SecureContextRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::SecureContextRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::SecureContextnessRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextnessRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::SecureContextnessRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::SecureContextWindowExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedMethod");

  test_interface_implementation_v8_internal::SecureContextWindowExposedMethodMethod(info);
}

void V8TestInterface::SecureContextWorkerExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedMethod");

  test_interface_implementation_v8_internal::SecureContextWorkerExposedMethodMethod(info);
}

void V8TestInterface::SecureContextWindowExposedRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWindowExposedRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::SecureContextWindowExposedRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::SecureContextWorkerExposedRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_secureContextWorkerExposedRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::SecureContextWorkerExposedRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::MethodWithNullableSequencesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_methodWithNullableSequences");

  test_interface_implementation_v8_internal::MethodWithNullableSequencesMethod(info);
}

void V8TestInterface::MethodWithNullableRecordsMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_methodWithNullableRecords");

  test_interface_implementation_v8_internal::MethodWithNullableRecordsMethod(info);
}

void V8TestInterface::ImplementsVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsVoidMethod");

  test_interface_implementation_v8_internal::ImplementsVoidMethodMethod(info);
}

void V8TestInterface::ImplementsComplexMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsComplexMethod");

  test_interface_implementation_v8_internal::ImplementsComplexMethodMethod(info);
}

void V8TestInterface::ImplementsCustomVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsCustomVoidMethod");

  V8TestInterface::ImplementsCustomVoidMethodMethodCustom(info);
}

void V8TestInterface::ImplementsStaticVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implementsStaticVoidMethod");

  test_interface_implementation_v8_internal::ImplementsStaticVoidMethodMethod(info);
}

void V8TestInterface::Implements2VoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements2VoidMethod");

  test_interface_implementation_v8_internal::Implements2VoidMethodMethod(info);
}

void V8TestInterface::Implements3VoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3VoidMethod");

  test_interface_implementation_v8_internal::Implements3VoidMethodMethod(info);
}

void V8TestInterface::Implements3StaticVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_implements3StaticVoidMethod");

  test_interface_implementation_v8_internal::Implements3StaticVoidMethodMethod(info);
}

void V8TestInterface::PartialVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialVoidMethod");

  test_interface_implementation_v8_internal::PartialVoidMethodMethod(info);
}

void V8TestInterface::PartialStaticVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialStaticVoidMethod");

  test_interface_implementation_v8_internal::PartialStaticVoidMethodMethod(info);
}

void V8TestInterface::PartialVoidMethodLongArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialVoidMethodLongArg");

  test_interface_implementation_v8_internal::PartialVoidMethodLongArgMethod(info);
}

void V8TestInterface::PartialCallWithExecutionContextRaisesExceptionVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialCallWithExecutionContextRaisesExceptionVoidMethod");

  test_interface_implementation_v8_internal::PartialCallWithExecutionContextRaisesExceptionVoidMethodMethod(info);
}

void V8TestInterface::PartialVoidMethodPartialCallbackTypeArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialVoidMethodPartialCallbackTypeArg");

  test_interface_implementation_v8_internal::PartialVoidMethodPartialCallbackTypeArgMethod(info);
}

void V8TestInterface::Partial2SecureContextMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2SecureContextMethod");

  test_interface_implementation_v8_internal::Partial2SecureContextMethodMethod(info);
}

void V8TestInterface::PartialSecureContextMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextMethod");

  test_interface_implementation_v8_internal::PartialSecureContextMethodMethod(info);
}

void V8TestInterface::PartialSecureContextRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::PartialSecureContextRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::PartialSecureContextWindowExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedMethod");

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedMethodMethod(info);
}

void V8TestInterface::PartialSecureContextWorkerExposedMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedMethod");

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedMethodMethod(info);
}

void V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWindowExposedRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::PartialSecureContextWindowExposedRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partialSecureContextWorkerExposedRuntimeEnabledMethod");

  test_interface_implementation_v8_internal::PartialSecureContextWorkerExposedRuntimeEnabledMethodMethod(info);
}

void V8TestInterface::VoidMethodPartialOverloadMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_voidMethodPartialOverload");

  test_interface_implementation_v8_internal::VoidMethodPartialOverloadMethod(info);
}

void V8TestInterface::StaticVoidMethodPartialOverloadMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticVoidMethodPartialOverload");

  test_interface_implementation_v8_internal::StaticVoidMethodPartialOverloadMethod(info);
}

void V8TestInterface::PromiseMethodPartialOverloadMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_promiseMethodPartialOverload");

  test_interface_implementation_v8_internal::PromiseMethodPartialOverloadMethod(info);
}

void V8TestInterface::StaticPromiseMethodPartialOverloadMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_staticPromiseMethodPartialOverload");

  test_interface_implementation_v8_internal::StaticPromiseMethodPartialOverloadMethod(info);
}

void V8TestInterface::Partial2VoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2VoidMethod");

  test_interface_implementation_v8_internal::Partial2VoidMethodMethod(info);
}

void V8TestInterface::Partial2StaticVoidMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_partial2StaticVoidMethod");

  test_interface_implementation_v8_internal::Partial2StaticVoidMethodMethod(info);
}

void V8TestInterface::KeysMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_keys");

  test_interface_implementation_v8_internal::KeysMethod(info);
}

void V8TestInterface::ValuesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_values");

  test_interface_implementation_v8_internal::ValuesMethod(info);
}

void V8TestInterface::ForEachMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_forEach");

  test_interface_implementation_v8_internal::ForEachMethod(info);
}

void V8TestInterface::ToJSONMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_toJSON");

  test_interface_implementation_v8_internal::ToJSONMethod(info);
}

void V8TestInterface::ToStringMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_toString");

  test_interface_implementation_v8_internal::ToStringMethod(info);
}

void V8TestInterface::IteratorMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_iterator");

  test_interface_implementation_v8_internal::IteratorMethod(info);
}

void V8TestInterface::NamedPropertyGetterCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_NamedPropertyGetter");

  if (!name->IsString())
    return;
  const AtomicString& propertyName = ToCoreAtomicString(name.As<v8::String>());

  test_interface_implementation_v8_internal::NamedPropertyGetter(propertyName, info);
}

void V8TestInterface::NamedPropertySetterCallback(v8::Local<v8::Name> name, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_NamedPropertySetter");

  if (!name->IsString())
    return;
  const AtomicString& propertyName = ToCoreAtomicString(name.As<v8::String>());

  test_interface_implementation_v8_internal::NamedPropertySetter(propertyName, v8Value, info);
}

void V8TestInterface::NamedPropertyDeleterCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  if (!name->IsString())
    return;
  const AtomicString& propertyName = ToCoreAtomicString(name.As<v8::String>());

  test_interface_implementation_v8_internal::NamedPropertyDeleter(propertyName, info);
}

void V8TestInterface::NamedPropertyQueryCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Integer>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_NamedPropertyQuery");

  if (!name->IsString())
    return;
  const AtomicString& propertyName = ToCoreAtomicString(name.As<v8::String>());

  test_interface_implementation_v8_internal::NamedPropertyQuery(propertyName, info);
}

void V8TestInterface::NamedPropertyEnumeratorCallback(const v8::PropertyCallbackInfo<v8::Array>& info) {
  test_interface_implementation_v8_internal::NamedPropertyEnumerator(info);
}

void V8TestInterface::IndexedPropertyGetterCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestInterfaceImplementation_IndexedPropertyGetter");

  test_interface_implementation_v8_internal::IndexedPropertyGetter(index, info);
}

void V8TestInterface::IndexedPropertyDescriptorCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
  test_interface_implementation_v8_internal::IndexedPropertyDescriptor(index, info);
}

void V8TestInterface::IndexedPropertySetterCallback(uint32_t index, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  test_interface_implementation_v8_internal::IndexedPropertySetter(index, v8Value, info);
}

void V8TestInterface::IndexedPropertyDeleterCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  test_interface_implementation_v8_internal::IndexedPropertyDeleter(index, info);
}

void V8TestInterface::IndexedPropertyDefinerCallback(
    uint32_t index,
    const v8::PropertyDescriptor& desc,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  // https://heycam.github.io/webidl/#legacy-platform-object-defineownproperty
  // 3.9.3. [[DefineOwnProperty]]
  // step 1.1. If the result of calling IsDataDescriptor(Desc) is false, then
  //   return false.
  if (desc.has_get() || desc.has_set()) {
    V8SetReturnValue(info, v8::Null(info.GetIsolate()));
    if (info.ShouldThrowOnError()) {
      ExceptionState exceptionState(info.GetIsolate(),
                                    ExceptionState::kIndexedSetterContext,
                                    "TestInterface");
      exceptionState.ThrowTypeError("Accessor properties are not allowed.");
    }
    return;
  }

  // Return nothing and fall back to indexedPropertySetterCallback.
}

// Suppress warning: global constructors, because AttributeConfiguration is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
static const V8DOMConfiguration::AttributeConfiguration V8TestInterfaceAttributes[] = {
    { "testInterfaceConstructorAttribute", V8TestInterface::TestInterfaceConstructorAttributeConstructorGetterCallback, nullptr, static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::kOnInstance, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kReplaceWithDataProperty, V8DOMConfiguration::kAllWorlds },
    { "TestInterface", V8TestInterface::TestInterfaceConstructorGetterCallback, nullptr, static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::kOnInstance, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kReplaceWithDataProperty, V8DOMConfiguration::kAllWorlds },
    { "TestInterface2", V8TestInterface::TestInterface2ConstructorGetterCallback, nullptr, static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::kOnInstance, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kReplaceWithDataProperty, V8DOMConfiguration::kAllWorlds },
};
#if defined(COMPONENT_BUILD) && defined(WIN32) && defined(__clang__)
#pragma clang diagnostic pop
#endif

static const V8DOMConfiguration::AccessorConfiguration V8TestInterfaceAccessors[] = {
    { "testInterfaceAttribute", V8TestInterface::TestInterfaceAttributeAttributeGetterCallback, V8TestInterface::TestInterfaceAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "doubleAttribute", V8TestInterface::DoubleAttributeAttributeGetterCallback, V8TestInterface::DoubleAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "floatAttribute", V8TestInterface::FloatAttributeAttributeGetterCallback, V8TestInterface::FloatAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "unrestrictedDoubleAttribute", V8TestInterface::UnrestrictedDoubleAttributeAttributeGetterCallback, V8TestInterface::UnrestrictedDoubleAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "unrestrictedFloatAttribute", V8TestInterface::UnrestrictedFloatAttributeAttributeGetterCallback, V8TestInterface::UnrestrictedFloatAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "testEnumAttribute", V8TestInterface::TestEnumAttributeAttributeGetterCallback, V8TestInterface::TestEnumAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "testEnumOrNullAttribute", V8TestInterface::TestEnumOrNullAttributeAttributeGetterCallback, V8TestInterface::TestEnumOrNullAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "stringOrDoubleAttribute", V8TestInterface::StringOrDoubleAttributeAttributeGetterCallback, V8TestInterface::StringOrDoubleAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "withExtendedAttributeStringAttribute", V8TestInterface::WithExtendedAttributeStringAttributeAttributeGetterCallback, V8TestInterface::WithExtendedAttributeStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "uncapitalAttribute", V8TestInterface::UncapitalAttributeAttributeGetterCallback, V8TestInterface::UncapitalAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "staticStringAttribute", V8TestInterface::StaticStringAttributeAttributeGetterCallback, V8TestInterface::StaticStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "staticReturnDOMWrapperAttribute", V8TestInterface::StaticReturnDOMWrapperAttributeAttributeGetterCallback, V8TestInterface::StaticReturnDOMWrapperAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "staticReadOnlyStringAttribute", V8TestInterface::StaticReadOnlyStringAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "staticReadOnlyReturnDOMWrapperAttribute", V8TestInterface::StaticReadOnlyReturnDOMWrapperAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "legacyInterfaceTypeCheckingAttribute", V8TestInterface::LegacyInterfaceTypeCheckingAttributeAttributeGetterCallback, V8TestInterface::LegacyInterfaceTypeCheckingAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "stringNullAsEmptyAttribute", V8TestInterface::StringNullAsEmptyAttributeAttributeGetterCallback, V8TestInterface::StringNullAsEmptyAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "usvStringOrNullAttribute", V8TestInterface::UsvStringOrNullAttributeAttributeGetterCallback, V8TestInterface::UsvStringOrNullAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "alwaysExposedAttribute", V8TestInterface::AlwaysExposedAttributeAttributeGetterCallback, V8TestInterface::AlwaysExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "lenientThisAttribute", V8TestInterface::LenientThisAttributeAttributeGetterCallback, V8TestInterface::LenientThisAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kDoNotCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "attributeWithSideEffectFreeGetter", V8TestInterface::AttributeWithSideEffectFreeGetterAttributeGetterCallback, V8TestInterface::AttributeWithSideEffectFreeGetterAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasNoSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsStaticReadOnlyLongAttribute", V8TestInterface::ImplementsStaticReadOnlyLongAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsStaticStringAttribute", V8TestInterface::ImplementsStaticStringAttributeAttributeGetterCallback, V8TestInterface::ImplementsStaticStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsReadonlyStringAttribute", V8TestInterface::ImplementsReadonlyStringAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsStringAttribute", V8TestInterface::ImplementsStringAttributeAttributeGetterCallback, V8TestInterface::ImplementsStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsNodeAttribute", V8TestInterface::ImplementsNodeAttributeAttributeGetterCallback, V8TestInterface::ImplementsNodeAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implementsEventHandlerAttribute", V8TestInterface::ImplementsEventHandlerAttributeAttributeGetterCallback, V8TestInterface::ImplementsEventHandlerAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implements3StringAttribute", V8TestInterface::Implements3StringAttributeAttributeGetterCallback, V8TestInterface::Implements3StringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "implements3StaticStringAttribute", V8TestInterface::Implements3StaticStringAttributeAttributeGetterCallback, V8TestInterface::Implements3StaticStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "partial2LongAttribute", V8TestInterface::Partial2LongAttributeAttributeGetterCallback, V8TestInterface::Partial2LongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    { "partial2StaticLongAttribute", V8TestInterface::Partial2StaticLongAttributeAttributeGetterCallback, V8TestInterface::Partial2StaticLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
};

static const V8DOMConfiguration::MethodConfiguration V8TestInterfaceMethods[] = {
    {"voidMethodTestInterfaceEmptyArg", V8TestInterface::VoidMethodTestInterfaceEmptyArgMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethodDoubleArgFloatArg", V8TestInterface::VoidMethodDoubleArgFloatArgMethodCallback, 2, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethodNullableAndOptionalObjectArgs", V8TestInterface::VoidMethodNullableAndOptionalObjectArgsMethodCallback, 2, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethodUnrestrictedDoubleArgUnrestrictedFloatArg", V8TestInterface::VoidMethodUnrestrictedDoubleArgUnrestrictedFloatArgMethodCallback, 2, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethodTestEnumArg", V8TestInterface::VoidMethodTestEnumArgMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethod", V8TestInterface::VoidMethodMethodCallbackForMainWorld, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kMainWorld},
    {"voidMethod", V8TestInterface::VoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kNonMainWorlds},
    {"alwaysExposedMethod", V8TestInterface::AlwaysExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"alwaysExposedStaticMethod", V8TestInterface::AlwaysExposedStaticMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"staticReturnDOMWrapperMethod", V8TestInterface::StaticReturnDOMWrapperMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"overloadMethodWithUnionTypeWithStringMember", V8TestInterface::OverloadMethodWithUnionTypeWithStringMemberMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"legacyInterfaceTypeCheckingMethod", V8TestInterface::LegacyInterfaceTypeCheckingMethodMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"sideEffectFreeMethod", V8TestInterface::SideEffectFreeMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasNoSideEffect, V8DOMConfiguration::kAllWorlds},
    {"methodWithNullableSequences", V8TestInterface::MethodWithNullableSequencesMethodCallback, 4, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"methodWithNullableRecords", V8TestInterface::MethodWithNullableRecordsMethodCallback, 4, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implementsVoidMethod", V8TestInterface::ImplementsVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implementsComplexMethod", V8TestInterface::ImplementsComplexMethodMethodCallback, 2, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implementsCustomVoidMethod", V8TestInterface::ImplementsCustomVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implementsStaticVoidMethod", V8TestInterface::ImplementsStaticVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implements3VoidMethod", V8TestInterface::Implements3VoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"implements3StaticVoidMethod", V8TestInterface::Implements3StaticVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"voidMethodPartialOverload", V8TestInterface::VoidMethodPartialOverloadMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"staticVoidMethodPartialOverload", V8TestInterface::StaticVoidMethodPartialOverloadMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"promiseMethodPartialOverload", V8TestInterface::PromiseMethodPartialOverloadMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kDoNotCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"staticPromiseMethodPartialOverload", V8TestInterface::StaticPromiseMethodPartialOverloadMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kDoNotCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"partial2VoidMethod", V8TestInterface::Partial2VoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"partial2StaticVoidMethod", V8TestInterface::Partial2StaticVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"keys", V8TestInterface::KeysMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"values", V8TestInterface::ValuesMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"forEach", V8TestInterface::ForEachMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"toJSON", V8TestInterface::ToJSONMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
    {"toString", V8TestInterface::ToStringMethodCallback, 0, static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds},
};

void V8TestInterface::InstallV8TestInterfaceTemplate(
    v8::Isolate* isolate,
    const DOMWrapperWorld& world,
    v8::Local<v8::FunctionTemplate> interfaceTemplate) {
  // Initialize the interface object's template.
  V8DOMConfiguration::InitializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8TestInterface::wrapperTypeInfo.interface_name, V8TestInterfaceEmpty::DomTemplate(isolate, world), V8TestInterface::internalFieldCount);

  v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
  ALLOW_UNUSED_LOCAL(signature);
  v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
  ALLOW_UNUSED_LOCAL(instanceTemplate);
  v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
  ALLOW_UNUSED_LOCAL(prototypeTemplate);

  // Register IDL constants, attributes and operations.
  static constexpr V8DOMConfiguration::ConstantConfiguration V8TestInterfaceConstants[] = {
      {"UNSIGNED_LONG", V8DOMConfiguration::kConstantTypeUnsignedLong, static_cast<int>(0)},
      {"CONST_JAVASCRIPT", V8DOMConfiguration::kConstantTypeShort, static_cast<int>(1)},
      {"IMPLEMENTS_CONSTANT_1", V8DOMConfiguration::kConstantTypeUnsignedShort, static_cast<int>(1)},
      {"IMPLEMENTS_CONSTANT_2", V8DOMConfiguration::kConstantTypeUnsignedShort, static_cast<int>(2)},
      {"PARTIAL2_UNSIGNED_SHORT", V8DOMConfiguration::kConstantTypeUnsignedShort, static_cast<int>(0)},
  };
  V8DOMConfiguration::InstallConstants(
      isolate, interfaceTemplate, prototypeTemplate,
      V8TestInterfaceConstants, base::size(V8TestInterfaceConstants));
  V8DOMConfiguration::InstallAttributes(
      isolate, world, instanceTemplate, prototypeTemplate,
      V8TestInterfaceAttributes, base::size(V8TestInterfaceAttributes));
  V8DOMConfiguration::InstallAccessors(
      isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate,
      signature, V8TestInterfaceAccessors, base::size(V8TestInterfaceAccessors));
  V8DOMConfiguration::InstallMethods(
      isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate,
      signature, V8TestInterfaceMethods, base::size(V8TestInterfaceMethods));

  // Indexed properties
  v8::IndexedPropertyHandlerConfiguration indexedPropertyHandlerConfig(
      V8TestInterface::IndexedPropertyGetterCallback,
      V8TestInterface::IndexedPropertySetterCallback,
      V8TestInterface::IndexedPropertyDescriptorCallback,
      V8TestInterface::IndexedPropertyDeleterCallback,
      IndexedPropertyEnumerator<TestInterfaceImplementation>,
      V8TestInterface::IndexedPropertyDefinerCallback,
      v8::Local<v8::Value>(),
      v8::PropertyHandlerFlags::kNone);
  instanceTemplate->SetHandler(indexedPropertyHandlerConfig);
  // Named properties
  v8::NamedPropertyHandlerConfiguration namedPropertyHandlerConfig(V8TestInterface::NamedPropertyGetterCallback, V8TestInterface::NamedPropertySetterCallback, V8TestInterface::NamedPropertyQueryCallback, V8TestInterface::NamedPropertyDeleterCallback, V8TestInterface::NamedPropertyEnumeratorCallback, v8::Local<v8::Value>(), static_cast<v8::PropertyHandlerFlags>(int(v8::PropertyHandlerFlags::kOnlyInterceptStrings) | int(v8::PropertyHandlerFlags::kNonMasking)));
  instanceTemplate->SetHandler(namedPropertyHandlerConfig);

  // Iterator (@@iterator)
  static const V8DOMConfiguration::SymbolKeyedMethodConfiguration
  symbolKeyedIteratorConfiguration = {
      v8::Symbol::GetIterator,
      "entries",
      V8TestInterface::IteratorMethodCallback,
      0,
      v8::DontEnum,
      V8DOMConfiguration::kOnPrototype,
      V8DOMConfiguration::kCheckHolder,
      V8DOMConfiguration::kDoNotCheckAccess,
      V8DOMConfiguration::kHasSideEffect
  };
  V8DOMConfiguration::InstallMethod(isolate, world, prototypeTemplate, signature, symbolKeyedIteratorConfiguration);

  instanceTemplate->SetCallAsFunctionHandler(V8TestInterface::LegacyCallCustom);

  // Custom signature
}

void V8TestInterface::InstallRuntimeEnabledFeaturesOnTemplate(
    v8::Isolate* isolate,
    const DOMWrapperWorld& world,
    v8::Local<v8::FunctionTemplate> interface_template) {
  v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interface_template);
  ALLOW_UNUSED_LOCAL(signature);
  v8::Local<v8::ObjectTemplate> instance_template = interface_template->InstanceTemplate();
  ALLOW_UNUSED_LOCAL(instance_template);
  v8::Local<v8::ObjectTemplate> prototype_template = interface_template->PrototypeTemplate();
  ALLOW_UNUSED_LOCAL(prototype_template);

  // Register IDL constants, attributes and operations.
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    static const V8DOMConfiguration::ConstantConfiguration constant_configurations[] = {
        {"PARTIAL_UNSIGNED_SHORT", V8DOMConfiguration::kConstantTypeUnsignedShort, static_cast<int>(0)},
        {"PARTIAL_DOUBLE", V8DOMConfiguration::kConstantTypeDouble, static_cast<double>(3.14)},
    };
    V8DOMConfiguration::InstallConstants(
        isolate, interface_template, prototype_template,
        constant_configurations, base::size(constant_configurations));
  }

  if (RuntimeEnabledFeatures::FeatureNameEnabled()) {
    static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
        { "conditionalReadOnlyLongAttribute", V8TestInterface::ConditionalReadOnlyLongAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "staticConditionalReadOnlyLongAttribute", V8TestInterface::StaticConditionalReadOnlyLongAttributeAttributeGetterCallback, nullptr, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "conditionalLongAttribute", V8TestInterface::ConditionalLongAttributeAttributeGetterCallback, V8TestInterface::ConditionalLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    };
    V8DOMConfiguration::InstallAccessors(
        isolate, world, instance_template, prototype_template, interface_template,
        signature, accessor_configurations,
        base::size(accessor_configurations));
  }
  if (RuntimeEnabledFeatures::Implements2FeatureNameEnabled()) {
    static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
        { "implements2StaticStringAttribute", V8TestInterface::Implements2StaticStringAttributeAttributeGetterCallback, V8TestInterface::Implements2StaticStringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "implements2StringAttribute", V8TestInterface::Implements2StringAttributeAttributeGetterCallback, V8TestInterface::Implements2StringAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    };
    V8DOMConfiguration::InstallAccessors(
        isolate, world, instance_template, prototype_template, interface_template,
        signature, accessor_configurations,
        base::size(accessor_configurations));
  }
  if (RuntimeEnabledFeatures::ImplementsFeatureNameEnabled()) {
    static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
        { "implementsRuntimeEnabledNodeAttribute", V8TestInterface::ImplementsRuntimeEnabledNodeAttributeAttributeGetterCallback, V8TestInterface::ImplementsRuntimeEnabledNodeAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    };
    V8DOMConfiguration::InstallAccessors(
        isolate, world, instance_template, prototype_template, interface_template,
        signature, accessor_configurations,
        base::size(accessor_configurations));
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
        { "partialCallWithExecutionContextLongAttribute", V8TestInterface::PartialCallWithExecutionContextLongAttributeAttributeGetterCallback, V8TestInterface::PartialCallWithExecutionContextLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "partialLongAttribute", V8TestInterface::PartialLongAttributeAttributeGetterCallback, V8TestInterface::PartialLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "partialPartialEnumTypeAttribute", V8TestInterface::PartialPartialEnumTypeAttributeAttributeGetterCallback, V8TestInterface::PartialPartialEnumTypeAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        { "partialStaticLongAttribute", V8TestInterface::PartialStaticLongAttributeAttributeGetterCallback, V8TestInterface::PartialStaticLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
    };
    V8DOMConfiguration::InstallAccessors(
        isolate, world, instance_template, prototype_template, interface_template,
        signature, accessor_configurations,
        base::size(accessor_configurations));
  }

  // Custom signature
  if (RuntimeEnabledFeatures::Implements2FeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration implements2VoidMethodMethodConfiguration[] = {
      {"implements2VoidMethod", V8TestInterface::Implements2VoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : implements2VoidMethodMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration partialVoidMethodMethodConfiguration[] = {
      {"partialVoidMethod", V8TestInterface::PartialVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : partialVoidMethodMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration partialStaticVoidMethodMethodConfiguration[] = {
      {"partialStaticVoidMethod", V8TestInterface::PartialStaticVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : partialStaticVoidMethodMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration partialVoidMethodLongArgMethodConfiguration[] = {
      {"partialVoidMethodLongArg", V8TestInterface::PartialVoidMethodLongArgMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : partialVoidMethodLongArgMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration partialCallWithExecutionContextRaisesExceptionVoidMethodMethodConfiguration[] = {
      {"partialCallWithExecutionContextRaisesExceptionVoidMethod", V8TestInterface::PartialCallWithExecutionContextRaisesExceptionVoidMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : partialCallWithExecutionContextRaisesExceptionVoidMethodMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
  if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
    const V8DOMConfiguration::MethodConfiguration partialVoidMethodPartialCallbackTypeArgMethodConfiguration[] = {
      {"partialVoidMethodPartialCallbackTypeArg", V8TestInterface::PartialVoidMethodPartialCallbackTypeArgMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
    };
    for (const auto& methodConfig : partialVoidMethodPartialCallbackTypeArgMethodConfiguration)
      V8DOMConfiguration::InstallMethod(isolate, world, instance_template, prototype_template, interface_template, signature, methodConfig);
  }
}

v8::Local<v8::FunctionTemplate> V8TestInterface::DomTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world) {
  return V8DOMConfiguration::DomClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), V8TestInterface::installV8TestInterfaceTemplateFunction);
}

bool V8TestInterface::HasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::From(isolate)->HasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8TestInterface::FindInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::From(isolate)->FindInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestInterfaceImplementation* V8TestInterface::ToImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value) {
  return HasInstance(value, isolate) ? ToImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

TestInterfaceImplementation* NativeValueTraits<TestInterfaceImplementation>::NativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState) {
  TestInterfaceImplementation* nativeValue = V8TestInterface::ToImplWithTypeCheck(isolate, value);
  if (!nativeValue) {
    exceptionState.ThrowTypeError(ExceptionMessages::FailedToConvertJSValue(
        "TestInterface"));
  }
  return nativeValue;
}

void V8TestInterface::InstallConditionalFeatures(
    v8::Local<v8::Context> context,
    const DOMWrapperWorld& world,
    v8::Local<v8::Object> instanceObject,
    v8::Local<v8::Object> prototypeObject,
    v8::Local<v8::Function> interfaceObject,
    v8::Local<v8::FunctionTemplate> interfaceTemplate) {
  CHECK(!interfaceTemplate.IsEmpty());
  DCHECK((!prototypeObject.IsEmpty() && !interfaceObject.IsEmpty()) ||
         !instanceObject.IsEmpty());

  v8::Isolate* isolate = context->GetIsolate();

  v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
  ExecutionContext* executionContext = ToExecutionContext(context);
  DCHECK(executionContext);
  bool isSecureContext = (executionContext && executionContext->IsSecureContext());

  if (!prototypeObject.IsEmpty() || !interfaceObject.IsEmpty()) {
    if (isSecureContext) {
      static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
          { "partial2SecureContextAttribute", V8TestInterface::Partial2SecureContextAttributeAttributeGetterCallback, V8TestInterface::Partial2SecureContextAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
          { "partialSecureContextAttribute", V8TestInterface::PartialSecureContextAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
          { "secureContextAttribute", V8TestInterface::SecureContextAttributeAttributeGetterCallback, V8TestInterface::SecureContextAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
      };
      V8DOMConfiguration::InstallAccessors(
          isolate, world, instanceObject, prototypeObject, interfaceObject,
          signature, accessor_configurations,
          base::size(accessor_configurations));
      if (RuntimeEnabledFeatures::PartialFeatureNameEnabled()) {
        static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
            { "partialSecureContextLongAttribute", V8TestInterface::PartialSecureContextLongAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextLongAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        };
        V8DOMConfiguration::InstallAccessors(
            isolate, world, instanceObject, prototypeObject, interfaceObject,
            signature, accessor_configurations,
            base::size(accessor_configurations));
      }
      if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
        static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
            { "partialSecureContextRuntimeEnabledAttribute", V8TestInterface::PartialSecureContextRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
            { "secureContextRuntimeEnabledAttribute", V8TestInterface::SecureContextRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::SecureContextRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        };
        V8DOMConfiguration::InstallAccessors(
            isolate, world, instanceObject, prototypeObject, interfaceObject,
            signature, accessor_configurations,
            base::size(accessor_configurations));
      }
    }
    if (isSecureContext || !RuntimeEnabledFeatures::SecureContextnessFeatureEnabled()) {
      static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
          { "secureContextnessRuntimeEnabledAttribute", V8TestInterface::SecureContextnessRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::SecureContextnessRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
      };
      V8DOMConfiguration::InstallAccessors(
          isolate, world, instanceObject, prototypeObject, interfaceObject,
          signature, accessor_configurations,
          base::size(accessor_configurations));
    }
    if (executionContext && (executionContext->IsDocument())) {
      static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
          { "windowExposedAttribute", V8TestInterface::WindowExposedAttributeAttributeGetterCallback, V8TestInterface::WindowExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
      };
      V8DOMConfiguration::InstallAccessors(
          isolate, world, instanceObject, prototypeObject, interfaceObject,
          signature, accessor_configurations,
          base::size(accessor_configurations));
      if (isSecureContext) {
        static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
            { "partialSecureContextWindowExposedAttribute", V8TestInterface::PartialSecureContextWindowExposedAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextWindowExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
            { "secureContextWindowExposedAttribute", V8TestInterface::SecureContextWindowExposedAttributeAttributeGetterCallback, V8TestInterface::SecureContextWindowExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        };
        V8DOMConfiguration::InstallAccessors(
            isolate, world, instanceObject, prototypeObject, interfaceObject,
            signature, accessor_configurations,
            base::size(accessor_configurations));
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
              { "partialSecureContextWindowExposedRuntimeEnabledAttribute", V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
              { "secureContextWindowExposedRuntimeEnabledAttribute", V8TestInterface::SecureContextWindowExposedRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::SecureContextWindowExposedRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
          };
          V8DOMConfiguration::InstallAccessors(
              isolate, world, instanceObject, prototypeObject, interfaceObject,
              signature, accessor_configurations,
              base::size(accessor_configurations));
        }
      }
    }
    if (executionContext && (executionContext->IsWorkerGlobalScope())) {
      static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
          { "workerExposedAttribute", V8TestInterface::WorkerExposedAttributeAttributeGetterCallback, V8TestInterface::WorkerExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
      };
      V8DOMConfiguration::InstallAccessors(
          isolate, world, instanceObject, prototypeObject, interfaceObject,
          signature, accessor_configurations,
          base::size(accessor_configurations));
      if (isSecureContext) {
        static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
            { "partialSecureContextWorkerExposedAttribute", V8TestInterface::PartialSecureContextWorkerExposedAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextWorkerExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
            { "secureContextWorkerExposedAttribute", V8TestInterface::SecureContextWorkerExposedAttributeAttributeGetterCallback, V8TestInterface::SecureContextWorkerExposedAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
        };
        V8DOMConfiguration::InstallAccessors(
            isolate, world, instanceObject, prototypeObject, interfaceObject,
            signature, accessor_configurations,
            base::size(accessor_configurations));
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          static const V8DOMConfiguration::AccessorConfiguration accessor_configurations[] = {
              { "partialSecureContextWorkerExposedRuntimeEnabledAttribute", V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
              { "secureContextWorkerExposedRuntimeEnabledAttribute", V8TestInterface::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeGetterCallback, V8TestInterface::SecureContextWorkerExposedRuntimeEnabledAttributeAttributeSetterCallback, V8PrivateProperty::kNoCachedAccessor, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAlwaysCallGetter, V8DOMConfiguration::kAllWorlds },
          };
          V8DOMConfiguration::InstallAccessors(
              isolate, world, instanceObject, prototypeObject, interfaceObject,
              signature, accessor_configurations,
              base::size(accessor_configurations));
        }
      }
    }
    if (executionContext && (executionContext->IsWorkerGlobalScope())) {
      const V8DOMConfiguration::MethodConfiguration workerExposedMethodMethodConfiguration[] = {
        {"workerExposedMethod", V8TestInterface::WorkerExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : workerExposedMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (executionContext && (executionContext->IsDocument())) {
      const V8DOMConfiguration::MethodConfiguration windowExposedMethodMethodConfiguration[] = {
        {"windowExposedMethod", V8TestInterface::WindowExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : windowExposedMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (executionContext && (executionContext->IsDocument())) {
      if (RuntimeEnabledFeatures::FeatureNameEnabled()) {
        const V8DOMConfiguration::MethodConfiguration methodWithExposedAndRuntimeEnabledFlagMethodConfiguration[] = {
          {"methodWithExposedAndRuntimeEnabledFlag", V8TestInterface::MethodWithExposedAndRuntimeEnabledFlagMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : methodWithExposedAndRuntimeEnabledFlagMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (executionContext && (executionContext->IsDocument())) {
      const V8DOMConfiguration::MethodConfiguration overloadMethodWithExposedAndRuntimeEnabledFlagMethodConfiguration[] = {
        {"overloadMethodWithExposedAndRuntimeEnabledFlag", V8TestInterface::OverloadMethodWithExposedAndRuntimeEnabledFlagMethodCallback, 1, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : overloadMethodWithExposedAndRuntimeEnabledFlagMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (executionContext && ((executionContext->IsDocument() && RuntimeEnabledFeatures::FeatureNameEnabled()) || (executionContext->IsWorkerGlobalScope() && RuntimeEnabledFeatures::FeatureName2Enabled()))) {
      const V8DOMConfiguration::MethodConfiguration methodWithExposedHavingRuntimeEnabldFlagMethodConfiguration[] = {
        {"methodWithExposedHavingRuntimeEnabldFlag", V8TestInterface::MethodWithExposedHavingRuntimeEnabldFlagMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : methodWithExposedHavingRuntimeEnabldFlagMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (executionContext && (executionContext->IsDocument() || executionContext->IsServiceWorkerGlobalScope())) {
      const V8DOMConfiguration::MethodConfiguration windowAndServiceWorkerExposedMethodMethodConfiguration[] = {
        {"windowAndServiceWorkerExposedMethod", V8TestInterface::WindowAndServiceWorkerExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : windowAndServiceWorkerExposedMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (isSecureContext) {
      const V8DOMConfiguration::MethodConfiguration secureContextMethodMethodConfiguration[] = {
        {"secureContextMethod", V8TestInterface::SecureContextMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : secureContextMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (isSecureContext) {
      if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
        const V8DOMConfiguration::MethodConfiguration secureContextRuntimeEnabledMethodMethodConfiguration[] = {
          {"secureContextRuntimeEnabledMethod", V8TestInterface::SecureContextRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : secureContextRuntimeEnabledMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext || !RuntimeEnabledFeatures::SecureContextnessFeatureEnabled()) {
      const V8DOMConfiguration::MethodConfiguration secureContextnessRuntimeEnabledMethodMethodConfiguration[] = {
        {"secureContextnessRuntimeEnabledMethod", V8TestInterface::SecureContextnessRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : secureContextnessRuntimeEnabledMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsDocument())) {
        const V8DOMConfiguration::MethodConfiguration secureContextWindowExposedMethodMethodConfiguration[] = {
          {"secureContextWindowExposedMethod", V8TestInterface::SecureContextWindowExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : secureContextWindowExposedMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsWorkerGlobalScope())) {
        const V8DOMConfiguration::MethodConfiguration secureContextWorkerExposedMethodMethodConfiguration[] = {
          {"secureContextWorkerExposedMethod", V8TestInterface::SecureContextWorkerExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : secureContextWorkerExposedMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsDocument())) {
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          const V8DOMConfiguration::MethodConfiguration secureContextWindowExposedRuntimeEnabledMethodMethodConfiguration[] = {
            {"secureContextWindowExposedRuntimeEnabledMethod", V8TestInterface::SecureContextWindowExposedRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
          };
          for (const auto& methodConfig : secureContextWindowExposedRuntimeEnabledMethodMethodConfiguration)
            V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
        }
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsWorkerGlobalScope())) {
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          const V8DOMConfiguration::MethodConfiguration secureContextWorkerExposedRuntimeEnabledMethodMethodConfiguration[] = {
            {"secureContextWorkerExposedRuntimeEnabledMethod", V8TestInterface::SecureContextWorkerExposedRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
          };
          for (const auto& methodConfig : secureContextWorkerExposedRuntimeEnabledMethodMethodConfiguration)
            V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
        }
      }
    }
    if (isSecureContext) {
      const V8DOMConfiguration::MethodConfiguration partial2SecureContextMethodMethodConfiguration[] = {
        {"partial2SecureContextMethod", V8TestInterface::Partial2SecureContextMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : partial2SecureContextMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (isSecureContext) {
      const V8DOMConfiguration::MethodConfiguration partialSecureContextMethodMethodConfiguration[] = {
        {"partialSecureContextMethod", V8TestInterface::PartialSecureContextMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : partialSecureContextMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (isSecureContext) {
      if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
        const V8DOMConfiguration::MethodConfiguration partialSecureContextRuntimeEnabledMethodMethodConfiguration[] = {
          {"partialSecureContextRuntimeEnabledMethod", V8TestInterface::PartialSecureContextRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : partialSecureContextRuntimeEnabledMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsDocument())) {
        const V8DOMConfiguration::MethodConfiguration partialSecureContextWindowExposedMethodMethodConfiguration[] = {
          {"partialSecureContextWindowExposedMethod", V8TestInterface::PartialSecureContextWindowExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : partialSecureContextWindowExposedMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsWorkerGlobalScope())) {
        const V8DOMConfiguration::MethodConfiguration partialSecureContextWorkerExposedMethodMethodConfiguration[] = {
          {"partialSecureContextWorkerExposedMethod", V8TestInterface::PartialSecureContextWorkerExposedMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
        };
        for (const auto& methodConfig : partialSecureContextWorkerExposedMethodMethodConfiguration)
          V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsDocument())) {
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          const V8DOMConfiguration::MethodConfiguration partialSecureContextWindowExposedRuntimeEnabledMethodMethodConfiguration[] = {
            {"partialSecureContextWindowExposedRuntimeEnabledMethod", V8TestInterface::PartialSecureContextWindowExposedRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
          };
          for (const auto& methodConfig : partialSecureContextWindowExposedRuntimeEnabledMethodMethodConfiguration)
            V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
        }
      }
    }
    if (isSecureContext) {
      if (executionContext && (executionContext->IsWorkerGlobalScope())) {
        if (RuntimeEnabledFeatures::SecureFeatureEnabled()) {
          const V8DOMConfiguration::MethodConfiguration partialSecureContextWorkerExposedRuntimeEnabledMethodMethodConfiguration[] = {
            {"partialSecureContextWorkerExposedRuntimeEnabledMethod", V8TestInterface::PartialSecureContextWorkerExposedRuntimeEnabledMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnPrototype, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
          };
          for (const auto& methodConfig : partialSecureContextWorkerExposedRuntimeEnabledMethodMethodConfiguration)
            V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
        }
      }
    }
    if (executionContext && (executionContext->IsWorkerGlobalScope())) {
      const V8DOMConfiguration::MethodConfiguration workerExposedStaticMethodMethodConfiguration[] = {
        {"workerExposedStaticMethod", V8TestInterface::WorkerExposedStaticMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : workerExposedStaticMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
    if (executionContext && (executionContext->IsDocument())) {
      const V8DOMConfiguration::MethodConfiguration windowExposedStaticMethodMethodConfiguration[] = {
        {"windowExposedStaticMethod", V8TestInterface::WindowExposedStaticMethodMethodCallback, 0, v8::None, V8DOMConfiguration::kOnInterface, V8DOMConfiguration::kCheckHolder, V8DOMConfiguration::kDoNotCheckAccess, V8DOMConfiguration::kHasSideEffect, V8DOMConfiguration::kAllWorlds}
      };
      for (const auto& methodConfig : windowExposedStaticMethodMethodConfiguration)
        V8DOMConfiguration::InstallMethod(isolate, world, instanceObject, prototypeObject, interfaceObject, signature, methodConfig);
    }
  }
}

InstallRuntimeEnabledFeaturesOnTemplateFunction
V8TestInterface::install_runtime_enabled_features_on_template_function_ =
    &V8TestInterface::InstallRuntimeEnabledFeaturesOnTemplate;

InstallTemplateFunction V8TestInterface::installV8TestInterfaceTemplateFunction =
    &V8TestInterface::InstallV8TestInterfaceTemplate;

void V8TestInterface::UpdateWrapperTypeInfo(
    InstallTemplateFunction install_template_function,
    InstallRuntimeEnabledFeaturesFunction install_runtime_enabled_features_function,
    InstallRuntimeEnabledFeaturesOnTemplateFunction install_runtime_enabled_features_on_template_function,
    InstallConditionalFeaturesFunction install_conditional_features_function) {
  V8TestInterface::installV8TestInterfaceTemplateFunction =
      install_template_function;

  CHECK(install_runtime_enabled_features_on_template_function);
  V8TestInterface::install_runtime_enabled_features_on_template_function_ =
      install_runtime_enabled_features_on_template_function;

  if (install_conditional_features_function) {
    V8TestInterface::wrapperTypeInfo.install_conditional_features_function =
        install_conditional_features_function;
  }
}

void V8TestInterface::RegisterVoidMethodPartialOverloadMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::voidMethodPartialOverloadMethodForPartialInterface = method;
}

void V8TestInterface::RegisterStaticVoidMethodPartialOverloadMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::staticVoidMethodPartialOverloadMethodForPartialInterface = method;
}

void V8TestInterface::RegisterPromiseMethodPartialOverloadMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::promiseMethodPartialOverloadMethodForPartialInterface = method;
}

void V8TestInterface::RegisterStaticPromiseMethodPartialOverloadMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::staticPromiseMethodPartialOverloadMethodForPartialInterface = method;
}

void V8TestInterface::RegisterPartial2VoidMethodMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::partial2VoidMethodMethodForPartialInterface = method;
}

void V8TestInterface::RegisterPartial2StaticVoidMethodMethodForPartialInterface(void (*method)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  test_interface_implementation_v8_internal::partial2StaticVoidMethodMethodForPartialInterface = method;
}

}  // namespace blink
