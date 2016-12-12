#include <iostream>
#include "math_ops.h"
#include "graph.h"
#include "operation.h"
#include "../../lib/conversions.h"

#include "../tf_ops.h"
#include "tensorflow/cc/ops/math_ops.h"
#include "tensorflow/cc/ops/const_op.h"

namespace addons {

using namespace tf::ops;
using namespace v8;
using namespace tensorflow;
using namespace ops;

NAN_MODULE_INIT(MathOps::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "add", add);
  Nan::SetMethod(obj, "matmul", matmul);
  Nan::SetMethod(obj, "matmul_add", matmul_add);
  Nan::SetMethod(obj, "reduce_mean", reduce_mean);
  Nan::SetMethod(obj, "equal", equal);
  Nan::SetMethod(obj, "argmax", argmax);
  Nan::SetMethod(obj, "cast", cast);
  Nan::SetMethod(obj, "log", log);

  target->Set(Nan::New("MathOps").ToLocalChecked(), obj);
};

NAN_METHOD(MathOps::add) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;

  auto result = Add(scope.WithOpName("Add"), arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;

  auto result = MatMul(scope.WithOpName("MatMul"), arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul_add) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;
  auto& arg3 = ObjectWrap::Unwrap<addons::Operation>(info[3]->ToObject())->m_output;

  auto result1 = MatMul(scope.WithOpName("MatMul"), arg1, arg2);
  auto result2 = Add(scope.WithOpName("Add"), result1, arg3);
  info.GetReturnValue().Set((new Operation(result2))->ToValue());
}

NAN_METHOD(MathOps::reduce_mean) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  Tensor* arg2 = lib::ToTensor2(0);
  
  auto reduction_indices = Const<int>(scope, *arg2); // delete arg2;
  auto result = ReduceMean(scope, arg1, reduction_indices);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::equal) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;

  auto result = Equal(scope.WithOpName("Equal"), arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::argmax) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  int dim = (info.Length() >= 3) ? info[2]->NumberValue() : 0;

  auto result = ArgMax(scope, arg1, dim);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::cast) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto arg2 = info[2]->NumberValue();

  auto result = tf::ops::Cast(scope, arg1, (DataType) arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::log) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;

  auto result = Log(scope, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
