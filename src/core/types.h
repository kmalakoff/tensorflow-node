#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include "tensorflow/core/framework/types.pb.h"

namespace tensorflow {
namespace js {

enum class Types {
  float32 = DT_FLOAT,
  float64 = DT_DOUBLE
};

} // js
} // tensorflow

#endif  // CORE_TYPES_H


  // DT_FLOAT = 1;
  // DT_DOUBLE = 2;
  // DT_INT32 = 3;
  // DT_UINT8 = 4;
  // DT_INT16 = 5;
  // DT_INT8 = 6;
  // DT_STRING = 7;
  // DT_COMPLEX64 = 8;  // Single-precision complex
  // DT_INT64 = 9;
  // DT_BOOL = 10;
  // DT_QINT8 = 11;     // Quantized int8
  // DT_QUINT8 = 12;    // Quantized uint8
  // DT_QINT32 = 13;    // Quantized int32
  // DT_BFLOAT16 = 14;  // Float32 truncated to 16 bits.  Only for cast ops.
  // DT_QINT16 = 15;    // Quantized int16
  // DT_QUINT16 = 16;   // Quantized uint16
  // DT_UINT16 = 17;
  // DT_COMPLEX128 = 18;  // Double-precision complex
  // DT_HALF = 19;
  // DT_RESOURCE = 20;

// resource = DType(types_pb2.DT_RESOURCE)
// float16 = DType(types_pb2.DT_HALF)
// half = float16
// float32 = DType(types_pb2.DT_FLOAT)
// float64 = DType(types_pb2.DT_DOUBLE)
// double = float64
// int32 = DType(types_pb2.DT_INT32)
// uint8 = DType(types_pb2.DT_UINT8)
// uint16 = DType(types_pb2.DT_UINT16)
// int16 = DType(types_pb2.DT_INT16)
// int8 = DType(types_pb2.DT_INT8)
// string = DType(types_pb2.DT_STRING)
// complex64 = DType(types_pb2.DT_COMPLEX64)
// complex128 = DType(types_pb2.DT_COMPLEX128)
// int64 = DType(types_pb2.DT_INT64)
// bool = DType(types_pb2.DT_BOOL)
// qint8 = DType(types_pb2.DT_QINT8)
// quint8 = DType(types_pb2.DT_QUINT8)
// qint16 = DType(types_pb2.DT_QINT16)
// quint16 = DType(types_pb2.DT_QUINT16)
// qint32 = DType(types_pb2.DT_QINT32)
// resource_ref = DType(types_pb2.DT_RESOURCE_REF)
// bfloat16 = DType(types_pb2.DT_BFLOAT16)
// float16_ref = DType(types_pb2.DT_HALF_REF)
// half_ref = float16_ref
// float32_ref = DType(types_pb2.DT_FLOAT_REF)
// float64_ref = DType(types_pb2.DT_DOUBLE_REF)
// double_ref = float64_ref
// int32_ref = DType(types_pb2.DT_INT32_REF)
// uint8_ref = DType(types_pb2.DT_UINT8_REF)
// uint16_ref = DType(types_pb2.DT_UINT16_REF)
// int16_ref = DType(types_pb2.DT_INT16_REF)
// int8_ref = DType(types_pb2.DT_INT8_REF)
// string_ref = DType(types_pb2.DT_STRING_REF)
// complex64_ref = DType(types_pb2.DT_COMPLEX64_REF)
// complex128_ref = DType(types_pb2.DT_COMPLEX128_REF)
// int64_ref = DType(types_pb2.DT_INT64_REF)
// bool_ref = DType(types_pb2.DT_BOOL_REF)
// qint8_ref = DType(types_pb2.DT_QINT8_REF)
// quint8_ref = DType(types_pb2.DT_QUINT8_REF)
// qint16_ref = DType(types_pb2.DT_QINT16_REF)
// quint16_ref = DType(types_pb2.DT_QUINT16_REF)
// qint32_ref = DType(types_pb2.DT_QINT32_REF)
// bfloat16_ref = DType(types_pb2.DT_BFLOAT16_REF)
