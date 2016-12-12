#include <iostream>

#include "graph.h"
#include "operation.h"
#include "session.h"
#include "../../lib/conversions.h"
#include "../../lib/utils.h"

#include "../tf_ops.h"
#include "tensorflow/cc/ops/math_ops.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/framework/tensor.h"

namespace addons {

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace tf::ops;
using namespace v8;
using namespace addons;

Graph::Graph() : m_scope(Scope::NewRootScope()) {}
Graph::~Graph() {}

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
  auto& scope = ObjectWrap::Unwrap<Graph>(info.Holder())->m_scope;
  TF_DataType arg0 = (info.Length() >= 1) ? (TF_DataType) info[0]->NumberValue() : TF_FLOAT;
  std::vector<int64_t> arg1; if (info.Length() >= 2) lib::ToShape(arg1, info[1]);

  auto result = Placeholder(scope, (DataType) arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info.Holder())->m_scope;
  Tensor* arg0 = lib::ToTensor2(info[0]);
  std::vector<int64_t> arg1; lib::ToShape(arg1, *arg0);

  auto result = Variable(scope, (DataType) arg0->dtype(), arg1);

  // https://www.tensorflow.org/versions/master/how_tos/variables/index.html
  auto value = Const<float>(scope, *arg0); delete arg0;
  auto assign = Assign(scope, result, value);
  ObjectWrap::Unwrap<Graph>(info.Holder())->m_variable_initializers.push_back(assign);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable_initializers) {
  auto& variable_initializers = ObjectWrap::Unwrap<Graph>(info.Holder())->m_variable_initializers;
  Local<Array> results = Nan::New<v8::Array>((int) variable_initializers.size());
  for (size_t i = 0; i < variable_initializers.size(); i++)
    results->Set((int) i, (new Operation(variable_initializers[i]))->ToValue());

  info.GetReturnValue().Set(results);
}

NAN_METHOD(Graph::constant) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info.Holder())->m_scope;
  Tensor* arg0 = lib::ToTensor2(info[0]);

  auto result = Const<float>(scope, *arg0); delete arg0;
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::run) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info.Holder())->m_scope;

  SessionOptions options;
  tensorflow::Session* session = NewSession(options);
  addons::Session::run(session, scope, info);
  TF_CHECK_OK(session->Close());
}

} // namespace addons
