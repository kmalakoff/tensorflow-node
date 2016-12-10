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
    TF_Operation* ref() { return m_ref; }

    v8::Local<v8::Value> ToValue() {
      // const int argc = 1;
      // v8::Local<v8::Value> argv[argc] = {Nan::New<v8::Object>(this)};
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Operation::constructor)->GetFunction()).ToLocalChecked();
      this->Wrap(result);
      return result;
    }

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
