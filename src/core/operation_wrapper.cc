#include <nan.h>
#include "operation_wrapper.h"

Nan::Persistent<v8::FunctionTemplate> OperationWrapper::constructor;

void OperationWrapper::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  //Class
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OperationWrapper::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Operation").ToLocalChecked());

  constructor.Reset(ctor);
  exports->Set(Nan::New("Operation  ").ToLocalChecked(), ctor->GetFunction());
};

void OperationWrapper::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;

  // TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<OperationWrapper>(info[0]->ToObject())->m_operation;
  OperationWrapper *instance = new OperationWrapper();

  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

OperationWrapper::OperationWrapper(TF_Operation* operation) : m_operation(operation) {};

void OperationWrapper::DoWrap(v8::MaybeLocal<v8::Object>& n) { Wrap(n.ToLocalChecked()); }
