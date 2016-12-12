#ifndef NAN_TEST_H
#define NAN_TEST_H

#include "index.h"

namespace addons {

class Test: public Nan::ObjectWrap {
  public:
    Test();
    ~Test();

    v8::Local<v8::Value> ToValue() {
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Test::constructor)->GetFunction()).ToLocalChecked();
      this->Wrap(result);
      return result;
    }

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(run);
};

} // namespace addons

#endif // NAN_TEST_H
