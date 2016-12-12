#include <iostream>
#include "graph.h"
#include "session.h"
#include "../tf/tensor.h"
#include "../addons/operation.h"
#include "../../lib/utils.h"
#include "../../lib/conversions.h"

namespace tf {

using namespace v8;
using namespace Nan;
using namespace addons;

TF_Graph* Graph::create() { return TF_NewGraph(); }
void Graph::destroy(TF_Graph* graph) { TF_DeleteGraph(graph); }

TF_Operation* Graph::placeholder(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Placeholder", lib::uniqueId("Placeholder").c_str());
  TF_SetAttrType(desc, "dtype", dtype);
  TF_SetAttrShape(desc, "shape", &dims[0], (int) dims.size());

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::variable(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims) {
  TF_Status* s = TF_NewStatus();
  
  TF_OperationDescription* desc = TF_NewOperation(graph, "Variable", lib::uniqueId("Variable").c_str());
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrShape(desc, "shape", &dims[0], (int) dims.size());
  TF_SetAttrType(desc, "dtype", dtype);
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
    
  return result;
}

// https://www.tensorflow.org/versions/master/how_tos/variables/index.html
TF_Operation* Graph::variableInitializer(TF_Graph *graph, TF_Operation* variable, TF_Tensor* value) {
  TF_Operation* initial_value = Graph::constant(graph, value);
  return Graph::assign(graph, variable, initial_value);
}

TF_Operation* Graph::constant(TF_Graph *graph, TF_Tensor* value) {
  TF_DataType dtype = value->dtype;

  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(graph, "Const", lib::uniqueId("Const").c_str());
  TF_SetAttrTensor(desc, "value", value, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrType(desc, "dtype", dtype);
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }

  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::assign(TF_Graph *graph, TF_Operation* var, TF_Operation* val) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Assign", lib::uniqueId("Assign").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port var_port = {var, 0};
  TF_AddInput(desc, var_port);
  TF_Port val_port = {val, 0};
  TF_AddInput(desc, val_port);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

void Graph::run(std::vector<TF_Tensor*>& o_results, TF_Graph* graph, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs) {
  TF_SessionWithGraph* session = Session::create(graph);
  tf::Session::run(o_results, session, ops, input_pairs);
  Session::destroy(session);
}

} // namespace tf
