#ifndef TF_OPS_H
#define TF_OPS_H

#include <vector>
#include "tensorflow/core/framework/types.pb.h"

// forward declarations
namespace tensorflow { class Scope; }
namespace tensorflow { namespace ops {class Output; } }

namespace tf {
namespace ops {

using namespace tensorflow;
using namespace tensorflow::ops;

Output Placeholder(Scope& scope, DataType dtype, const std::vector<int64_t>& dims);
Output Variable(Scope& scope, DataType dtype, const std::vector<int64_t>& dims);
Output Assign(Scope& scope, const Output& target, const Output& value);
Output Cast(Scope& scope, const Output& value, DataType dtype);

} // namespace ops
} // namespace tf

#endif // TF_OPS_H
