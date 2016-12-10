#ifndef TENSOR_H
#define TENSOR_H

#include "tensorflow/c/c_api.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"

struct TF_Tensor {
  TF_DataType dtype;
  tensorflow::TensorShape shape;
  tensorflow::TensorBuffer* buffer;
};

#endif // TENSOR_H
