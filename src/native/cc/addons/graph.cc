#include <iostream>

#include "graph.h"
#include "operation.h"
#include "session.h"
#include "../tf/graph.h"
#include "../tf/session.h"
#include "../tf/tensor.h"
#include "../../lib/conversions.h"
#include "../../lib/utils.h"

#include "tensorflow/core/graph/node_builder.h"
#include "tensorflow/cc/ops/math_ops.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"

namespace addons {

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace v8;
using namespace addons;

Graph::Graph() : m_scope(tensorflow::Scope::NewRootScope()) {}
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

  // TODO: wrap in a Placeholder function
  tensorflow::TensorShape shape(arg1);
  const auto op_name = scope.GetUniqueNameForOp("Placeholder");
  auto builder = tensorflow::NodeBuilder(op_name, "Placeholder")
    .Attr("dtype", (DataType) arg0)
    .Attr("shape", shape);
  scope.UpdateBuilder(&builder);
  tensorflow::Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  auto result = Output(ret, 0);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(Graph::variable) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info.Holder())->m_scope;
  tensorflow::Tensor* arg0 = lib::ToTensor2(info[0]);
  std::vector<int64_t> arg1; lib::ToShape(arg1, *arg0);

  // TODO: wrap in a Variable function
  tensorflow::TensorShape shape(arg1);
  const auto op_name = scope.GetUniqueNameForOp("Variable");
  auto builder = tensorflow::NodeBuilder(op_name, "Variable")
    .Attr("dtype", DT_FLOAT)
    .Attr("shape", shape);
  scope.UpdateBuilder(&builder);
  tensorflow::Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  auto result = Output(ret, 0);

  // https://www.tensorflow.org/versions/master/how_tos/variables/index.html
  auto& variable_initializers = ObjectWrap::Unwrap<Graph>(info.Holder())->m_variable_initializers;
  auto value = Const<float>(scope, *arg0); delete arg0;
  const auto op_name1 = scope.GetUniqueNameForOp("Assign");
  auto builder1 = tensorflow::NodeBuilder(op_name1, "Assign")
    .Input(result.node())
    .Input(value.node())
    .Attr("use_locking", true);
  scope.UpdateBuilder(&builder1);
  tensorflow::Node* ret1;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret1));
  auto assign = Output(ret1, 0);
  variable_initializers.push_back(assign);

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
  tensorflow::Tensor* arg0 = lib::ToTensor2(info[0]);

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