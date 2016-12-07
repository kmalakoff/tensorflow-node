#ifndef OperationWrapper_H
#define OperationWrapper_H

#include <nan.h>
#include "tensorflow/c/c_api.h"

class OperationWrapper: public Nan::ObjectWrap {
  public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> info);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

    OperationWrapper(TF_Operation* operation = nullptr);
    TF_Operation* m_operation;

    void DoWrap(v8::Local<v8::Object> n);
};

#endif // OperationWrapper_H
