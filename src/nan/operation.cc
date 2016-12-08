#include <nan.h>
#include "operation.h"

namespace nan {

Operation::Operation(TF_Operation* operation) : m_operation(operation) {};

/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
Nan::Persistent<v8::FunctionTemplate> Operation::constructor;

NAN_MODULE_INIT(Operation::Init) {
  Nan::HandleScope scope;

  // Class
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Operation::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Operation").ToLocalChecked());
  constructor.Reset(ctor);

  target->Set(Nan::New("Operation  ").ToLocalChecked(), ctor->GetFunction());
};

void Operation::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;

  // TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_operation;
  Operation *instance = new Operation();

  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan
