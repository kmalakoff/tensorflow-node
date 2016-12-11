#include <iostream>

#include "graph.h"
#include "operation.h"
#include "../tensorflow/graph.h"
#include "../tensorflow/session.h"
#include "../tensorflow/tensor.h"
#include "../lib/conversions.h"

namespace addons {

using namespace tensorflow;
using namespace v8;
using namespace addons;

Graph::Graph() { m_ref = tensorflow::Graph::create(); }
Graph::~Graph() { tensorflow::Graph::destroy(m_ref); m_ref = nullptr; }

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
  Nan::SetPrototypeMethod(ctor, "variable_initializers", variable_initializers);
  Nan::SetPrototypeMethod(ctor, "constant", constant);
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

NAN_METHOD(Graph::placeholder) {
  TF_Graph* graph = ObjectWrap::Unwrap<Graph>(info.Holder())->ref();
  TF_DataType arg0 = TF_FLOAT;
  std::vector<int64_t> arg1;

  if (info.Length() >= 1) arg0 = (TF_DataType) info[0]->NumberValue();
  if (info.Length() >= 2) lib::ToShape(arg1, info[1]);

  TF_Operation* result = tensorflow::Graph::placeholder(graph, arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable) {
  TF_Graph* graph = ObjectWrap::Unwrap<Graph>(info.Holder())->ref();
  TF_Tensor* arg0 = lib::ToTensor(info[0]); 
  std::vector<int64_t> arg1; lib::ToShape(arg1, arg0);

  TF_Operation* result = tensorflow::Graph::variable(graph, arg0->dtype, arg1);

  // https://www.tensorflow.org/versions/master/how_tos/variables/index.html
  std::vector<TF_Operation*>& variable_initializers = ObjectWrap::Unwrap<Graph>(info.Holder())->m_variable_initializers;
  variable_initializers.push_back(tensorflow::Graph::variableInitializer(graph, result, arg0));

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable_initializers) {
  std::vector<TF_Operation*>& variable_initializers = ObjectWrap::Unwrap<Graph>(info.Holder())->m_variable_initializers;
  Local<Array> results = Nan::New<v8::Array>((int) variable_initializers.size());
  for (size_t i = 0; i < variable_initializers.size(); i++)
    results->Set((int) i, (new Operation(variable_initializers[i]))->ToValue());

  info.GetReturnValue().Set(results);
}

NAN_METHOD(Graph::constant) {
  TF_Graph* graph = ObjectWrap::Unwrap<Graph>(info.Holder())->ref();

  TF_Tensor* arg0 = lib::ToTensor(info[0]); 

//  std::cout << TF_TensorDims(arg0)

  TF_Operation* result = tensorflow::Graph::constant(graph, arg0);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::run) {
  TF_Graph* graph = ObjectWrap::Unwrap<Graph>(info.Holder())->ref();

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
  tensorflow::Graph::run(results, graph, arg0, info[1]);

  info.GetReturnValue().Set(info[0]->IsArray() ? lib::ToArrayValue(results) : lib::ToValue(results[0]));
}

} // namespace addons
