#include <nan.h>
#include "graph_wrapper.h"
#include "operation_wrapper.h"

void InitAll(v8::Local<v8::Object> exports) {
  GraphWrapper::Init(exports);
  OperationWrapper::Init(exports);
}

NODE_MODULE(Tensorflow, InitAll)
