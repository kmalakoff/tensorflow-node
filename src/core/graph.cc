#include <map>
#include "graph.h"
#include "../tensorflow/tensor.h"
#include "../addons/conversions.h"
#include "../addons/operation.h"

// TODO: move to lib
std::map<tensorflow::string, int> unique_ids;
tensorflow::string uniqueId(const char* key) {
  std::map<tensorflow::string, int>::iterator it = unique_ids.find(key);
  if (it == unique_ids.end()) unique_ids[key] = 0;
  return tensorflow::string(key + unique_ids[key]++);
}

namespace tensorflow {

using namespace v8;
using namespace Nan;
using namespace addons;

Graph::Graph() { m_ref = TF_NewGraph(); }

TF_Operation* Graph::placeholder(TF_DataType dtype, const std::vector<int64_t>& dims) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "Placeholder", uniqueId("Placeholder").c_str());
  TF_SetAttrType(desc, "dtype", dtype);
  TF_SetAttrShape(desc, "shape", &dims[0], (int) dims.size());

  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::constant(TF_Tensor* value) {
  TF_DataType dtype = value->dtype;

  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "Const", uniqueId("Const").c_str());
  TF_SetAttrTensor(desc, "value", value, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrType(desc, "dtype", dtype);
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  TF_DeleteStatus(s);
  return result;
}

TF_Operation* Graph::variable(TF_Tensor* value, const std::vector<int64_t>& dims) {
  TF_DataType dtype = value->dtype;

  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "Variable", uniqueId("Variable").c_str());
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  if (TF_GetCode(s) != TF_OK) return nullptr; // TODO: general error handling
  TF_SetAttrShape(desc, "shape", &dims[0], (int) dims.size());
  TF_SetAttrType(desc, "dtype", dtype);
  TF_Operation* result = TF_FinishOperation(desc, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);

  // https://www.tensorflow.org/versions/master/how_tos/variables/index.html
  TF_Operation* initial_value = this->constant(value);
  TF_Operation* initializer = this->assign(result, initial_value);
  m_initializers.push_back(initializer);

  return result;
}

TF_Operation* Graph::add(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "Add", uniqueId("Add").c_str());
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

TF_Operation* Graph::assign(TF_Operation* l, TF_Operation* r) {
  TF_Status* s = TF_NewStatus();

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "Assign", uniqueId("Assign").c_str());
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

  TF_OperationDescription* desc = TF_NewOperation(m_ref, "MatMul", uniqueId("MatMul").c_str());

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
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(m_ref, opts, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;
  if (input_pairs->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(input_pairs);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      TF_Operation* in = ObjectWrap::Unwrap<addons::Operation>(pair->Get(0)->ToObject())->ref();
      TF_Tensor* va = ToTensor(pair->Get(1));
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
    &input_ports[0], &input_tensors[0], (int) input_ports.size(),
    &output_ports[0], &o_results[0], (int) output_ports.size(),
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
