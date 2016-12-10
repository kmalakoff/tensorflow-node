#include "conversions.h"
#include "tensorflow/c/c_api.h"
#include "tensorflow/core/framework/tensor.h"

namespace lib {

using namespace v8;
using namespace tensorflow;

void Deallocator(void* data, size_t, void* arg) { tensorflow::cpu_allocator()->DeallocateRaw(data); }

void jsCollectDimensions(std::vector<int64_t>& o_dims, Handle<Array> jsArray) {
  o_dims.push_back(jsArray->Length());
  if (jsArray->Get(0)->IsArray()) jsCollectDimensions(o_dims, Handle<Array>::Cast(jsArray->Get(0)));
}

int jsCollectValues(float* o_values, Handle<Array> jsArray, int index) {
  for (uint32_t i = 0; i < jsArray->Length(); i++) {
    if (jsArray->Get(i)->IsArray()) index = jsCollectValues(o_values, Handle<Array>::Cast(jsArray->Get(i)), index);
    else {
      o_values[index] = jsArray->Get(i)->NumberValue();
      index++;
    }
  }
  return index;
}

TF_Tensor* ToTensor(const Local<Value>& info) {
  if (info->IsNumber()) {
    const int byte_count = 1 * sizeof(float);
    float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, byte_count));
    values[0] = info->NumberValue();
    return TF_NewTensor(TF_FLOAT, nullptr, 0, values, byte_count, &Deallocator, nullptr);
  }
  else if (info->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info);
    std::vector<int64_t> dims;
    jsCollectDimensions(dims, jsArray);

    const int byte_count = (int) std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<int64_t>()) * sizeof(float);
    float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, byte_count));
    jsCollectValues(values, jsArray, 0);

    return TF_NewTensor(TF_FLOAT, &dims[0], (int) dims.size(), values, byte_count, &Deallocator, nullptr);
  }

  return nullptr;
}

void ToShape(std::vector<int64_t>& o_dims, const Local<Value>& info) { jsCollectDimensions(o_dims, Handle<Array>::Cast(info)); }

Local<Value> tfCollectValues(TF_Tensor* value, std::vector<int64_t>& dims, int dim_index, size_t& offset) {
  int dim_count = (int) dims.size();
  if (dim_index >= dim_count) return Nan::Undefined();
  int64_t dim = TF_Dim(value, dim_index);
  Local<Array> results = Nan::New<v8::Array>((int) dim);
  for (int64_t i = 0; i < dim; i++) {
    if (dim_index == dim_count - 1) {
      results->Set((int) i, Nan::New(*((float*) TF_TensorData(value) + offset)));
      offset++;
    }
    else results->Set((int) i, tfCollectValues(value, dims, dim_index + 1, offset));
  }
  return results;
}

Local<Value> ToValue(TF_Tensor* value) {
  size_t dim_count = TF_NumDims(value);
  if (dim_count == 0) return Nan::New(*((float*) TF_TensorData(value))); // TF_TensorType(results[i]) == DT_Float32 // TODO: check type

  std::vector<int64_t> dims;
  for (size_t i = 0; i < dim_count; i++) dims.push_back(TF_Dim(value, (int) i));

  size_t offset = 0;
  return tfCollectValues(value, dims, 0, offset);
}

Local<Value> ToArrayValue(const std::vector<TF_Tensor*>& value) {
  Local<Array> results = Nan::New<v8::Array>((int) value.size());
  for (size_t i = 0; i < value.size(); i++) results->Set((int) i, ToValue(value[i]));
  return results;
}

Local<Value> ToBufferValue(TF_Tensor* value) {
  Local<Object> buf = Nan::NewBuffer((uint32_t) TF_TensorByteSize(value)).ToLocalChecked();
  uint8* data = (uint8*) node::Buffer::Data(buf);
  memcpy(data, TF_TensorData(value), TF_TensorByteSize(value));

  Local<v8::Object> globalObj = Nan::GetCurrentContext()->Global();
  Local<v8::Function> bufferConstructor = Local<v8::Function> ::Cast(globalObj->Get(Nan::New<String>("Buffer").ToLocalChecked()));
  Local<Value> constructorArgs[3] = {buf, Nan::New<v8::Integer>((int)TF_TensorByteSize(value)), Nan::New<v8::Integer>(0)};
  return Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();
}

} // namespace lib

// IN_TO_BUFFER
// char* buf = node::Buffer::Data(info[0]->ToObject());
// size_t len = node::Buffer::Length(info[0]->ToObject());
// int arg0 = *((int32*) buf);
