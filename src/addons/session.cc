#include <iostream>
#include "session.h"
#include "../tensorflow/session.h"
#include "graph.h"
#include "../tensorflow/graph.h"
#include "../lib/conversions.h"
#include "operation.h"

namespace addons {

using namespace v8;

Session::Session(Graph* graph) {
  m_graph = graph; /* m_graph->Ref(); */ // TODO: figure out how to hande references

  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(graph->ref()->ref(), opts, s);
  TF_DeleteSessionOptions(opts);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);

  m_ref = new tensorflow::Session(session);
}

Session::~Session() {
  delete m_ref; m_ref = nullptr;
  /* m_graph->Unref(); */ m_graph = nullptr; // TODO: figure out how to hande references
}

NAN_MODULE_INIT(Session::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Session::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Session").ToLocalChecked());
  constructor.Reset(ctor);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "run", run);

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

NAN_METHOD(Session::run) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());

  std::vector<TF_Operation*> arg0;
  if (info[0]->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      arg0.push_back(ObjectWrap::Unwrap<Operation>(jsArray->Get(i)->ToObject())->ref());
    }
  }
  else {
    arg0.push_back(ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref());
  }

  std::vector<TF_Tensor*> results;
  obj->m_ref->run(results, arg0, info[1]);

  info.GetReturnValue().Set(info[0]->IsArray() ? lib::ToArrayValue(results) : lib::ToValue(results[0]));
}

} // namespace addons
