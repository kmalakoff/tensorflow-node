#include "neural_network.h"
#include "graph.h"
#include "operation.h"
#include "../../lib/conversions.h"
#include "../tf_ops.h"

namespace addons {

using namespace tf::ops;
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
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg0 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 

  TF_Operation* result = Softmax(graph, arg0);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

NAN_METHOD(NeuralNetwork::softmax_cross_entropy_with_logits) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg1 = ObjectWrap::Unwrap<addons::Operation>(info[1]->ToObject())->ref(); 
  TF_Operation* arg2 = ObjectWrap::Unwrap<addons::Operation>(info[2]->ToObject())->ref(); 

  TF_Operation* result = SoftmaxCrossEntropyWithLogits(graph, arg1, arg2);
  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
