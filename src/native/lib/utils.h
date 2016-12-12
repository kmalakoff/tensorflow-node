#ifndef LIB_UTILS_H
#define LIB_UTILS_H

#include <string>
#include "tensorflow/cc/framework/ops.h"

namespace lib {

std::string uniqueId(const char* key);
std::string nodeName(const tensorflow::Node* node); // TODO: remove after headers match for node name

} // namespace lib

#endif // LIB_UTILS_H
