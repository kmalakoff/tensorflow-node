#ifndef TF_C_OPS_H
#define TF_C_OPS_H

#include <vector>
#include "tensorflow/c/c_api.h" // TF_DataType

// forward declarations
struct TF_Graph;
struct TF_Operation;

namespace tf {
namespace ops {

//////////////////////////////////////////////
// Graph
//////////////////////////////////////////////
static TF_Operation* Placeholder(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims);
static TF_Operation* Variable(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims);

//////////////////////////////////////////////
// Math
//////////////////////////////////////////////
static TF_Operation* Const(TF_Graph *graph, TF_Tensor* value);
static TF_Operation* Assign(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
static TF_Operation* Add(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
static TF_Operation* MatMul(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
static TF_Operation* Equal(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
static TF_Operation* ArgMax(TF_Graph *graph, TF_Operation* v, int dim);
static TF_Operation* Cast(TF_Graph *graph, TF_Operation* v, TF_DataType dtype);
static TF_Operation* Mean(TF_Graph *graph, TF_Operation* v, TF_Operation* reduction_indices);
static TF_Operation* Log(TF_Graph *graph, TF_Operation* v);

//////////////////////////////////////////////
// Neural Network
//////////////////////////////////////////////
static TF_Operation* Softmax(TF_Graph *graph, TF_Operation* v);
static TF_Operation* SoftmaxCrossEntropyWithLogits(TF_Graph *graph, TF_Operation* y, TF_Operation* y_);

//////////////////////////////////////////////
// Train
//////////////////////////////////////////////
static TF_Operation* GradientDescentOptimizer(TF_Graph *graph, float learning_rate, TF_Operation* v);

} // namespace ops
} // namespace tf

#endif // TF_C_OPS_H
