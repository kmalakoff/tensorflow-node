#include <iostream>
#include "math_ops.h"
#include "graph.h"
#include "operation.h"
#include "../../lib/conversions.h"
#include "../tf_ops.h"

namespace addons {

using namespace tf::ops;
using namespace v8;

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
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = Add(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = MatMul(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul_add) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 
  TF_Operation* arg3 = ObjectWrap::Unwrap<addons::Operation>(info[3]->ToObject())->ref(); 

  auto result1 = MatMul(graph, arg1, arg2);
  auto result2 = Add(graph, result1, arg3);
  info.GetReturnValue().Set((new Operation(result2))->ToValue());
}

NAN_METHOD(MathOps::reduce_mean) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 

  TF_Tensor* arg2 = lib::ToTensor(0);
  auto reduction_indices = Const(graph, arg2);
  auto result = Mean(graph, arg1, reduction_indices); // TF_DeleteTensor(arg2); // constant takes over tensor ownership
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::equal) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = Equal(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::argmax) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  int dim = (info.Length() >= 3) ? info[2]->NumberValue() : 0;

  TF_Operation* result = ArgMax(graph, arg1, dim);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::cast) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_DataType arg2 = (TF_DataType) info[2]->NumberValue(); 

  TF_Operation* result = Cast(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::log) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = Log(graph, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
