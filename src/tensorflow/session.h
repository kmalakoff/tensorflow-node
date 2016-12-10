#ifndef CORE_SESSION_H
#define CORE_SESSION_H

#include <vector>
#include <nan.h> // remove dependency

// forward declarations
struct TF_Operation;
struct TF_Tensor;
struct TF_SessionWithGraph;

namespace tensorflow {

class Session {
  public:
    Session(TF_SessionWithGraph* session);
    TF_SessionWithGraph* ref() { return m_ref; }

    void run(std::vector<TF_Tensor*>& o_results, const std::vector<TF_Operation*>& ops, const v8::Local<v8::Value>& input_pairs);

  private:
    TF_SessionWithGraph* m_ref;
};

} // namespace tensorflow

#endif // CORE_SESSION_H
