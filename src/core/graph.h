#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include "tensorflow/c/c_api.h"
#include <nan.h> // remove dependency
#include "../tensorflow/tensorflow.h"

namespace tensorflow {

class Graph {
  public:
    Graph();
    TF_Operation* input();
    TF_Operation* constant(TF_Tensor* value);
    TF_Operation* add(TF_Operation* l, TF_Operation* r);
    TF_Operation* matmul(TF_Operation* l, TF_Operation* r);
    void run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, v8::Local<v8::Array>& inputs);

  private:
    TF_Graph* m_graph;
    std::vector<TF_Operation*> m_inputs;
};

} // namespace tensorflow

#endif // CORE_GRAPH_H
