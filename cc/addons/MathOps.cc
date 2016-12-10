#include "MathOps.h"
#include "Graph.h"
#include "Operation.h"
#include "../tensorflow/Graph.h"
#include "../lib/Conversions.h"

namespace addons {

using namespace v8;

NAN_MODULE_INIT(MathOps::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "add", add);
  Nan::SetMethod(obj, "matmul", matmul);

  target->Set(Nan::New("MathOps").ToLocalChecked(), obj);
};

NAN_METHOD(MathOps::add) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = obj->ref()->add(arg0, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(MathOps::matmul) {
  Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* result = obj->ref()->matmul(arg0, arg1);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
