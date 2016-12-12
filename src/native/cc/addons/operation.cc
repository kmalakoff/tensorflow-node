#include "operation.h"

namespace addons {

using namespace v8;

Operation::Operation(tensorflow::ops::Output output) : m_output(output) {};
Operation::Operation(TF_Operation* operation) { m_ref = operation; };
Operation::~Operation() { m_ref = nullptr; }

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

   TF_Operation* arg0 = nullptr;
   if (info.Length() >= 1) arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_ref;
   Operation *instance = new Operation(arg0);
   instance->Wrap(info.Holder());
   info.GetReturnValue().Set(info.Holder());
 }

} // namespace addons
