#ifndef TENSORFLOW_JS_GRAPH_H_
#define TENSORFLOW_JS_GRAPH_H_

#include <vector>
#include "tensorflow/c/c_api.h"
#include "tensorflow/core/platform/types.h"

class Graph {
  public:
    Graph();
    TF_Operation* Placeholder();
    TF_Operation* ScalarConst(int v);
    TF_Operation* Add(TF_Operation* l, TF_Operation* r);
    int Run(int v);
    // int Run(const std::vector<int> ops, int v);

  private:
    TF_Graph* m_graph = nullptr;
    std::vector<TF_Operation*> m_inputs;
    std::vector<TF_Operation*> m_outputs;
};

#endif  // TENSORFLOW_JS_GRAPH_H_