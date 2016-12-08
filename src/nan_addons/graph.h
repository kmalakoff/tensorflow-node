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
    tensorflow::Graph* ref() { return m_graph; }

    static NAN_METHOD(constant);
    static NAN_METHOD(matmul);
    static NAN_METHOD(run);

    static NAN_METHOD(Placeholder);
    static NAN_METHOD(ScalarConst);
    static NAN_METHOD(Add);
    static NAN_METHOD(Run);

  private:
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
