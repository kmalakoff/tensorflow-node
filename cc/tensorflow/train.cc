#include <iostream>
#include "train.h"
#include "graph.h"
#include "../addons/operation.h"
#include "../lib/utils.h"
#include "../lib/conversions.h"

namespace tensorflow {

using namespace v8;
using namespace Nan;
using namespace addons;

TF_Operation* Train::GradientDescentOptimizer(TF_Graph *graph, float learning_rate, TF_Operation* v) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "ApplyGradientDescent", lib::uniqueId("ApplyGradientDescent").c_str());

  TF_Port input_alpha = {Graph::constant(graph, lib::ToTensor(0.0f)), 0};
  TF_AddInput(desc, input_alpha);
  TF_Port input_delta = {Graph::constant(graph, lib::ToTensor(0.0f)), 0};
  TF_AddInput(desc, input_delta);

  // TF_SetAttrType(desc, "T", TF_FLOAT);
  // TF_SetAttrFloat(desc, "alpha", 0);
  // TF_SetAttrFloat(desc, "delta", 0);
//  TF_Port v_input = {v, 0};
//  TF_AddInput(desc, v_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

} // namespace tensorflow
