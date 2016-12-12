#include "tf_ops.h"
#include "../lib/conversions.h"

#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/core/graph/node_builder.h"

namespace tf {
namespace ops {

using namespace tensorflow;
using namespace ops;

//////////////////////////////////////////////
// Graph
//////////////////////////////////////////////
Output Placeholder(Scope& scope, DataType dtype, const std::vector<int64_t>& dims) {
  TensorShape shape(dims);
  const auto op_name = scope.GetUniqueNameForOp("Placeholder");
  auto builder = NodeBuilder(op_name, "Placeholder")
    .Attr("dtype", dtype)
    .Attr("shape", shape);
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}

Output Variable(Scope& scope, DataType dtype, const std::vector<int64_t>& dims) {
  TensorShape shape(dims);
  const auto op_name = scope.GetUniqueNameForOp("Variable");
  auto builder = NodeBuilder(op_name, "Variable")
    .Attr("dtype", dtype)
    .Attr("shape", shape);
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}

//////////////////////////////////////////////
// Math
//////////////////////////////////////////////
Output Assign(Scope& scope, const Output& target, const Output& value) {
  const auto op_name = scope.GetUniqueNameForOp("Assign");
  auto builder = NodeBuilder(op_name, "Assign")
    .Input(target.node())
    .Input(value.node())
    .Attr("use_locking", true);
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}

Output Cast(Scope& scope, const Output& value, DataType dtype) {
  const auto op_name = scope.GetUniqueNameForOp("Cast");
  auto builder = NodeBuilder(op_name, "Cast")
    .Attr("DstT", dtype)
    .Input(value.node());
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}

Output ReduceMean(Scope& scope, const Output& v, const Output& reduction_indices) {
  const auto op_name = scope.GetUniqueNameForOp("ReduceMean");
  auto builder = NodeBuilder(op_name, "Mean")
    .Input(v.node())
    .Input(reduction_indices.node());
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}
  
  //////////////////////////////////////////////
// Train
//////////////////////////////////////////////
Output GradientDescentOptimizer(Scope& scope, float learning_rate, const Output& v) {
  auto alpha_tensor = lib::ToTensor2(learning_rate);
  auto alpha = Const<float>(scope, *alpha_tensor);
  auto delta_tensor = lib::ToTensor2(100.0f);
  auto delta = Const<float>(scope, *delta_tensor);

  const auto op_name = scope.GetUniqueNameForOp("ApplyGradientDescent");
  auto builder = NodeBuilder(op_name, "ApplyGradientDescent")
    .Input(v.node())
    .Input(alpha.node())
    .Input(delta.node());
  scope.UpdateBuilder(&builder);
  Node* ret;
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  return Output(ret, 0);
}

} // namespace ops
} // namespace tf
