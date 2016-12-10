#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include "nan.h"

// forward declarations
namespace tensorflow { class Graph; }

namespace nan_bridge {

class Graph: public Nan::ObjectWrap {
  public:
    Graph();
    ~Graph();

    NAN_TO_VALUE(Graph, ToValue);
    tensorflow::Graph* ref() { return m_ref; }

  private:
    tensorflow::Graph* m_ref;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(placeholder);
    static NAN_METHOD(variable);
    static NAN_METHOD(constant);
    static NAN_METHOD(add);
    static NAN_METHOD(matmul);
    static NAN_METHOD(run);
};

}

#endif // NAN_GRAPH_H
