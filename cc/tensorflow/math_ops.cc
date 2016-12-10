#include "math_ops.h"
#include "../tensorflow/tensor.h"
#include "../addons/operation.h"
#include "../lib/utils.h"
#include "../lib/conversions.h"

namespace tensorflow {

using namespace v8;
using namespace Nan;
using namespace addons;

TF_Operation* MathOps::add(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Add", lib::uniqueId("Add").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port l_input = {l, 0};
  TF_AddInput(desc, l_input);
  TF_Port r_input = {r, 0};
  TF_AddInput(desc, r_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* MathOps::matmul(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "MatMul", lib::uniqueId("MatMul").c_str());

  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port l_input = {l, 0};
  TF_AddInput(desc, l_input);
  TF_Port r_input = {r, 0};
  TF_AddInput(desc, r_input);
  TF_SetAttrBool(desc, "transpose_a", false);
  TF_SetAttrBool(desc, "transpose_b", false);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* MathOps::matmul_add(TF_Graph *graph, TF_Operation* l, TF_Operation* r, TF_Operation* a) {

}

TF_Operation* MathOps::reduce_mean(TF_Graph *graph, TF_Operation* v) {

}

TF_Operation* MathOps::equal(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {

}

TF_Operation* MathOps::argmax(TF_Graph *graph, TF_Operation* l, int dim) {

}

TF_Operation* MathOps::cast(TF_Graph *graph, TF_Operation* v, TF_DataType dtype) {

}

TF_Operation* MathOps::log(TF_Graph *graph, TF_Operation* v) {

}

} // namespace tensorflow
