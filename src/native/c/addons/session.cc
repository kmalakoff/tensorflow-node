#include <iostream>
#include "session.h"
#include "../tf/session.h"
#include "graph.h"
#include "../tf/graph.h"
#include "../../lib/conversions.h"
#include "operation.h"

namespace addons {

using namespace v8;

Session::Session(Graph* graph) {
  m_graph = graph; /* m_graph->Ref(); */ // TODO: safe references
  m_ref = tf::Session::create(graph->ref());
}

Session::~Session() {
  tf::Session::destroy(m_ref); m_ref = nullptr;
  /* m_graph->Unref(); */ m_graph = nullptr; // TODO: safe references
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
  TF_SessionWithGraph* session = ObjectWrap::Unwrap<Session>(info.Holder())->ref();
  addons::Session::run(session, info);
}

void Session::run(TF_SessionWithGraph* session, const Nan::FunctionCallbackInfo<v8::Value>& info) {
  bool outputs = (info.Length() >= 2) ? info[1]->BooleanValue() : true; // TODO: infer the output instead of having a separate function

  // operations
  std::vector<TF_Operation*> ops;
  if (info[0]->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
    for (unsigned int i = 0; i < jsArray->Length(); i++) ops.push_back(ObjectWrap::Unwrap<Operation>(jsArray->Get(i)->ToObject())->ref());
  }
  else ops.push_back(ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref());

  // inputs
  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;
  if (info[1]->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info[1]);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      TF_Operation* in = ObjectWrap::Unwrap<addons::Operation>(pair->Get(0)->ToObject())->ref();
      TF_Tensor* va = lib::ToTensor(pair->Get(1));
      input_ports.push_back(TF_Port({in, 0}));
      input_tensors.push_back(va);
    }
  }

  // outputs
  std::vector<TF_Tensor*> results;
  std::vector<TF_Port> output_ports;
  for (std::size_t i = 0; i < ops.size(); i++) {
    if (!ops[i]) { std::cout << "Skipping run: operation is missing" << "\n"; return;}
    if (!outputs) continue;
    output_ports.push_back(TF_Port({ops[i], 0}));
    results.push_back(nullptr);
  }

  TF_Status* s = TF_NewStatus();
  if (outputs) {
    TF_SessionRun(
      session, nullptr,
      &input_ports[0], &input_tensors[0], (int) input_ports.size(),
      &output_ports[0], &results[0], (int) output_ports.size(),
      nullptr, 0,
      nullptr, s
    );
  }
  else {
    TF_SessionRun(
      session, nullptr,
      &input_ports[0], &input_tensors[0], (int) input_ports.size(),
      nullptr, nullptr, 0,
      &ops[0], (int) ops.size(),
      nullptr, s
    );
  }

  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);

  if (outputs) {
    if (info[0]->IsArray()) info.GetReturnValue().Set(lib::ToArrayValue(results));
    else if (results.size()) info.GetReturnValue().Set(lib::ToValue(results[0]));
  }
}

} // namespace addons
