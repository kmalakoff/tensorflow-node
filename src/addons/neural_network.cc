#include "neural_network.h"

namespace addons {

using namespace v8;

NAN_METHOD(NeuralNetwork::softmax) {

}

NAN_MODULE_INIT(NeuralNetwork::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "softmax", softmax);

  target->Set(Nan::New("nn").ToLocalChecked(), obj);
};

} // namespace addons
