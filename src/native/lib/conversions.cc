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
      o_values[index] = (float) jsArray->Get(i)->NumberValue();
      index++;
    }
  }
  return index;
}

struct TensorData {
  TF_DataType dtype;
  std::vector<int64_t> dims;
  int byte_count;
};

bool ToTensorData(TensorData& o_data, const Local<Value>& info) {
  if (!(info->IsNumber() || info->IsArray())) { Nan::ThrowError(Nan::TypeError("Expecting Number or Array of Numbers")); return false; }

  if (info->IsNumber()) {
    o_data.dtype = TF_FLOAT; // TODO: implement flexible types
    o_data.byte_count = 1 * sizeof(float);
    return true;
  }
  else if (info->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info);
    
    jsCollectDimensions(o_data.dims, jsArray);

    o_data.dtype = TF_FLOAT; // TODO: implement flexible types
    o_data.byte_count = (int) std::accumulate(o_data.dims.begin(), o_data.dims.end(), 1, std::multiplies<int64_t>()) * sizeof(float);
    return true;
  }

  return false;
}

TF_Tensor* ToTensor(const Local<Value>& info) {
  TensorData data;
  if (!ToTensorData(data, info)) return nullptr;

  float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, data.byte_count));
  if (info->IsNumber())
    values[0] = info->NumberValue();
  else
    jsCollectValues(values, Handle<Array>::Cast(info), 0);

  if (data.dims.size() == 0) return TF_NewTensor(data.dtype, nullptr, 0, values, data.byte_count, &Deallocator, nullptr);
  return TF_NewTensor(data.dtype, &data.dims[0], (int) data.dims.size(), values, data.byte_count, &Deallocator, nullptr);
}

tensorflow::Tensor* ToTensor2(const Local<Value>& info) {
  TensorData data;
  if (!ToTensorData(data, info)) return nullptr;

  // reduce memory copying
  TensorShape shape(data.dims);
  tensorflow::Tensor* result = new tensorflow::Tensor((DataType) data.dtype, shape);
  
  if (info->IsNumber())
    *((float*) result->tensor_data().data()) = info->NumberValue();
  else
    jsCollectValues((float*) result->tensor_data().data(), Handle<Array>::Cast(info), 0);
  
  return result;
}
 
TF_Tensor* ToTensor(int value) {
  const int byte_count = 1 * sizeof(int32_t);
  int32_t* values = reinterpret_cast<int32_t*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, byte_count));
  values[0] = value;
  return TF_NewTensor(TF_INT32, nullptr, 0, values, byte_count, &Deallocator, nullptr);
}

tensorflow::Tensor* ToTensor2(int value) {
  const int byte_count = 1 * sizeof(int);
  
  TensorShape shape({});
  tensorflow::Tensor* result = new tensorflow::Tensor((DataType) DT_INT32, shape);
  *((int32_t*) result->tensor_data().data()) = value;
  return result;
}

TF_Tensor* ToTensor(float value) {
  const float byte_count = 1 * sizeof(float);
  float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, byte_count));
  values[0] = value;
  return TF_NewTensor(TF_FLOAT, nullptr, 0, values, byte_count, &Deallocator, nullptr);
}

tensorflow::Tensor* ToTensor2(float value) {
  const int byte_count = 1 * sizeof(int);
  
  TensorShape shape({});
  tensorflow::Tensor* result = new tensorflow::Tensor((DataType) DT_FLOAT, shape);
  *((float*) result->tensor_data().data()) = value;
  return result;
}

void ToShape(std::vector<int64_t>& o_dims, TF_Tensor* value) {
  size_t dim_count = TF_NumDims(value);
  for (size_t i = 0; i < dim_count; i++) o_dims.push_back(TF_Dim(value, (int) i));
}

void ToShape(std::vector<int64_t>& o_dims, const tensorflow::Tensor& value) {
  size_t dim_count = value.dims();
  for (size_t i = 0; i < dim_count; i++) o_dims.push_back(value.dim_size((int) i));
}

void ToShape(std::vector<int64_t>& o_dims, const Local<Value>& info) {
  Local<Array> jsArray = Handle<Array>::Cast(info);
  for (uint32_t i = 0; i < jsArray->Length(); i++) o_dims.push_back(jsArray->Get(i)->NumberValue());
}

