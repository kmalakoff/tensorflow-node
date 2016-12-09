#ifndef NAN_CONVERSIONS_H
#define NAN_CONVERSIONS_H

#include <nan.h>

struct TF_Tensor;

namespace nan_bridge {

TF_Tensor* VALUE_TO_TENSOR(const v8::Local<v8::Value>& info);
#define VALUE_TO_BUFFER_DATA(_i) node::Buffer::Data(_i->ToObject())
#define VALUE_TO_BUFFER_LENGTH(_i) node::Buffer::Length(_i->ToObject())

v8::Local<v8::Value> TENSOR_TO_VALUE(TF_Tensor* value);
v8::Local<v8::Value> TENSOR_TO_ARRAY_VALUE(const std::vector<TF_Tensor*>& value);
v8::Local<v8::Value> TENSOR_TO_BUFFER_VALUE(TF_Tensor* value);

} // namespace nan_bridge

#endif // NAN_CONVERSIONS_H
