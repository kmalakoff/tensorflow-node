#include <iostream>
#include "tensorflow/core/platform/types.h"
#include "tensorflow/c/c_api.h"
#include "graph.h"
#include <nan.h> // remove dependency

namespace tensorflow {

using namespace v8;

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

Graph::Graph() { m_graph = TF_NewGraph(); }

TF_Operation* Graph::constant(TF_Tensor* value) {
  TF_DataType dtype = value->dtype;
  // std::cout << "TYPE";
  // std::cout << value->dtype;
  // std::cout << dtype;
  // std::cout << "\n";

  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Const", "const");
  TF_SetAttrTensor(desc, "value", value, s);

  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrType(desc, "dtype", dtype);

  // std::cout << "TYPE";
  // std::cout << value->dtype;
  // std::cout << dtype;
  // std::cout << "\n";

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::matmul(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "MatMul", "matmul");
  TF_Port inputs[2] = {{l, 0}, {r, 0}};
  TF_AddInputList(desc, inputs, 2);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

void Graph::run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, v8::Handle<v8::Object>& inputs) {
  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(m_graph, opts, s);

  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;

  // for (std::size_t i = 0; i < this->m_inputs.size(); i++) {
  //   input_ports.push_back(TF_Port({this->m_inputs[i], i}));
  //   input_tensors.push_back(Int32Tensor(inputs->Get(Nan::New("input").ToLocalChecked())->NumberValue()));
  // }

  std::vector<TF_Port> output_ports;

  std::cout << "HERE";
  std::cout << ops.size();
  std::cout << ops[0];

  for (std::size_t i = 0; i < ops.size(); i++) {
    output_ports.push_back(TF_Port({ops[i], static_cast<int>(i)}));
    o_results.push_back(nullptr);
  }

  std::cout << output_ports.size();

  TF_SessionRun(
    session, nullptr,
    nullptr, nullptr, 0,
    &output_ports[0], &o_results[0], output_ports.size(),
    nullptr, 0,
    nullptr, s
  );

  TF_DeleteSessionOptions(opts);
  TF_CloseSessionWithGraph(session, s);
  TF_DeleteStatus(s);
}

TF_Operation* Graph::Placeholder() {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Placeholder", "feed");
  TF_SetAttrType(desc, "dtype", TF_INT32);

  TF_Operation* result = TF_FinishOperation(desc, s);
  this->m_inputs.push_back(result);
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::ScalarConst(int v) {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Const", "scalar");
  TF_SetAttrTensor(desc, "value", Int32Tensor(v), s);
  if (TF_GetCode(s) != TF_OK) return nullptr;
  TF_SetAttrType(desc, "dtype", TF_INT32);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::Add(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "AddN", "add");
  TF_Port add_inputs[2] = {{l, 0}, {r, 0}};
  TF_AddInputList(desc, add_inputs, 2);

  TF_Operation* result = TF_FinishOperation(desc, s);
  TF_DeleteStatus(s);
  return result;
}

void Graph::Run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, v8::Handle<v8::Object>& inputs) {
  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(m_graph, opts, s);

  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;

  for (std::size_t i = 0; i < this->m_inputs.size(); i++) {
    input_ports.push_back(TF_Port({this->m_inputs[i], static_cast<int>(i)}));
    input_tensors.push_back(Int32Tensor(inputs->Get(Nan::New("input").ToLocalChecked())->NumberValue()));
  }

  std::vector<TF_Port> output_ports;

  for (std::size_t i = 0; i < ops.size(); i++) {
    output_ports.push_back(TF_Port({ops[i], static_cast<int>(i)}));
    o_results.push_back(nullptr);
  }

  TF_SessionRun(
    session, nullptr,
    &input_ports[0], &input_tensors[0], input_ports.size(),
    &output_ports[0], &o_results[0], output_ports.size(),
    nullptr, 0,
    nullptr, s
  );

  TF_DeleteSessionOptions(opts);
  TF_CloseSessionWithGraph(session, s);
  TF_DeleteStatus(s);
}

} // namespace tensorflow
