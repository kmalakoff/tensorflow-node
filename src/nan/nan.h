#ifndef NAN_H
#define NAN_H

#include "addons.h"

#define NAN_WRAP_RESULT(OW, T, r) nan::AddOns::_nan_wrap_result<OW, T>(r)
#define NAN_CONSTRUCTOR(c) Nan::Persistent<v8::FunctionTemplate> c
#define NAN_NEW(n) void n(const Nan::FunctionCallbackInfo<v8::Value>& info)

#endif // NAN_H
