#include "tf_ops.h"

#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/core/graph/node_builder.h"

namespace tf {
namespace ops {

using namespace tensorflow;
using namespace ops;

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

} // namespace ops
} // namespace tf
