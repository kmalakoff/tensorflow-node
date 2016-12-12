#include "train.h"
#include "graph.h"
#include "operation.h"
#include "../tf/train.h"
#include "../../lib/conversions.h"

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
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  float arg0 = info[1]->NumberValue();
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;

  // TF_Operation* result = tf::Train::GradientDescentOptimizer(graph, arg0, arg1);
  // info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
