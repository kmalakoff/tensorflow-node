#ifndef NAN_CONSTANTS_H
#define NAN_CONSTANTS_H

#include "nan.h"

namespace addons {

class CONSTANTS: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
};

}

#endif // NAN_CONSTANTS_H
