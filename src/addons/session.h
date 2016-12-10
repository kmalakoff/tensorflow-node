#ifndef NAN_SESSION_H
#define NAN_SESSION_H

#include "addons.h"

// forward declarations
namespace tensorflow { class Session; }
namespace addons { class Graph; }

namespace addons {

class Session: public Nan::ObjectWrap {
  public:
    Session(Graph* graph);
    ~Session();

    NAN_TO_VALUE(Session, ToValue);
    tensorflow::Session* ref() { return m_ref; }

  private:
    tensorflow::Session* m_ref;
    Graph* m_graph;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
};

} // namespace addons

#endif // NAN_SESSION_H
