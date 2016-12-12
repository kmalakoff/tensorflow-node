#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include <nan.h> // remove dependency
#include "tensorflow/c/c_api.h" // TF_DataType

// forward declarations
struct TF_Operation;
struct TF_Tensor;
struct TF_Graph;

namespace tf {

class Graph {
  public:
    static TF_Graph* create();
    static void destroy(TF_Graph* graph);

    static TF_Operation* placeholder(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims);
    static TF_Operation* variable(TF_Graph *graph, TF_DataType dtype, const std::vector<int64_t>& dims);
    static TF_Operation* variableInitializer(TF_Graph *graph, TF_Operation* variable, TF_Tensor* value);
    static TF_Operation* constant(TF_Graph *graph, TF_Tensor* value);
    static TF_Operation* assign(TF_Graph *graph, TF_Operation* l, TF_Operation* r);
    static void run(std::vector<TF_Tensor*>& o_results, TF_Graph* graph, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);
};

} // namespace tf

#endif // CORE_GRAPH_H
