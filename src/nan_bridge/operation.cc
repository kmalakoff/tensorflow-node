#include <nan.h>
#include "operation.h"

namespace nan_bridge {

using namespace v8;

Operation::Operation(TF_Operation* operation) : m_operation(operation) {};
Operation::~Operation() { m_operation = nullptr; }

/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
NAN_MODULE_INIT(Operation::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Operation::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Operation").ToLocalChecked());
  constructor.Reset(ctor);

  target->Set(Nan::New("Operation").ToLocalChecked(), ctor->GetFunction());
};

NAN_CONSTRUCTOR(Operation::constructor);

NAN_NEW(Operation::New) {
  Nan::HandleScope scope;

  // TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_operation;
  Operation *instance = new Operation();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan_bridge