Local<Value> TensorValue(TF_DataType dtype, void* data, size_t offset) {
  switch (dtype) {
    // case DT_HALF: float16
    case DT_FLOAT: return Nan::New(*((float*) data + offset));
    case DT_DOUBLE: return Nan::New(*((double*) data + offset));
    case DT_INT32: return Nan::New(*((uint32_t*) data + offset));
    case DT_UINT8: return Nan::New(*((uint8_t*) data + offset));
    case DT_UINT16: return Nan::New(*((uint16_t*) data + offset));
    case DT_INT16: return Nan::New(*((int16_t*) data + offset));
    case DT_INT8: return Nan::New(*((int8_t*) data + offset));
    case DT_STRING: return Nan::New(*((uint8_t**) data + offset));
    // case DT_COMPLEX64: complex64
    // case DT_COMPLEX128: complex128
    case DT_INT64: return Nan::New(*((int32_t*) data + 2 * offset)); // TODO: make sure not lossing presicsion from 64 bit to 32 bit
    case DT_BOOL: return Nan::New(*((bool*) data + offset));
    // case DT_QINT8: qint8
    // case DT_QUINT8: quint8
    // case DT_QINT16: qint16
    // case DT_QUINT16: quint16
    // case DT_QINT32: qint32
    // // case DT_RESOURCE_REF: resource_ref
    // case DT_BFLOAT16: bfloat16
    // case DT_HALF_REF: float16_ref
    // case DT_FLOAT_REF: float32_ref
    // case DT_DOUBLE_REF: float64_ref
    // case DT_INT32_REF: int32_ref
    // case DT_UINT8_REF: uint8_ref
    // case DT_UINT16_REF: uint16_ref
    // case DT_INT16_REF: int16_ref
    // case DT_INT8_REF: int8_ref
    // case DT_STRING_REF: string_ref
    // case DT_COMPLEX64_REF: complex64_ref
    // case DT_COMPLEX128_REF: complex128_ref
    // case DT_INT64_REF: int64_ref
    // case DT_BOOL_REF: bool_ref
    // case DT_QINT8_REF: qint8_ref
    // case DT_QUINT8_REF: quint8_ref
    // case DT_QINT16_REF: qint16_ref
    // case DT_QUINT16_REF: quint16_ref
    // case DT_QINT32_REF: qint32_ref
    // case DT_BFLOAT16_REF: bfloat16_ref
    default: std::cout << "Cannot convert tensor value type: " << dtype; return Nan::Undefined();
  }
}

Local<Value> tfCollectValues(TF_Tensor* value, std::vector<int64_t>& dims, int dim_index, size_t& offset) {
  int dim_count = (int) dims.size();
  if (dim_index >= dim_count) return Nan::Undefined();
  int64_t dim = TF_Dim(value, dim_index);
  Local<Array> results = Nan::New<v8::Array>((int) dim);
  for (int64_t i = 0; i < dim; i++) {
    if (dim_index == dim_count - 1) {
      results->Set((int) i, TensorValue(TF_TensorType(value), TF_TensorData(value), offset));
      offset++;
    }
    else results->Set((int) i, tfCollectValues(value, dims, dim_index + 1, offset));
  }
  return results;
}

Local<Value> tfCollectValues(const tensorflow::Tensor& value, std::vector<int64_t>& dims, int dim_index, size_t& offset) {
  int dim_count = (int) dims.size();
  if (dim_index >= dim_count) return Nan::Undefined();
  int64_t dim = value.dim_size(dim_index);
  Local<Array> results = Nan::New<v8::Array>((int) dim);
  for (int64_t i = 0; i < dim; i++) {
    if (dim_index == dim_count - 1) {
      results->Set((int) i, TensorValue((TF_DataType) value.dtype(), (void*) value.tensor_data().data(), offset));
      offset++;
    }
    else results->Set((int) i, tfCollectValues(value, dims, dim_index + 1, offset));
  }
  return results;
}

Local<Value> ToValue(TF_Tensor* value) {
  if (!value) return Nan::Undefined(); // TODO: add warning for missing value

  size_t dim_count = TF_NumDims(value);
  if (dim_count == 0) return TensorValue(TF_TensorType(value), TF_TensorData(value), 0);
  
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

Local<Value> ToValue(const tensorflow::Tensor& value) {
  size_t dim_count = value.dims();
  if (dim_count == 0) return TensorValue((TF_DataType) value.dtype(), (void*) value.tensor_data().data(), 0);
  
  std::vector<int64_t> dims;
  for (size_t i = 0; i < dim_count; i++) dims.push_back(value.dim_size((int) i));

  size_t offset = 0;
  return tfCollectValues(value, dims, 0, offset);
}

Local<Value> ToArrayValue(const std::vector<tensorflow::Tensor>& value) {
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
