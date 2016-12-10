#include <nan.h>
#include "constants.h"
#include "graph.h"
#include "operation.h"
#include "session.h"
#include "types.h"

void Init(v8::Local<v8::Object> exports) {
  addons::CONSTANTS::Init(exports);
  addons::Graph::Init(exports);
  addons::Operation::Init(exports);
  addons::Session::Init(exports);
  addons::TYPES::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
