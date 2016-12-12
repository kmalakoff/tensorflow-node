#ifndef LIB_CONVERSIONS_H
#define LIB_CONVERSIONS_H

#include <nan.h>
#include "tensorflow/c/c_api.h"
#include "tensorflow/core/framework/tensor.h"

struct TF_Tensor;

namespace lib {

using namespace v8;

void Deallocator(void* data, size_t, void* arg);
void jsCollectDimensions(std::vector<int64_t>& o_dims, Handle<Array> jsArray);
int jsCollectValues(float* o_values, Handle<Array> jsArray, int index);

TF_Tensor* ToTensor(const Local<Value>& info);
tensorflow::Tensor* ToTensor2(const Local<Value>& info);
TF_Tensor* ToTensor(int value);
tensorflow::Tensor* ToTensor2(int value);
TF_Tensor* ToTensor(float value);
tensorflow::Tensor* ToTensor2(float value);
void ToShape(std::vector<int64_t>& o_dims, TF_Tensor* value);
void ToShape(std::vector<int64_t>& o_dims, const tensorflow::Tensor& value);
void ToShape(std::vector<int64_t>& o_dims, const Local<Value>& info);
v8::Local<v8::Value> ToValue(TF_Tensor* value);
v8::Local<v8::Value> ToArrayValue(const std::vector<TF_Tensor*>& value);
v8::Local<v8::Value> ToValue(const tensorflow::Tensor& value);
v8::Local<v8::Value> ToArrayValue(const std::vector<tensorflow::Tensor>& value);
v8::Local<v8::Value> ToBufferValue(TF_Tensor* value);

} // namespace lib

#endif // LIB_CONVERSIONS_H
