#ifndef NAN_OPERATION_H
#define NAN_OPERATION_H

#include "nan.h"

// forward declarations
struct TF_Operation;

namespace nan_addons {

class Operation: public Nan::ObjectWrap {
  public:
    Operation(TF_Operation* operation = nullptr);
    ~Operation();

    NAN_TO_VALUE(Operation, ToValue);
    TF_Operation* ref() { return m_operation; }

  private:
    TF_Operation* m_operation;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
};

} // namespace nan_addons

#endif // NAN_OPERATION_H
