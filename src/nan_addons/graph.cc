#include <iostream>
#include "nan.h"
#include "tensorflow/core/platform/types.h"
#include "graph.h"
#include "../core/graph.h"
#include "operation.h"

namespace nan_addons {

using namespace tensorflow;
using namespace v8;

Graph::Graph() { m_graph = new tensorflow::Graph(); }
Graph::~Graph() {}

NAN_METHOD(Graph::constant) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Tensor* arg0 = VALUE_TO_TENSOR(info[0]); 
  TF_Operation* result = obj->m_graph->constant(arg0);

  info.GetReturnValue().Set(WRAPPER_OBJECT_TO_VALUE(new Operation(result)));
}

NAN_METHOD(Graph::matmul) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* arg0 = VALUE_TO_WRAPPER_OBJECT(Operation, info[0])->ref(); 
  TF_Operation* arg1 = VALUE_TO_WRAPPER_OBJECT(Operation, info[1])->ref(); 
  TF_Operation* result = obj->m_graph->matmul(arg0, arg1);

  info.GetReturnValue().Set(WRAPPER_OBJECT_TO_VALUE(new Operation(result)));
}

NAN_METHOD(Graph::run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  std::vector<TF_Operation*> arg0;
  Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    arg0.push_back(VALUE_TO_WRAPPER_OBJECT(Operation, jsArray->Get(i))->ref());
  }

  Handle<Array> arg1 = Handle<Array>::Cast(info[1]);

  std::vector<TF_Tensor*> results;
  obj->m_graph->run(results, arg0, arg1);

  v8::Local<v8::Array> arr = Nan::New<v8::Array>(results.size());
  for (std::size_t i = 0; i < results.size(); i++) {
    Nan::Set(arr, i, TENSOR_TO_BUFFER_VALUE(results[i]));
  }
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Graph::Placeholder) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Operation* result = obj->m_graph->Placeholder();
  info.GetReturnValue().Set(WRAPPER_OBJECT_TO_VALUE(new Operation(result)));
}

NAN_METHOD(Graph::ScalarConst) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Tensor* arg0 = VALUE_TO_TENSOR(info[0]); 
  TF_Operation* result = obj->m_graph->ScalarConst(arg0);

  info.GetReturnValue().Set(WRAPPER_OBJECT_TO_VALUE(new Operation(result)));
}

NAN_METHOD(Graph::Add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = VALUE_TO_WRAPPER_OBJECT(Operation, info[0])->ref(); 
  TF_Operation* arg1 = VALUE_TO_WRAPPER_OBJECT(Operation, info[1])->ref(); 

  TF_Operation* result = obj->m_graph->Add(arg0, arg1);
  info.GetReturnValue().Set(WRAPPER_OBJECT_TO_VALUE(new Operation(result)));
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
  Nan::SetPrototypeMethod(ctor, "constant", constant);
  Nan::SetPrototypeMethod(ctor, "matmul", matmul);
  Nan::SetPrototypeMethod(ctor, "run", run);
  Nan::SetPrototypeMethod(ctor, "Placeholder", Placeholder);
  Nan::SetPrototypeMethod(ctor, "ScalarConst", ScalarConst);
  Nan::SetPrototypeMethod(ctor, "Add", Add);

  target->Set(Nan::New("Graph").ToLocalChecked(), ctor->GetFunction());
}

NAN_NEW(Graph::New) {
  Nan::HandleScope scope;

  Graph *instance = new Graph();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan_addons
