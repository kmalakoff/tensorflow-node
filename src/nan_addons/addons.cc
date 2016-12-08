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

static void Int32Deallocator(void* data, size_t, void* arg) {
  delete[] static_cast<int32*>(data);
}

static void Float32Deallocator(void* data, size_t, void* arg) {
  delete[] static_cast<float*>(data);
}

static void Deallocator(void* data, size_t, void* arg) {
  tensorflow::cpu_allocator()->DeallocateRaw(data);
  // *reinterpret_cast<bool*>(arg) = true;
}

static TF_Tensor* Int32Tensor(int32 v) {
  const int num_bytes = sizeof(int32);
  int32* values = new int32[1];
  values[0] = v;
  return TF_NewTensor(TF_INT32, nullptr, 0, values, num_bytes, &Int32Deallocator, nullptr);
}

void AddOns::Init(Local<Object> exports) {
  nan_addons::Graph::Init(exports);
  nan_addons::Operation::Init(exports);
}

TF_Tensor* AddOns::_NAN_IN_TO_TENSOR(const v8::Local<v8::Value>& info) {
  if (info->IsNumber()) {
    // const int num_bytes = sizeof(float);
    // float* values = new float[1];
    // values[0] = info->NumberValue();
    // return TF_NewTensor(TF_FLOAT, nullptr, 0, values, num_bytes, &Float32Deallocator, nullptr);
  }
  else if (info->IsArray()) {
    // std::cout << "\ntensor";
    Handle<Array> jsArray = Handle<Array>::Cast(info);

    const int num_bytes = 2 * sizeof(float);
    float* values = reinterpret_cast<float*>(tensorflow::cpu_allocator()->AllocateRaw(EIGEN_MAX_ALIGN_BYTES, num_bytes));

    // std::cout << num_bytes;
    // std::cout << jsArray->Length();    
    // std::cout << "\n";

    if (jsArray->Length() == 1) {
      values[0] = 3.f;
      values[1] = 3.f;
      int64_t dims[] = {2};
      return TF_NewTensor(TF_FLOAT, dims, sizeof(dims) / sizeof(int64_t), values, num_bytes, &Deallocator, nullptr);
    }
    else {
      values[0] = 2.f;
      values[1] = 2.f;
      int64_t dims[] = {1, 1};
      return TF_NewTensor(TF_FLOAT, dims, sizeof(dims) / sizeof(int64_t), values, num_bytes, &Deallocator, nullptr);
    }
  }

  return nullptr;
}

} // namespace nan_addons

NODE_MODULE(Tensorflow, nan_addons::AddOns::Init)
