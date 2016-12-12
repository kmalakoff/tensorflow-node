#include <iostream>
#include "session.h"
#include "graph.h"
#include "../../lib/conversions.h"
#include "../../lib/utils.h"
#include "operation.h"

#include "tensorflow/core/graph/node_builder.h"
#include "tensorflow/cc/ops/math_ops.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/cc/framework/ops.h"

namespace addons {

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace v8;

Session::Session(Graph* graph) : m_scope(graph->m_scope) {
  SessionOptions options;
  m_session = NewSession(options);
}
Session::~Session() {
  m_session->Close(); m_session = nullptr;
  // /* m_graph->Unref(); */ m_scope = nullptr; // TODO: safe references
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
  tensorflow::Session* session = ObjectWrap::Unwrap<Session>(info.Holder())->m_session;
  tensorflow::Scope& scope = ObjectWrap::Unwrap<Session>(info.Holder())->m_scope;

  Session::run(session, scope, info);
}

void Session::run(tensorflow::Session* session, tensorflow::Scope& scope, const Nan::FunctionCallbackInfo<v8::Value>& info) {
  bool outputs = (info.Length() >= 2) ? info[1]->NumberValue() : true; // TODO: infer the output instead of having a separate function

  GraphDef def;
  TF_CHECK_OK(scope.ToGraphDef(&def));
  graph::SetDefaultDevice("/cpu:0", &def);
  TF_CHECK_OK(session->Create(def));

  // operations
  std::vector<string> ops;
  if (info[0]->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
    for (unsigned int i = 0; i < jsArray->Length(); i++) ops.push_back(lib::nodeName(ObjectWrap::Unwrap<Operation>(jsArray->Get(i)->ToObject())->m_output.node()));
  }
  else ops.push_back(lib::nodeName(ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_output.node()));

  // inputs
  std::vector<std::pair<string, Tensor>> arg1;
  if (info[1]->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info[1]);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      Output out = ObjectWrap::Unwrap<Operation>(pair->Get(0)->ToObject())->m_output;
      string name = lib::nodeName(out.node());
      tensorflow::Tensor* va = lib::ToTensor2(pair->Get(1));
      arg1.push_back(std::pair<string, Tensor>(name, *va));
      delete va; // TODO:: memory
    }
  }

  // outputs
  std::vector<Tensor> results;
  if (outputs) {
    TF_CHECK_OK(session->Run(arg1, ops, {}, &results));
  }
  else {
    TF_CHECK_OK(session->Run(arg1, {}, ops, &results));
  }
  if (outputs) info.GetReturnValue().Set(info[0]->IsArray() ? lib::ToArrayValue(results) : lib::ToValue(results[0]));
}

} // namespace addons
