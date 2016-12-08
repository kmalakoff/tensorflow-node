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
  
  TF_Operation* result = obj->m_graph->constant(NAN_IN_TO_TENSOR(info[0]));
  info.GetReturnValue().Set(NAN_OUT_WRAP_OBJECT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::matmul) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* arg0 = NAN_IN_WRAP_OBJECT(Operation, info[0])->ref(); 
  TF_Operation* arg1 = NAN_IN_WRAP_OBJECT(Operation, info[1])->ref(); 

  TF_Operation* result = obj->m_graph->matmul(arg0, arg1);
  info.GetReturnValue().Set(NAN_OUT_WRAP_OBJECT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  std::vector<TF_Operation*> arg0;
  Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    TF_Operation* value0 = NAN_IN_WRAP_OBJECT(Operation, jsArray->Get(i))->ref();
    arg0.push_back(value0);
  }
  Handle<Object> arg1 = Handle<Object>::Cast(info[1]);
  std::vector<TF_Tensor*> results;
  obj->m_graph->run(results, arg0, arg1);

  // v8::Local<v8::Array> arr = Nan::New<v8::Array>(results.size());
  // for (std::size_t i = 0; i < results.size(); i++) {
  //   TF_Tensor* value = results[i];
  //   Nan::Set(arr, i, Nan::New(*static_cast<int32*>(TF_TensorData(value))));
  // }
  // info.GetReturnValue().Set(arr);
}

NAN_METHOD(Graph::Placeholder) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Operation* result = obj->m_graph->Placeholder();
  info.GetReturnValue().Set(NAN_OUT_WRAP_OBJECT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::ScalarConst) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  char* buf = NAN_IN_BUFFER_DATA(info[0]);
  size_t len = NAN_IN_BUFFER_LENGTH(info[0]);
  int arg0 = *((int32*) buf);

  TF_Operation* result = obj->m_graph->ScalarConst(arg0);
  info.GetReturnValue().Set(NAN_OUT_WRAP_OBJECT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::Add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = NAN_IN_WRAP_OBJECT(Operation, info[0])->ref(); 
  TF_Operation* arg1 = NAN_IN_WRAP_OBJECT(Operation, info[1])->ref(); 

  TF_Operation* result = obj->m_graph->Add(arg0, arg1);
  info.GetReturnValue().Set(NAN_OUT_WRAP_OBJECT(Operation, TF_Operation*, result));
}

NAN_METHOD(Graph::Run) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  std::vector<TF_Operation*> arg0;
  Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    TF_Operation* value0 = NAN_IN_WRAP_OBJECT(Operation, jsArray->Get(i))->ref();
    arg0.push_back(value0);
  }
  Handle<Object> arg1 = Handle<Object>::Cast(info[1]);
  std::vector<TF_Tensor*> results;
  obj->m_graph->Run(results, arg0, arg1);

  v8::Local<v8::Array> arr = Nan::New<v8::Array>(results.size());
  for (std::size_t i = 0; i < results.size(); i++) {
    TF_Tensor* value = results[i];
    Nan::Set(arr, i, Nan::New(*static_cast<int32*>(TF_TensorData(value))));
  }
  info.GetReturnValue().Set(arr);
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
  Nan::SetPrototypeMethod(ctor, "Run", Run);

  target->Set(Nan::New("Graph").ToLocalChecked(), ctor->GetFunction());
}

NAN_NEW(Graph::New) {
  Nan::HandleScope scope;

  Graph *instance = new Graph();
  instance->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

} // namespace nan_addons


    // Local<Object> buf = Nan::NewBuffer(TF_TensorByteSize(value)).ToLocalChecked();
    // uint8* data = (uint8*) node::Buffer::Data(buf);
    // memcpy(data, TF_TensorData(value), TF_TensorByteSize(value));

    // v8::Local<v8::Object> globalObj = Nan::GetCurrentContext()->Global();
    // v8::Local<v8::Function> bufferConstructor = v8::Local<v8::Function> ::Cast(globalObj->Get(Nan::New<String>("Buffer").ToLocalChecked()));
    // v8::Local<v8::Value> constructorArgs[3] = {buf, Nan::New<v8::Integer>((unsigned)TF_TensorByteSize(value)), Nan::New<v8::Integer>(0)};
    // v8::Local<v8::Object> bufferValue = Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();
    // Nan::Set(arr, i, bufferValue);
