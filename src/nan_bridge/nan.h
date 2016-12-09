#ifndef NAN_H
#define NAN_H

#define NAN_CONSTRUCTOR(c) Nan::Persistent<v8::FunctionTemplate> c
#define NAN_NEW(n) void n(const Nan::FunctionCallbackInfo<v8::Value>& info)
#define NAN_TO_VALUE(T, n) v8::Local<v8::Value> n() { \
  v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(T::constructor)->GetFunction()).ToLocalChecked(); \
  this->Wrap(result); \
  return result; \
}

#endif // NAN_H
