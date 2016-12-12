#include <map>
#include "session.h"
#include "../tf/tensor.h"
#include "../addons/operation.h"
#include "../../lib/conversions.h"

namespace tf {

using namespace v8;
using namespace Nan;
using namespace addons;

TF_SessionWithGraph* Session::create(TF_Graph* graph) {
  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  TF_SessionWithGraph* session = TF_NewSessionWithGraph(graph, opts, s);
  TF_DeleteSessionOptions(opts);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
  return session;
}

void Session::destroy(TF_SessionWithGraph* session) {
  TF_Status* s = TF_NewStatus();

  TF_CloseSessionWithGraph(session, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
}

void Session::run(std::vector<TF_Tensor*>& o_results, TF_SessionWithGraph* session, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs, bool outputs=true) {
  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;
  if (input_pairs->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(input_pairs);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      TF_Operation* in = ObjectWrap::Unwrap<addons::Operation>(pair->Get(0)->ToObject())->ref();
      TF_Tensor* va = lib::ToTensor(pair->Get(1));
      input_ports.push_back(TF_Port({in, 0}));
      input_tensors.push_back(va);
    }
  }

  std::vector<TF_Port> output_ports;

  for (std::size_t i = 0; i < ops.size(); i++) {
    if (!ops[i]) { std::cout << "Skipping run: operation is missing" << "\n"; return;}
    output_ports.push_back(TF_Port({ops[i], 0}));
    o_results.push_back(nullptr);
  }

  TF_Status* s = TF_NewStatus();
  TF_SessionRun(
    session, nullptr,
    &input_ports[0], &input_tensors[0], (int) input_ports.size(),
    &output_ports[0], &o_results[0], (int) output_ports.size(),
    nullptr, 0,
    nullptr, s
  );
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
}

void Session::runNoOut(TF_SessionWithGraph* session, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs) {
  std::vector<TF_Port> input_ports;
  std::vector<TF_Tensor*> input_tensors;
  if (input_pairs->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(input_pairs);
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
      Handle<Array> pair = Handle<Array>::Cast(jsArray->Get(i));

      TF_Operation* in = ObjectWrap::Unwrap<addons::Operation>(pair->Get(0)->ToObject())->ref();
      TF_Tensor* va = lib::ToTensor(pair->Get(1));
      input_ports.push_back(TF_Port({in, static_cast<int>(i)}));
      input_tensors.push_back(va);
    }
  }

  for (std::size_t i = 0; i < ops.size(); i++) {
    if (!ops[i]) { std::cout << "Skipping run: operation is missing" << "\n"; return;}
  }

  TF_Status* s = TF_NewStatus();
  TF_SessionRun(
    session, nullptr,
    &input_ports[0], &input_tensors[0], (int) input_ports.size(),
    nullptr, nullptr, 0,
    &ops[0], (int) ops.size(),
    nullptr, s
  );
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s) << "\n"; }
  TF_DeleteStatus(s);
}

} // namespace tf
