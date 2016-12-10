#ifndef CORE_TRAIN_H
#define CORE_TRAIN_H

#include <vector>

// forward declarations
struct TF_Operation;
struct TF_Graph;

namespace tensorflow {

class Train {
  public:
    static TF_Operation* GradientDescentOptimizer(TF_Graph *graph, TF_Operation* v);
};

} // namespace tensorflow

#endif // CORE_TRAIN_H
