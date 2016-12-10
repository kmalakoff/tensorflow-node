#include "Train.h"
#include "Graph.h"
#include "Operation.h"
#include "../tensorflow/Graph.h"
#include "../lib/Conversions.h"

namespace addons {

using namespace v8;

NAN_MODULE_INIT(Train::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "GradientDescentOptimizer", GradientDescentOptimizer);

  target->Set(Nan::New("Train").ToLocalChecked(), obj);
};

NAN_METHOD(Train::GradientDescentOptimizer) {
  // Graph* obj = ObjectWrap::Unwrap<Graph>(info.Holder());
  
  // TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  // TF_Operation* arg1 = ObjectWrap::Unwrap<Operation>(info[1]->ToObject())->ref(); 
  // TF_Operation* result = obj->ref()->matmul(arg0, arg1);

  // info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
