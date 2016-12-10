#include <nan.h>
#include "CONSTANTS.h"
#include "Graph.h"
#include "MathOps.h"
#include "NeuralNetwork.h"
#include "Operation.h"
#include "Session.h"
#include "Train.h"
#include "TYPES.h"

void Init(v8::Local<v8::Object> exports) {
  addons::CONSTANTS::Init(exports);
  addons::Graph::Init(exports);
  addons::MathOps::Init(exports);
  addons::NeuralNetwork::Init(exports);
  addons::Operation::Init(exports);
  addons::Session::Init(exports);
  addons::Train::Init(exports);
  addons::TYPES::Init(exports);
}

NODE_MODULE(Tensorflow, Init)
