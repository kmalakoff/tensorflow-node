#include "addons.h"
#include "graph.h"
#include "operation.h"

namespace nan {

using namespace v8;

void AddOns::Init(Local<Object> exports) {
  nan::Graph::Init(exports);
  nan::Operation::Init(exports);
}

NODE_MODULE(Tensorflow, AddOns::Init)

} // namespace nan
