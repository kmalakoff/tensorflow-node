#include "neural_network.h"
#include "graph.h"
#include "operation.h"
#include "../../lib/conversions.h"

#include "tensorflow/core/graph/node_builder.h"
#include "tensorflow/cc/framework/grad_op_registry.h"
#include "tensorflow/cc/ops/standard_ops.h"

namespace addons {

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace v8;

NAN_MODULE_INIT(NeuralNetwork::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "softmax", softmax);
  Nan::SetMethod(obj, "softmax_cross_entropy_with_logits", softmax_cross_entropy_with_logits);

  target->Set(Nan::New("NeuralNetwork").ToLocalChecked(), obj);
};

NAN_METHOD(NeuralNetwork::softmax) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;

  auto result = Softmax(scope, arg1);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(NeuralNetwork::softmax_cross_entropy_with_logits) {
  auto& scope = ObjectWrap::Unwrap<Graph>(info[0]->ToObject())->m_scope;
  auto& arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->m_output;
  auto& arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->m_output;

  auto result = SoftmaxCrossEntropyWithLogits(scope, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result.loss))->ToValue()); // TODO: is only loss correct?
}

} // namespace addons
