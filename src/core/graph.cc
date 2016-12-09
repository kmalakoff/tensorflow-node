#include <iostream>
#include "tensorflow/core/platform/types.h"
#include "tensorflow/c/c_api.h"
#include "graph.h"
#include <nan.h> // remove dependency
#include "../nan_addons/addons.h"
#include "../nan_addons/operation.h"

namespace tensorflow {

using namespace v8;

void gen_random(char *s, const int len) {
  for (int i = 0; i < len; ++i) {
    int randomChar = rand()%(26+26+10);
    if (randomChar < 26)
      s[i] = 'a' + randomChar;
    else if (randomChar < 26+26)
      s[i] = 'A' + randomChar - 26;
    else
      s[i] = '0' + randomChar - 26 - 26;
  }
  s[len] = 0;
}

Graph::Graph() { m_graph = TF_NewGraph(); }

TF_Operation* Graph::input() {
  TF_Status* s = TF_NewStatus();

  char name[10]; gen_random(name, 4); name[4] = '\0';
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Placeholder", name);
  TF_SetAttrType(desc, "dtype", TF_FLOAT);

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::constant(TF_Tensor* value) {
  TF_DataType dtype = value->dtype;

  TF_Status* s = TF_NewStatus();

  char name[10]; gen_random(name, 4); name[4] = '\0';
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Const", name);
  TF_SetAttrTensor(desc, "value", value, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrType(desc, "dtype", dtype);
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::add(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  char name[10]; gen_random(name, 4); name[4] = '\0';
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "Add", name);
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

TF_Operation* Graph::matmul(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  char name[10]; gen_random(name, 4); name[4] = '\0';
  TF_OperationDescription* desc = TF_NewOperation(m_graph, "MatMul", name);

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

void Graph::run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs) {
  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(m_graph, opts, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;
  if (input_pairs->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(input_pairs);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      TF_Operation* in = VALUE_TO_WRAPPER_OBJECT(nan_addons::Operation, pair->Get(0))->ref();
      TF_Tensor* va = VALUE_TO_TENSOR(pair->Get(1));
      input_ports.push_back(TF_Port({in, static_cast<int>(i)}));
      input_tensors.push_back(va);
    }
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
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  TF_DeleteSessionOptions(opts);
  TF_CloseSessionWithGraph(session, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
}

} // namespace tensorflow
