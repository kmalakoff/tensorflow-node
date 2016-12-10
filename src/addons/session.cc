#include "session.h"
#include "../tensorflow/session.h"
#include "graph.h"

namespace addons {

using namespace v8;

Session::Session(Graph* graph) {
  m_graph = graph; /* m_graph->Ref(); */ // TODO: figure out how to hande references
  m_ref = new tensorflow::Session();
}

Session::~Session() {
  delete m_ref; m_ref = nullptr;
  /* m_graph->Unref(); */ m_graph = nullptr; // TODO: figure out how to hande references
}

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

  Graph* arg0 = nullptr;
  if (info.Length() >= 1) arg0 = Nan::ObjectWrap::Unwrap<Graph>(info[0]->ToObject());
  Session *instance = new Session(arg0);
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace addons
