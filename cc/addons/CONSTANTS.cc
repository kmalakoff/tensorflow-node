#include "CONSTANTS.h"
#include "tensorflow/core/public/version.h"

namespace addons {

using namespace v8;

#define CONST_STRING(n, v) obj->Set(Nan::New<String>(n).ToLocalChecked(), Nan::New<String>(v).ToLocalChecked());

NAN_MODULE_INIT(CONSTANTS::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  CONST_STRING("VERSION", TF_VERSION_STRING);

  target->Set(Nan::New("CONSTANTS").ToLocalChecked(), obj);
};

} // namespace addons
