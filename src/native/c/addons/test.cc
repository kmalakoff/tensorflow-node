#include <iostream>
#include "test.h"

namespace addons {

using namespace v8;

Test::Test() {}
Test::~Test() {}

NAN_MODULE_INIT(Test::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Test::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Test").ToLocalChecked());
  constructor.Reset(ctor);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "run", run);

  target->Set(Nan::New("Test").ToLocalChecked(), ctor->GetFunction());
};

NAN_CONSTRUCTOR(Test::constructor);

NAN_NEW(Test::New) {
  Nan::HandleScope scope;

  Test *instance = new Test();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Test::run) {
}

} // namespace addons
