#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include <nan.h>

namespace tensorflow { class Graph; }

namespace nan {

class Graph: public Nan::ObjectWrap {
  public:
    Graph();
    ~Graph();
    tensorflow::Graph* ref() { return m_graph; }

    static NAN_METHOD(Placeholder);
    static NAN_METHOD(ScalarConst);
    static NAN_METHOD(Add);
    static NAN_METHOD(Run);

  private:
    friend class AddOns;

    tensorflow::Graph* m_graph;

    /////////////////////////////////
    // Nan Lifecycle
    /////////////////////////////////
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static NAN_MODULE_INIT(Init);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
};

}

#endif // NAN_GRAPH_H
