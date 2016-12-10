#ifndef NAN_NEURAL_NETWORK_H
#define NAN_NEURAL_NETWORK_H

#include "addons.h"

namespace addons {

class NeuralNetwork: public Nan::ObjectWrap {
  public:

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_METHOD(softmax);
};

} // namespace addons

#endif // NAN_NEURAL_NETWORK_H
