#ifndef NAN_MATH_OPS_H
#define NAN_MATH_OPS_H

#include "index.h"

namespace addons {

class MathOps: public Nan::ObjectWrap {
  public:

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_METHOD(add);
    static NAN_METHOD(matmul);
};

} // namespace addons

#endif // NAN_MATH_OPS_H
