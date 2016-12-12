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

} // namespace tf
