#include <iostream>
#include "neural_network.h"
#include "../addons/operation.h"
#include "../../lib/utils.h"
#include "../../lib/conversions.h"

namespace tf {

using namespace v8;
using namespace Nan;
using namespace addons;

TF_Operation* NeuralNetwork::softmax(TF_Graph *graph, TF_Operation* v) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Softmax", lib::uniqueId("Softmax").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port v_input = {v, 0};
  TF_AddInput(desc, v_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* NeuralNetwork::softmax_cross_entropy_with_logits(TF_Graph *graph, TF_Operation* y, TF_Operation* y_) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "SoftmaxCrossEntropyWithLogits", lib::uniqueId("SoftmaxCrossEntropyWithLogits").c_str());
  // TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port input_y = {y, 0};
  TF_AddInput(desc, input_y);
  TF_Port input_y_ = {y_, 0};
  TF_AddInput(desc, input_y_);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

} // namespace tf
