#include "types.h"
#include "tensorflow/core/framework/types.pb.h"

namespace nan_bridge {

using namespace v8;
using namespace tensorflow;

#define CONST(n, v) obj->Set(Nan::New<String>(n).ToLocalChecked(), Nan::New<Integer>(v));

NAN_MODULE_INIT(Types::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  // CONST("resource", DT_RESOURCE);
  CONST("float16", DT_HALF);
  CONST("half", DT_HALF);
  CONST("float32", DT_FLOAT);
  CONST("float64", DT_DOUBLE);
  CONST("double", DT_DOUBLE);
  CONST("int32", DT_INT32);
  CONST("uint8", DT_UINT8);
  CONST("uint16", DT_UINT16);
  CONST("int16", DT_INT16);
  CONST("int8", DT_INT8);
  CONST("string", DT_STRING);
  CONST("complex64", DT_COMPLEX64);
  CONST("complex128", DT_COMPLEX128);
  CONST("int64", DT_INT64);
  CONST("bool", DT_BOOL);
  CONST("qint8", DT_QINT8);
  CONST("quint8", DT_QUINT8);
  CONST("qint16", DT_QINT16);
  CONST("quint16", DT_QUINT16);
  CONST("qint32", DT_QINT32);
  // CONST("resource_ref", DT_RESOURCE_REF);
  CONST("bfloat16", DT_BFLOAT16);
  CONST("float16_ref", DT_HALF_REF);
  CONST("half_ref", DT_HALF_REF);
  CONST("float32_ref", DT_FLOAT_REF);
  CONST("float64_ref", DT_DOUBLE_REF);
  CONST("double_ref", DT_DOUBLE_REF);
  CONST("int32_ref", DT_INT32_REF);
  CONST("uint8_ref", DT_UINT8_REF);
  CONST("uint16_ref", DT_UINT16_REF);
  CONST("int16_ref", DT_INT16_REF);
  CONST("int8_ref", DT_INT8_REF);
  CONST("string_ref", DT_STRING_REF);
  CONST("complex64_ref", DT_COMPLEX64_REF);
  CONST("complex128_ref", DT_COMPLEX128_REF);
  CONST("int64_ref", DT_INT64_REF);
  CONST("bool_ref", DT_BOOL_REF);
  CONST("qint8_ref", DT_QINT8_REF);
  CONST("quint8_ref", DT_QUINT8_REF);
  CONST("qint16_ref", DT_QINT16_REF);
  CONST("quint16_ref", DT_QUINT16_REF);
  CONST("qint32_ref", DT_QINT32_REF);
  CONST("bfloat16_ref", DT_BFLOAT16_REF);

  target->Set(Nan::New("TYPES").ToLocalChecked(), obj);
};

} // namespace nan_bridge
