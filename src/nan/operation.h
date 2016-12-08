#ifndef NAN_OPERATION_H
#define NAN_OPERATION_H

#include <nan.h>
#include "tensorflow/c/c_api.h"

namespace nan {

class Operation: public Nan::ObjectWrap {
  public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

    Operation(TF_Operation* operation = nullptr);
    TF_Operation* m_operation;

    void DoWrap(v8::MaybeLocal<v8::Object>& n);
};

} // namespace nan

#endif // NAN_OPERATION_H
