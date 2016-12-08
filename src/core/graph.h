#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include "tensorflow/c/c_api.h"
#include "tensorflow/core/platform/types.h"

namespace tensorflow {

class Graph {
  public:
    Graph();
    TF_Operation* Placeholder();
    TF_Operation* ScalarConst(int v);
    TF_Operation* Add(TF_Operation* l, TF_Operation* r);
    int Run(const std::vector<int>& ops, int v);

  private:
    TF_Graph* m_graph = nullptr;
    std::vector<TF_Operation*> m_inputs;
    std::vector<TF_Operation*> m_outputs;
};

} // namespace tensorflow

#endif  // CORE_GRAPH_H