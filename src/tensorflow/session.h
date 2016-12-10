#ifndef CORE_SESSION_H
#define CORE_SESSION_H

#include <vector>
#include <nan.h> // remove dependency
#include "tensorflow/c/c_api.h"

// forward declarations
struct TF_Operation;
struct TF_Tensor;
struct TF_SessionWithGraph;

namespace tensorflow {

class Session {
  public:
    Session();
    void run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);

  private:
    TF_SessionWithGraph* m_ref;
    std::vector<TF_Operation*> m_initializers;
};

} // namespace tensorflow

#endif // CORE_SESSION_H
