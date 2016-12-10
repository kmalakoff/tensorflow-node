#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include <nan.h> // remove dependency
#include "tensorflow/c/c_api.h" // TF_DataType

// forward declarations
struct TF_Operation;
struct TF_Tensor;
struct TF_Graph;

namespace tensorflow {

class Graph {
  public:
    Graph();
    TF_Graph* ref() { return m_ref; }

    TF_Operation* placeholder(TF_DataType dtype, const std::vector<int64_t>& dims);
    TF_Operation* variable(TF_Tensor* value, const std::vector<int64_t>& dims);
    void variable_initializers(std::vector<TF_Operation*>& o_variable_initializers) { o_variable_initializers = this->m_variable_initializers; }
    TF_Operation* constant(TF_Tensor* value);
    TF_Operation* assign(TF_Operation* l, TF_Operation* r);
    TF_Operation* add(TF_Operation* l, TF_Operation* r);
    TF_Operation* matmul(TF_Operation* l, TF_Operation* r);
    void run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);

  private:
    TF_Graph* m_ref;
    std::vector<TF_Operation*> m_variable_initializers;
};

} // namespace tensorflow

#endif // CORE_GRAPH_H
