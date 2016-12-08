#include <nan.h>
#include "operation.h"

namespace nan {

Nan::Persistent<v8::FunctionTemplate> Operation::constructor;

void Operation::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Class
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Operation::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Operation").ToLocalChecked());
  constructor.Reset(ctor);

  exports->Set(Nan::New("Operation  ").ToLocalChecked(), ctor->GetFunction());
};

void Operation::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;

  // TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_operation;
  Operation *instance = new Operation();

  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Operation::Operation(TF_Operation* operation) : m_operation(operation) {};

void Operation::DoWrap(v8::MaybeLocal<v8::Object>& n) { Wrap(n.ToLocalChecked()); }

} // namespace nan
