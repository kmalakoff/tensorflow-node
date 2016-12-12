#ifndef CORE_SESSION_H
#define CORE_SESSION_H

#include <vector>
#include <nan.h> // remove dependency

// forward declarations
struct TF_Graph;
struct TF_Operation;
struct TF_SessionWithGraph;
struct TF_Tensor;

namespace tf {

class Session {
  public:
    static TF_SessionWithGraph* create(TF_Graph* graph);
    static void destroy(TF_SessionWithGraph* session);
};

} // namespace tf

#endif // CORE_SESSION_H
