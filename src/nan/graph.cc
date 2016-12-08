#include <iostream>
#include "graph.h"
#include "../core/graph.h"
#include "tensorflow/c/c_api.h"
#include "operation.h"

namespace nan {

Graph::Graph() { m_graph = new tensorflow::Graph(); }
Graph::~Graph() {}

NAN_METHOD(Graph::Placeholder) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Operation::constructor)->GetFunction()).ToLocalChecked();
  (new Operation(obj->m_graph->Placeholder()))->Wrap(result);
  info.GetReturnValue().Set(result);
}

NAN_METHOD(Graph::ScalarConst) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  int arg0 = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();

  v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Operation::constructor)->GetFunction()).ToLocalChecked();
  (new Operation(obj->m_graph->ScalarConst(arg0)))->Wrap(result);
  info.GetReturnValue().Set(result);
}

NAN_METHOD(Graph::Add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->m_operation;
  TF_Operation* arg1 = Nan::ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->m_operation;

  v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Operation::constructor)->GetFunction()).ToLocalChecked();
  (new Operation(obj->m_graph->Add(arg0, arg1)))->Wrap(result);
  info.GetReturnValue().Set(result);
}

NAN_METHOD(Graph::Run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  std::vector<int> arg0;
  v8::Handle<v8::Array> jsArray = v8::Handle<v8::Array>::Cast(info[0]);
  for (unsigned int i = 0; i < jsArray->Length(); i++) { arg0.push_back(jsArray->Get(i)->NumberValue()); }
  int arg1 = info[0]->IsUndefined() ? 0 : info[1]->NumberValue();

  info.GetReturnValue().Set(Nan::New(obj->m_graph->Run(arg0, arg1)));
}

/////////////////////////////////
// Nan Lifecycle
/////////////////////////////////
Nan::Persistent<v8::FunctionTemplate> Graph::constructor;

NAN_MODULE_INIT(Graph::Init) {
  Nan::HandleScope scope;

  // Class
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Graph::New);
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

void Graph::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;

  Graph *instance = new Graph();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan