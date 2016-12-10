#include "session.h"

namespace nan_bridge {

using namespace v8;

Session::Session(TF_Session* session) : m_ref(session) {};
Session::~Session() { m_ref = nullptr; }

/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
NAN_MODULE_INIT(Session::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Session::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Session").ToLocalChecked());
  constructor.Reset(ctor);

  target->Set(Nan::New("Session").ToLocalChecked(), ctor->GetFunction());
};

NAN_CONSTRUCTOR(Session::constructor);

NAN_NEW(Session::New) {
  Nan::HandleScope scope;

  // TF_Session* arg0 = Nan::ObjectWrap::Unwrap<Session>(info[0]->ToObject())->m_ref;
  Session *instance = new Session();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan_bridge
