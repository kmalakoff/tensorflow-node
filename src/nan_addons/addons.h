#ifndef NAN_ADDONS_H
#define NAN_ADDONS_H

#include <nan.h>

struct TF_Tensor;

namespace nan_addons {

class AddOns {
  public:
    static void Init(v8::Local<v8::Object> exports);

    static TF_Tensor* _NAN_IN_TO_TENSOR(const v8::Local<v8::Value>& info);
    static v8::Local<v8::Value> _NAN_OUT_TO_BUFFER(TF_Tensor* value);

    template<typename OW, typename T>
    static v8::Local<v8::Object> _NAN_OUT_WRAP_OBJECT(T r) {
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(OW::constructor)->GetFunction()).ToLocalChecked();
      (new OW(r))->Wrap(result);
      return result;
    }
};

} // namespace nan_addons

#define NAN_IN_TO_TENSOR(_i) nan_addons::AddOns::_NAN_IN_TO_TENSOR(_i)
#define NAN_IN_BUFFER_DATA(_i) node::Buffer::Data(_i->ToObject())
#define NAN_IN_BUFFER_LENGTH(_i) node::Buffer::Length(_i->ToObject())
#define NAN_IN_WRAP_OBJECT(OW, _i) Nan::ObjectWrap::Unwrap<OW>(_i->ToObject())

#define NAN_OUT_TO_BUFFER(_v) nan_addons::AddOns::_NAN_OUT_TO_BUFFER(_v)
#define NAN_OUT_WRAP_OBJECT(OW, T, _v) nan_addons::AddOns::_NAN_OUT_WRAP_OBJECT<OW, T>(_v)

#endif // NAN_ADDONS_H
