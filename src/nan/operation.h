#ifndef NAN_OPERATION_H
#define NAN_OPERATION_H

#include "nan.h"

// forward declarations
struct TF_Operation;

namespace nan {

class Operation: public Nan::ObjectWrap {
  public:
    Operation(TF_Operation* operation = nullptr);
    TF_Operation* ref() { return m_operation; }

  private:
    TF_Operation* m_operation;
   
    /////////////////////////////////
    // Nan Lifecycle
    /////////////////////////////////
    friend class AddOns;
    static NAN_CONSTRUCTOR(constructor);
    static NAN_MODULE_INIT(Init);
    static NAN_NEW(New);
};

} // namespace nan

#endif // NAN_OPERATION_H
