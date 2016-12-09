#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include "nan.h"

// forward declarations
namespace tensorflow { class Graph; }

namespace nan_addons {

class Graph: public Nan::ObjectWrap {
  public:
    Graph();
    ~Graph();

    NAN_TO_VALUE(Graph, ToValue);
    tensorflow::Graph* ref() { return m_graph; }

  private:
    tensorflow::Graph* m_graph;

  /////////////////////////////////
  // Nan Lifecycle
  /////////////////////////////////
  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(input);
    static NAN_METHOD(constant);
    static NAN_METHOD(add);
    static NAN_METHOD(matmul);
    static NAN_METHOD(run);
};

}

#endif // NAN_GRAPH_H
