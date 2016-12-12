#include "Types.h"
#include "tensorflow/core/framework/types.pb.h"

namespace addons {

using namespace v8;
using namespace tensorflow;

#define CONST_INT(n, v) obj->Set(Nan::New<String>(n).ToLocalChecked(), Nan::New<Integer>(v));

NAN_MODULE_INIT(Types::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  // CONST_INT("resource", DT_RESOURCE);
  CONST_INT("float16", DT_HALF);
  CONST_INT("half", DT_HALF);
  CONST_INT("float32", DT_FLOAT);
  CONST_INT("float64", DT_DOUBLE);
  CONST_INT("double", DT_DOUBLE);
  CONST_INT("int32", DT_INT32);
  CONST_INT("uint8", DT_UINT8);
  CONST_INT("uint16", DT_UINT16);
  CONST_INT("int16", DT_INT16);
  CONST_INT("int8", DT_INT8);
  CONST_INT("string", DT_STRING);
  CONST_INT("complex64", DT_COMPLEX64);
  CONST_INT("complex128", DT_COMPLEX128);
  CONST_INT("int64", DT_INT64);
  CONST_INT("bool", DT_BOOL);
  CONST_INT("qint8", DT_QINT8);
  CONST_INT("quint8", DT_QUINT8);
  CONST_INT("qint16", DT_QINT16);
  CONST_INT("quint16", DT_QUINT16);
  CONST_INT("qint32", DT_QINT32);
  // CONST_INT("resource_ref", DT_RESOURCE_REF);
  CONST_INT("bfloat16", DT_BFLOAT16);
  CONST_INT("float16_ref", DT_HALF_REF);
  CONST_INT("half_ref", DT_HALF_REF);
  CONST_INT("float32_ref", DT_FLOAT_REF);
  CONST_INT("float64_ref", DT_DOUBLE_REF);
  CONST_INT("double_ref", DT_DOUBLE_REF);
  CONST_INT("int32_ref", DT_INT32_REF);
  CONST_INT("uint8_ref", DT_UINT8_REF);
  CONST_INT("uint16_ref", DT_UINT16_REF);
  CONST_INT("int16_ref", DT_INT16_REF);
  CONST_INT("int8_ref", DT_INT8_REF);
  CONST_INT("string_ref", DT_STRING_REF);
  CONST_INT("complex64_ref", DT_COMPLEX64_REF);
  CONST_INT("complex128_ref", DT_COMPLEX128_REF);
  CONST_INT("int64_ref", DT_INT64_REF);
  CONST_INT("bool_ref", DT_BOOL_REF);
  CONST_INT("qint8_ref", DT_QINT8_REF);
  CONST_INT("quint8_ref", DT_QUINT8_REF);
  CONST_INT("qint16_ref", DT_QINT16_REF);
  CONST_INT("quint16_ref", DT_QUINT16_REF);
  CONST_INT("qint32_ref", DT_QINT32_REF);
  CONST_INT("bfloat16_ref", DT_BFLOAT16_REF);

  target->Set(Nan::New("Types").ToLocalChecked(), obj);
};

} // namespace addons
