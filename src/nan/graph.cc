#include <iostream>
#include "nan.h"
#include "tensorflow/core/platform/types.h"
#include "graph.h"
#include "../core/graph.h"
#include "operation.h"

namespace nan {

using namespace tensorflow;
using namespace v8;

Graph::Graph() { m_graph = new tensorflow::Graph(); }
Graph::~Graph() {}

NAN_METHOD(Graph::Placeholder) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* result = obj->m_graph->Placeholder();
  info.GetReturnValue().Set(NAN_WRAP_RESULT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::ScalarConst) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  int arg0 = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();

  TF_Operation* result = obj->m_graph->ScalarConst(arg0);
  info.GetReturnValue().Set(NAN_WRAP_RESULT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::Add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = Nan::ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref();

  TF_Operation* result = obj->m_graph->Add(arg0, arg1);
  info.GetReturnValue().Set(NAN_WRAP_RESULT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::Run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  std::vector<TF_Operation*> arg0;
  Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
  TF_Operation* value0;
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    value0 = Nan::ObjectWrap::Unwrap<Operation>(jsArray->Get(i)->ToObject())->ref();
    arg0.push_back(value0);
  }
  Handle<Object> arg1 = Handle<Object>::Cast(info[1]);

  std::vector<TF_Tensor*> results;
  obj->m_graph->Run(results, arg0, arg1);

  TF_Tensor* out = results[0];
  info.GetReturnValue().Set(Nan::New(*static_cast<int32*>(TF_TensorData(out))));
}

/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
NAN_CONSTRUCTOR(Graph::constructor);
NAN_MODULE_INIT(Graph::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Graph::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Graph").ToLocalChecked());
  constructor.Reset(ctor);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "Placeholder", Placeholder);
  Nan::SetPrototypeMethod(ctor, "ScalarConst", ScalarConst);
  Nan::SetPrototypeMethod(ctor, "Add", Add);
  Nan::SetPrototypeMethod(ctor, "Run", Run);

  target->Set(Nan::New("Graph").ToLocalChecked(), ctor->GetFunction());
}

NAN_NEW(Graph::New) {
  Nan::HandleScope scope;

  Graph *instance = new Graph();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan