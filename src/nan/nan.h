#ifndef NAN_H
#define NAN_H

#include "addons.h"

#define NAN_WRAP_RESULT(OW, T, r) nan::AddOns::_nan_wrap_result<OW, T>(r)

#endif // NAN_H
