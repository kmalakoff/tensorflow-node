#include <iostream>
#include "tf_ops.h"
#include "tf_tensor.h"
#include "../lib/utils.h"
#include "../lib/conversions.h"

namespace tf {
namespace ops {

//////////////////////////////////////////////
// Graph
//////////////////////////////////////////////
TF_Operation* Placeholder(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Placeholder", lib::uniqueId("Placeholder").c_str());
  TF_SetAttrType(desc, "dtype", dtype);
  TF_SetAttrShape(desc, "shape", &dims[0], (int) dims.size());

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Variable(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims) {
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

//////////////////////////////////////////////
// Math
//////////////////////////////////////////////

// TODO: move to conversions
void Deallocator(void* data, size_t size, void* arg) { tensorflow::cpu_allocator()->DeallocateRaw(data); }

TF_Operation* Const(TF_Graph *graph, TF_Tensor* value) {
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

TF_Operation* Assign(TF_Graph *graph, TF_Operation* var, TF_Operation* val) {
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

TF_Operation* Add(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Add", lib::uniqueId("Add").c_str());
  // TF_SetAttrType(desc, "T", dtype);
  TF_Port l_input = {l, 0};
  TF_AddInput(desc, l_input);
  TF_Port r_input = {r, 0};
  TF_AddInput(desc, r_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* MatMul(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {
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
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Equal(TF_Graph *graph, TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  // TODO: use for shape checking
  // TF_Buffer* buffer = TF_NewBuffer();
  // tf::NodeDef node_def;
  // TF_OperationToNodeDef(r, buffer, s);
  // if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  // node_def.ParseFromArray(buffer->data, buffer->length);
  // TF_DeleteBuffer(buffer);

  // TF_DataType dtype = TF_FLOAT; // TODO: handle not found
  // for (const auto& attr : node_def.attr()) {
  //   if (attr.first == "dtype") {
  //     dtype = (TF_DataType) attr.second.type();
  //     break;
  //   }
  // }

  TF_OperationDescription* desc = TF_NewOperation(graph, "Equal", lib::uniqueId("Equal").c_str());
  TF_Port l_input = {l, 0};
  TF_AddInput(desc, l_input);
  TF_Port r_input = {r, 0};
  TF_AddInput(desc, r_input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* ArgMax(TF_Graph *graph, TF_Operation* v, int dim) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "ArgMax", lib::uniqueId("ArgMax").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port input = {v, 0};
  TF_AddInput(desc, input);

  // dimension
  const int byte_count = 1 * sizeof(int);
  int* values = reinterpret_cast<int*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, byte_count));
  values[0] = dim;
  // std::cout << "dim" << dim << byte_count << values[0] << "\n";
  TF_Tensor* reduction_indices = TF_NewTensor(TF_INT32, nullptr, 0, values, byte_count, &Deallocator, nullptr);
  TF_Operation* op = Const(graph, reduction_indices);
  TF_Port input_dim = {op, 0};
  TF_AddInput(desc, input_dim);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Cast(TF_Graph *graph, TF_Operation* v, TF_DataType dtype) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Cast", lib::uniqueId("Cast").c_str());
  TF_Port input = {v, 0};
  TF_AddInput(desc, input);
  TF_SetAttrType(desc, "DstT", dtype);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* ReduceMean(TF_Graph *graph, TF_Operation* v, TF_Operation* reduction_indices) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Mean", lib::uniqueId("ReduceMean").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port input = {v, 0};
  TF_AddInput(desc, input);

  // reduction_indices
  TF_Port input_ri = {reduction_indices, 0};
  TF_AddInput(desc, input_ri);

  // keep_dims
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Log(TF_Graph *graph, TF_Operation* v) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "Log", lib::uniqueId("Log").c_str());
  TF_SetAttrType(desc, "T", TF_FLOAT);
  TF_Port input = {v, 0};
  TF_AddInput(desc, input);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

//////////////////////////////////////////////
// Neural Network
//////////////////////////////////////////////
TF_Operation* Softmax(TF_Graph *graph, TF_Operation* v) {
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

TF_Operation* SoftmaxCrossEntropyWithLogits(TF_Graph *graph, TF_Operation* y, TF_Operation* y_) {
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

//////////////////////////////////////////////
// Train
//////////////////////////////////////////////
TF_Operation* GradientDescentOptimizer(TF_Graph *graph, float learning_rate, TF_Operation* v) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(graph, "ApplyGradientDescent", lib::uniqueId("ApplyGradientDescent").c_str());

  TF_Port input_var = {v, 0};
  TF_AddInput(desc, input_var);
  TF_Port input_alpha = {Const(graph, lib::ToTensor(learning_rate)), 0};
  TF_AddInput(desc, input_alpha);
  TF_Port input_delta = {Const(graph, lib::ToTensor(100.0f)), 0};
  TF_AddInput(desc, input_delta);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return result;
}

} // namespace ops
} // namespace tf
