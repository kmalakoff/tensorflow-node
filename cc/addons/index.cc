#include <nan.h>
#include "constants.h"
#include "graph.h"
#include "math_ops.h"
#include "neural_network.h"
#include "operation.h"
#include "session.h"
#include "train.h"
#include "types.h"

void Init(v8::Local<v8::Object> exports) {
  addons::Constants::Init(exports);
  addons::Graph::Init(exports);
  addons::MathOps::Init(exports);
  addons::NeuralNetwork::Init(exports);
  addons::Operation::Init(exports);
  addons::Session::Init(exports);
  addons::Train::Init(exports);
  addons::Types::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
