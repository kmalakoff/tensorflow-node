#include "addons.h"
#include "graph.h"
#include "operation.h"

namespace nan {

void AddOns::Init(v8::Local<v8::Object> exports) {
  nan::Graph::Init(exports);
  nan::Operation::Init(exports);
}

NODE_MODULE(Tensorflow, AddOns::Init)

} // namespace nan
