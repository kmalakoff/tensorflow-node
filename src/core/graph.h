#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include "tensorflow/c/c_api.h"
#include <nan.h> // remove dependency

namespace tensorflow {

class Graph {
  public:
    Graph();
    TF_Operation* Placeholder();
    TF_Operation* ScalarConst(int v);
    TF_Operation* Add(TF_Operation* l, TF_Operation* r);
    void Run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, v8::Handle<v8::Object>& inputs);

  private:
    TF_Graph* m_graph;
    std::vector<TF_Operation*> m_inputs;
    std::vector<TF_Operation*> m_outputs;
};

} // namespace tensorflow

#endif  // CORE_GRAPH_H