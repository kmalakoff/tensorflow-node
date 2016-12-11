#ifndef NAN_TRAIN_H
#define NAN_TRAIN_H

#include "index.h"

namespace addons {

class Train: public Nan::ObjectWrap {
  public:

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_METHOD(GradientDescentOptimizer);
};

} // namespace addons

#endif // NAN_TRAIN_H
