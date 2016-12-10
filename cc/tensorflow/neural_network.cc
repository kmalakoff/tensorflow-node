#include <iostream>
#include "neural_network.h"
#include "../addons/operation.h"
#include "../lib/utils.h"
#include "../lib/conversions.h"

namespace tensorflow {

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
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* NeuralNetwork::softmax_cross_entropy_with_logits(TF_Graph *graph, TF_Operation* y, TF_Operation* y_) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Softmax", lib::uniqueId("Softmax").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port v_input = {y, 0};
  TF_AddInput(desc, v_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

} // namespace tensorflow

  // with variable_scope.variable_scope(scope, 'softmax', [logits]):
  //   num_logits = utils.last_dimension(logits.get_shape(), min_rank=2)
  //   logits_2d = array_ops.reshape(logits, [-1, num_logits])
  //   predictions = nn.softmax(logits_2d)
  //   predictions = array_ops.reshape(predictions, array_ops.shape(logits))
  //   predictions.set_shape(logits.get_shape())
  //   return predictions
