#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include "nan.h"

// forward declarations
namespace tensorflow { class Graph; }

namespace nan_addons {

class Graph: public Nan::ObjectWrap {
  public:
    tensorflow::Graph* ref() { return m_graph; }

    static NAN_METHOD(input);
    static NAN_METHOD(constant);
    static NAN_METHOD(add);
    static NAN_METHOD(matmul);
    static NAN_METHOD(run);

  private:
    Graph();
    ~Graph();

    tensorflow::Graph* m_graph;

    /////////////////////////////////
    // Nan Lifecycle
    /////////////////////////////////
    friend class AddOns;
    static NAN_CONSTRUCTOR(constructor);
    static NAN_MODULE_INIT(Init);
    static NAN_NEW(New);
};

}

#endif // NAN_GRAPH_H
