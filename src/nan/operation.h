#ifndef NAN_OPERATION_H
#define NAN_OPERATION_H

#include <nan.h>
#include "tensorflow/c/c_api.h"

namespace nan {

class Operation: public Nan::ObjectWrap {
  public:
    Operation(TF_Operation* operation = nullptr);
    TF_Operation* ref() { return m_operation; }

  private:
    friend class AddOns;

    TF_Operation* m_operation;
   
    /////////////////////////////////
    // Nan Lifecycle
    /////////////////////////////////
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static NAN_MODULE_INIT(Init);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
};

} // namespace nan

#endif // NAN_OPERATION_H
