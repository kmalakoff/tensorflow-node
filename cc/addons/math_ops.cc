#include "math_ops.h"
#include "graph.h"
#include "operation.h"
#include "../lib/conversions.h"
#include "../tensorflow/math_ops.h"

namespace addons {

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

  TF_Operation* result = tensorflow::MathOps::add(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = tensorflow::MathOps::matmul(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul_add) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 
  TF_Operation* arg3 = ObjectWrap::Unwrap<addons::Operation>(info[3]->ToObject())->ref(); 

  TF_Operation* result = tensorflow::MathOps::matmul_add(graph, arg1, arg2, arg3);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::reduce_mean) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = tensorflow::MathOps::reduce_mean(graph, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::equal) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = tensorflow::MathOps::matmul(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::argmax) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  int arg2 = info[2]->NumberValue(); 

  TF_Operation* result = tensorflow::MathOps::argmax(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::cast) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref();
  TF_DataType arg2 = (TF_DataType) info[2]->NumberValue(); 

  TF_Operation* result = tensorflow::MathOps::cast(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::log) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = tensorflow::MathOps::log(graph, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
