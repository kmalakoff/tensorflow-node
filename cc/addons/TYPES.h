#ifndef NAN_TYPES_H
#define NAN_TYPES_H

#include "nan.h"

namespace addons {

class TYPES: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
};

}

#endif // NAN_TYPES_H
