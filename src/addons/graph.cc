#include <iostream>

#include "graph.h"
#include "conversions.h"
#include "operation.h"
#include "../tensorflow/graph.h"

namespace addons {

using namespace tensorflow;
using namespace v8;
using namespace addons;

Graph::Graph() { m_ref = new tensorflow::Graph(); }
Graph::~Graph() { delete m_ref; m_ref = nullptr; }

NAN_METHOD(Graph::placeholder) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_DataType arg0 = TF_FLOAT;
  std::vector<int64_t> arg1;

  if (info.Length() >= 1) arg0 = (TF_DataType) info[0]->NumberValue();
  if (info.Length() >= 2) ToShape(arg1, info[1]);

  TF_Operation* result = obj->m_ref->placeholder(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Tensor* arg0 = ToTensor(info[0]); 
  std::vector<int64_t> arg1; ToShape(arg1, info[0]);
  TF_Operation* result = obj->m_ref->variable(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::constant) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());

  TF_Tensor* arg0 = ToTensor(info[0]); 
  TF_Operation* result = obj->m_ref->constant(arg0);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = obj->m_ref->add(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::matmul) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* result = obj->m_ref->matmul(arg0, arg1);

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
  obj->m_ref->run(results, arg0, info[1]);

  info.GetReturnValue().Set(info[0]->IsArray() ? ToArrayValue(results) : addons::ToValue(results[0]));
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
  Nan::SetPrototypeMethod(ctor, "placeholder", placeholder);
  Nan::SetPrototypeMethod(ctor, "variable", variable);
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

} // namespace addons
