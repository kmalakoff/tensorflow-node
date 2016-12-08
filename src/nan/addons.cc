#include <nan.h>
#include "graph.h"
#include "operation.h"

void InitAll(v8::Local<v8::Object> exports) {
  nan::Graph::Init(exports);
  nan::Operation::Init(exports);
}

NODE_MODULE(Tensorflow, InitAll)
