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
    static NAN_METHOD(matmul_add);
    static NAN_METHOD(reduce_mean);
    static NAN_METHOD(equal);
    static NAN_METHOD(argmax);
    static NAN_METHOD(cast);
    static NAN_METHOD(log);
};

} // namespace addons

#endif // NAN_MATH_OPS_H
