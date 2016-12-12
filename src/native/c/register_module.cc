#include <nan.h>
#include "addons/constants.h"
#include "addons/graph.h"
#include "addons/math_ops.h"
#include "addons/neural_network.h"
#include "addons/operation.h"
#include "addons/session.h"
#include "addons/test.h"
#include "addons/train.h"
#include "addons/types.h"

void Init(v8::Local<v8::Object> exports) {
  addons::Constants::Init(exports);
  addons::Graph::Init(exports);
  addons::MathOps::Init(exports);
  addons::NeuralNetwork::Init(exports);
  addons::Operation::Init(exports);
  addons::Session::Init(exports);
  addons::Test::Init(exports);
  addons::Train::Init(exports);
  addons::Types::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
