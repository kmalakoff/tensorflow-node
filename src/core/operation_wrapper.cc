#include <nan.h>
#include "operation_wrapper.h"

Nan::Persistent<v8::FunctionTemplate> OperationWrapper::constructor;

void OperationWrapper::Init(v8::Local<v8::Object> target) {
  Nan::HandleScope scope;

  //Class
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OperationWrapper::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("OperationWrapper").ToLocalChecked());
  target->Set(Nan::New("OperationWrapper").ToLocalChecked(), ctor->GetFunction());
};

void OperationWrapper::New(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  Nan::HandleScope scope;
  // if (info.This()->InternalFieldCount() == 0) { Nan::ThrowTypeError("Cannot instantiate without new"); }

  OperationWrapper *instance = new OperationWrapper();

  instance->Wrap(args.Holder());
  args.GetReturnValue().Set(args.Holder());
}

OperationWrapper::OperationWrapper(TF_Operation* operation) : m_operation(operation) {};

void OperationWrapper::DoWrap(v8::Local<v8::Object> n) { Wrap(n); }
