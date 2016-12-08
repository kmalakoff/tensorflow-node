#include <nan.h>
#include "graph.h"
#include "operation.h"

namespace nan {

class AddOns {
  public:
    static void Init(v8::Local<v8::Object> exports) {
      nan::Graph::Init(exports);
      nan::Operation::Init(exports);
    }
};

NODE_MODULE(Tensorflow, AddOns::Init)

} // namespace nan
