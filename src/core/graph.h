#ifndef TENSORFLOW_JS_GRAPH_H_
#define TENSORFLOW_JS_GRAPH_H_

#include "tensorflow/c/c_api.h"
#include "tensorflow/core/platform/types.h"

TF_Graph* createGraph();
TF_Operation* Placeholder(TF_Graph* graph);
TF_Operation* ScalarConst(TF_Graph* graph, int v);
TF_Operation* Add(TF_Graph* graph, TF_Operation* l, TF_Operation* r);
int run(TF_Graph* graph, TF_Operation* op1, TF_Operation* op2);

#endif  // TENSORFLOW_JS_GRAPH_H_