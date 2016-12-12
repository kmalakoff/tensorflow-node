#ifndef CORE_TRAIN_H
#define CORE_TRAIN_H

#include <vector>

// forward declarations
struct TF_Operation;
struct TF_Graph;

namespace tf {

class Train {
  public:
    static TF_Operation* GradientDescentOptimizer(TF_Graph *graph, float learning_rate, TF_Operation* v);
};

} // namespace tf

#endif // CORE_TRAIN_H
