#include "math_ops.h"
#include "graph.h"
#include "operation.h"
#include "../tensorflow/graph.h"
#include "../lib/conversions.h"

namespace addons {

using namespace v8;

NAN_MODULE_INIT(MathOps::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "add", add);
  Nan::SetMethod(obj, "matmul", matmul);
  Nan::SetMethod(obj, "reduce_mean", reduce_mean);
  Nan::SetMethod(obj, "reduce_sum", reduce_sum);
  Nan::SetMethod(obj, "log", log);

  target->Set(Nan::New("MathOps").ToLocalChecked(), obj);
};

NAN_METHOD(MathOps::add) {
  tensorflow::Graph* obj = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg0 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = obj->add(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul) {
  tensorflow::Graph* obj = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg0 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = obj->matmul(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::reduce_mean) {}
NAN_METHOD(MathOps::reduce_sum) {}
NAN_METHOD(MathOps::log) {}

} // namespace addons
