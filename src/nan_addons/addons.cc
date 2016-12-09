#include <nan.h>
#include "tensorflow/core/platform/types.h"
#include "tensorflow/c/c_api.h"
#include "../tensorflow/tensorflow.h"
#include "addons.h"
#include "graph.h"
#include "operation.h"

namespace nan_addons {

using namespace v8;
using namespace tensorflow;

static void Deallocator(void* data, size_t, void* arg) { tensorflow::cpu_allocator()->DeallocateRaw(data); }

static void Dimensions(std::vector<int64_t>& o_dims, Handle<Array> jsArray) {
  o_dims.push_back(jsArray->Length());
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    if (jsArray->Get(i)->IsArray()) {
      Dimensions(o_dims, Handle<Array>::Cast(jsArray->Get(i)));
    }
    break;
  }
}

static int Values(float* o_values, Handle<Array> jsArray, int index) {
  for (unsigned int i = 0; i < jsArray->Length(); i++) {
    if (jsArray->Get(i)->IsArray()) {
      index = Values(o_values, Handle<Array>::Cast(jsArray->Get(i)), index);
    }
    else {
      o_values[index] = jsArray->Get(i)->NumberValue();
      index++;
    }
  }
  return index;
}

void AddOns::Init(Local<Object> exports) {
  nan_addons::Graph::Init(exports);
  nan_addons::Operation::Init(exports);
}

TF_Tensor* AddOns::_VALUE_TO_TENSOR(const Local<Value>& info) {
  if (info->IsNumber()) {
    const int num_bytes = 1 * sizeof(float);
    float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, num_bytes));
    values[0] = info->NumberValue();
    return TF_NewTensor(TF_FLOAT, nullptr, 0, values, num_bytes, &Deallocator, nullptr);
  }
  else if (info->IsArray()) {
    Handle<Array> jsArray = Handle<Array>::Cast(info);
    std::vector<int64_t> dims;
    Dimensions(dims, jsArray);

    const int num_bytes = (int) std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<int64_t>()) * sizeof(float);
    float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, num_bytes));
    Values(values, jsArray, 0);

    return TF_NewTensor(TF_FLOAT, &dims[0], dims.size(), values, num_bytes, &Deallocator, nullptr);
  }

  return nullptr;
}

Local<Value> AddOns::_TENSOR_TO_BUFFER_VALUE(TF_Tensor* value) {
  Local<Object> buf = Nan::NewBuffer(TF_TensorByteSize(value)).ToLocalChecked();
  uint8* data = (uint8*) node::Buffer::Data(buf);
  memcpy(data, TF_TensorData(value), TF_TensorByteSize(value));

  Local<v8::Object> globalObj = Nan::GetCurrentContext()->Global();
  Local<v8::Function> bufferConstructor = Local<v8::Function> ::Cast(globalObj->Get(Nan::New<String>("Buffer").ToLocalChecked()));
  Local<Value> constructorArgs[3] = {buf, Nan::New<v8::Integer>((unsigned)TF_TensorByteSize(value)), Nan::New<v8::Integer>(0)};
  return Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();
}

} // namespace nan_addons

NODE_MODULE(Tensorflow, nan_addons::AddOns::Init)

// IN_TO_BUFFER
// char* buf = VALUE_TO_BUFFER_DATA(info[0]);
// size_t len = VALUE_TO_BUFFER_LENGTH(info[0]);
// int arg0 = *((int32*) buf);
