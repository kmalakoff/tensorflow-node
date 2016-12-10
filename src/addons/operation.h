#ifndef NAN_OPERATION_H
#define NAN_OPERATION_H

#include "addons.h"

// forward declarations
struct TF_Operation;

namespace addons {

class Operation: public Nan::ObjectWrap {
  public:
    Operation(TF_Operation* operation);
    ~Operation();

    NAN_TO_VALUE(Operation, ToValue);
    TF_Operation* ref() { return m_ref; }

  private:
    TF_Operation* m_ref;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
};

} // namespace addons

#endif // NAN_OPERATION_H
