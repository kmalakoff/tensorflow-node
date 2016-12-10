#include <map>
#include "session.h"
#include "../tensorflow/tensor.h"
#include "../addons/conversions.h"
#include "../addons/operation.h"

namespace tensorflow {

using namespace v8;
using namespace Nan;
using namespace addons;

Session::Session() { m_ref = nullptr; } // TF_NewSession(); }

void Session::run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs) {
  TF_Status* s = TF_NewStatus();
  TF_SessionOptions* opts = TF_NewSessionOptions();
  // TF_SessionWithSession* session = TF_NewSessionWithGraph(m_ref, opts, s);
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
    m_ref, nullptr,
    &input_ports[0], &input_tensors[0], (int) input_ports.size(),
    &output_ports[0], &o_results[0], (int) output_ports.size(),
    nullptr, 0,
    nullptr, s
  );
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }

  TF_DeleteSessionOptions(opts);
  // TF_CloseSessionWithSession(session, s);
  if (TF_OK != TF_GetCode(s)) { std::cout << TF_Message(s); }
  TF_DeleteStatus(s);
}

} // namespace tensorflow
