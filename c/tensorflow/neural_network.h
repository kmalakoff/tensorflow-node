#ifndef CORE_NEURAL_NETWORK_H
#define CORE_NEURAL_NETWORK_H

#include <vector>

// forward declarations
struct TF_Operation;
struct TF_Graph;

namespace tensorflow {

class NeuralNetwork {
  public:
    static TF_Operation* softmax(TF_Graph *graph, TF_Operation* v);
    static TF_Operation* softmax_cross_entropy_with_logits(TF_Graph *graph, TF_Operation* y, TF_Operation* y_);
};

} // namespace tensorflow

#endif // CORE_NEURAL_NETWORK_H
