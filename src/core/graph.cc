#include <iostream>
#include "graph.h"

using tensorflow::int32;
static void Int32Deallocator(void* data, size_t, void* arg) {
  delete[] static_cast<int32*>(data);
}

static TF_Tensor* Int32Tensor(int32 v) {
  const int num_bytes = sizeof(int32);
  int32* values = new int32[1];
  values[0] = v;
  return TF_NewTensor(TF_INT32, nullptr, 0, values, num_bytes, &Int32Deallocator, nullptr);
}

Graph::Graph() { graph = TF_NewGraph(); }
  
TF_Operation* Graph::Placeholder() {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(graph, "Placeholder", "feed");
  TF_SetAttrType(desc, "dtype", TF_INT32);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::ScalarConst(int v) {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(graph, "Const", "scalar");
  TF_SetAttrTensor(desc, "value", Int32Tensor(v), s);
  if (TF_GetCode(s) != TF_OK) return nullptr;
  TF_SetAttrType(desc, "dtype", TF_INT32);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::Add(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(graph, "AddN", "add");
  TF_Port add_inputs[2] = {{l, 0}, {r, 0}};
  TF_AddInputList(desc, add_inputs, 2);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

int Graph::Run(TF_Operation* op1, TF_Operation* op2) {
  int result = 0;

  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(graph, opts, s);

  std::vector<TF_Port> input_ports;
  input_ports.push_back(TF_Port({op1, 0}));
  std::vector<TF_Tensor*> input_tensors;
  input_tensors.push_back(Int32Tensor(3));

  std::vector<TF_Port> output_ports;
  output_ports.push_back(TF_Port({op2, 0}));
  std::vector<TF_Tensor*> output_tensors;
  output_tensors.push_back(nullptr);

  TF_SessionRun(
    session, nullptr,
    &input_ports[0], &input_tensors[0], input_ports.size(),
    &output_ports[0], &output_tensors[0], output_ports.size(),
    nullptr, 0,
    nullptr, s
  );

  TF_Tensor* out = output_tensors[0];
  int32* output_contents = static_cast<int32*>(TF_TensorData(out));

  result = *output_contents;

  TF_DeleteSessionOptions(opts);
  TF_CloseSessionWithGraph(session, s);
  TF_DeleteStatus(s);

  return result;
}
