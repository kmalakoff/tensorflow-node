#include <iostream>
#include "nan.h"
#include "tensorflow/core/platform/types.h"
#include "conversions.h"
#include "graph.h"
#include "../core/graph.h"
#include "operation.h"

namespace nan_bridge {

using namespace tensorflow;
using namespace v8;
using namespace nan_bridge;

Graph::Graph() { m_graph = new tensorflow::Graph(); }
Graph::~Graph() { delete m_graph; m_graph = nullptr; }

NAN_METHOD(Graph::input) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Operation* result = obj->m_graph->input();
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::constant) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Tensor* arg0 = ToTensor(info[0]); 
  TF_Operation* result = obj->m_graph->constant(arg0);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = obj->m_graph->add(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::matmul) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* result = obj->m_graph->matmul(arg0, arg1);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

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
  obj->m_graph->run(results, arg0, info[1]);

  info.GetReturnValue().Set(info[0]->IsArray() ? ToArrayValue(results) : nan_bridge::ToValue(results[0]));
}
/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
NAN_MODULE_INIT(Graph::Init) {
  Nan::HandleScope scope;

  // Class
  Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Graph::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Graph").ToLocalChecked());
  constructor.Reset(ctor);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "input", input);
  Nan::SetPrototypeMethod(ctor, "constant", constant);
  Nan::SetPrototypeMethod(ctor, "add", add);
  Nan::SetPrototypeMethod(ctor, "matmul", matmul);
  Nan::SetPrototypeMethod(ctor, "run", run);

  target->Set(Nan::New("Graph").ToLocalChecked(), ctor->GetFunction());
}

NAN_CONSTRUCTOR(Graph::constructor);

NAN_NEW(Graph::New) {
  Nan::HandleScope scope;

  Graph *instance = new Graph();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan_bridge
