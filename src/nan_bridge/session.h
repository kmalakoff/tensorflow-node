#ifndef NAN_SESSION_H
#define NAN_SESSION_H

#include "nan.h"

// forward declarations
struct TF_Session;

namespace nan_bridge {

class Session: public Nan::ObjectWrap {
  public:
    Session(TF_Session* session = nullptr);
    ~Session();

    NAN_TO_VALUE(Session, ToValue);
    TF_Session* ref() { return m_ref; }

  private:
    TF_Session* m_ref;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
};

} // namespace nan_bridge

#endif // NAN_SESSION_H
