#ifndef CORE_MATH_OPS_H
#define CORE_MATH_OPS_H

#include <vector>

// forward declarations
struct TF_Operation;
struct TF_Tensor;
struct TF_Graph;

namespace tensorflow {

class MathOps {
  public:
    static TF_Operation* add(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
    static TF_Operation* matmul(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
};

} // namespace tensorflow

#endif // CORE_MATH_OPS_H
