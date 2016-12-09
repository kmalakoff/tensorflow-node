#ifndef NAN_ADDONS_H
#define NAN_ADDONS_H

#include <nan.h>

struct TF_Tensor;

namespace nan_addons {

class AddOns {
  public:
    static void Init(v8::Local<v8::Object> exports);

    static TF_Tensor* _VALUE_TO_TENSOR(const v8::Local<v8::Value>& info);

    static v8::Local<v8::Value> _TENSOR_TO_VALUE(TF_Tensor* value);
    static v8::Local<v8::Value> _TENSOR_TO_ARRAY_VALUE(const std::vector<TF_Tensor*>& value);
    static v8::Local<v8::Value> _TENSOR_TO_BUFFER_VALUE(TF_Tensor* value);

    template<typename T>
    static v8::Local<v8::Object> _WRAPPER_OBJECT_TO_VALUE(T* r) {
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(T::constructor)->GetFunction()).ToLocalChecked();
      (r)->Wrap(result);
      return result;
    }
};

} // namespace nan_addons

#define VALUE_TO_TENSOR(_i) nan_addons::AddOns::_VALUE_TO_TENSOR(_i)
#define VALUE_TO_BUFFER_DATA(_i) node::Buffer::Data(_i->ToObject())
#define VALUE_TO_BUFFER_LENGTH(_i) node::Buffer::Length(_i->ToObject())
#define VALUE_TO_WRAPPER_OBJECT(OW, _i) Nan::ObjectWrap::Unwrap<OW>(_i->ToObject())

#define TENSOR_TO_VALUE(_v) nan_addons::AddOns::_TENSOR_TO_VALUE(_v)
#define TENSOR_TO_ARRAY_VALUE(_v) nan_addons::AddOns::_TENSOR_TO_ARRAY_VALUE(_v)
#define TENSOR_TO_BUFFER_VALUE(_v) nan_addons::AddOns::_TENSOR_TO_BUFFER_VALUE(_v)
#define WRAPPER_OBJECT_TO_VALUE(_v) nan_addons::AddOns::_WRAPPER_OBJECT_TO_VALUE(_v)

#endif // NAN_ADDONS_H
