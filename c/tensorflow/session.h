#ifndef CORE_SESSION_H
#define CORE_SESSION_H

#include <vector>
#include <nan.h> // remove dependency

// forward declarations
struct TF_Graph;
struct TF_Operation;
struct TF_SessionWithGraph;
struct TF_Tensor;

namespace tensorflow {

class Session {
  public:
    static TF_SessionWithGraph* create(TF_Graph* graph);
    static void destroy(TF_SessionWithGraph* session);
    static void run(std::vector<TF_Tensor*>& o_results, TF_SessionWithGraph* m_session, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);
    static void runNoOut(TF_SessionWithGraph* m_session, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);
};

} // namespace tensorflow

#endif // CORE_SESSION_H
