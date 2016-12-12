#ifndef TF_OPS_H
#define TF_OPS_H

#include <vector>
#include "tensorflow/core/framework/types.pb.h" // DataType

// forward declarations
namespace tensorflow { class Scope; }
namespace tensorflow { namespace ops {class Output; } }

namespace tf {
namespace ops {

using namespace tensorflow;
using namespace tensorflow::ops;

//////////////////////////////////////////////
// Graph
//////////////////////////////////////////////
Output Placeholder(Scope& scope, DataType dtype, const std::vector<int64_t>& dims);
Output Variable(Scope& scope, DataType dtype, const std::vector<int64_t>& dims);

//////////////////////////////////////////////
// Math
//////////////////////////////////////////////
Output Assign(Scope& scope, const Output& target, const Output& value);
Output Cast(Scope& scope, const Output& value, DataType dtype);
Output ReduceMean(Scope& scope, const Output& v, const Output& reduction_indices);

//////////////////////////////////////////////
// Train
//////////////////////////////////////////////
Output GradientDescentOptimizer(Scope& scope, float learning_rate, const Output& v);

} // namespace ops
} // namespace tf

#endif // TF_OPS_H
