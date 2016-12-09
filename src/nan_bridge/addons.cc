#include <nan.h>
#include "graph.h"
#include "operation.h"

void Init(v8::Local<v8::Object> exports) {
  nan_bridge::Graph::Init(exports);
  nan_bridge::Operation::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
