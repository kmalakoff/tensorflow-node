#ifndef CORE_MATH_OPS_H
#define CORE_MATH_OPS_H

#include <vector>
#include "tensorflow/c/c_api.h" // TF_DataType

// forward declarations
struct TF_Operation;
struct TF_Graph;

namespace tf {

class MathOps {
  public:
    static TF_Operation* add(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
    static TF_Operation* matmul(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
    static TF_Operation* matmul_add(TF_Graph *graph, TF_Operation* l, TF_Operation* r, TF_Operation* a);
    static TF_Operation* reduce_mean(TF_Graph *graph, TF_Operation* v);
    static TF_Operation* equal(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
    static TF_Operation* argmax(TF_Graph *graph, TF_Operation* v, int dim);
    static TF_Operation* cast(TF_Graph *graph, TF_Operation* v, TF_DataType dtype);
    static TF_Operation* log(TF_Graph *graph, TF_Operation* v);
};

} // namespace tf

#endif // CORE_MATH_OPS_H
