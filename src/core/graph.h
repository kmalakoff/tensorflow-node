#ifndef TENSORFLOW_JS_GRAPH_H_
#define TENSORFLOW_JS_GRAPH_H_

#include "tensorflow/c/c_api.h"
#include "tensorflow/core/platform/types.h"

class Graph {
  public:
    Graph();
    TF_Operation* Placeholder();
    TF_Operation* ScalarConst(int v);
    TF_Operation* Add(TF_Operation* l, TF_Operation* r);
    int Run(TF_Operation* op1, TF_Operation* op2);

  private:
    TF_Graph* graph = nullptr;
};

#endif  // TENSORFLOW_JS_GRAPH_H_