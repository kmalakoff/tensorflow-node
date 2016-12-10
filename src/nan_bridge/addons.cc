#include <nan.h>
#include "constants.h"
#include "graph.h"
#include "operation.h"
#include "session.h"
#include "types.h"

void Init(v8::Local<v8::Object> exports) {
  nan_bridge::CONSTANTS::Init(exports);
  nan_bridge::Graph::Init(exports);
  nan_bridge::Operation::Init(exports);
  nan_bridge::Session::Init(exports);
  nan_bridge::TYPES::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
