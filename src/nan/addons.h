#ifndef NAN_ADDONS_H
#define NAN_ADDONS_H

#include <nan.h>

namespace nan {

class AddOns {
  public:
    template<typename OW, typename T>
    static v8::Local<v8::Object> _nan_wrap_result(T r) {
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(OW::constructor)->GetFunction()).ToLocalChecked();
      (new OW(r))->Wrap(result);
      return result;
    }

    static void Init(v8::Local<v8::Object> exports);
};

} // namespace nan

#endif // NAN_ADDONS_H
