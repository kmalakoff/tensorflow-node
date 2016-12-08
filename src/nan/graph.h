#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include <nan.h>

namespace tensorflow { class Graph; }

namespace nan {

class Graph: public Nan::ObjectWrap {
  public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

    Graph();
    ~Graph();
    tensorflow::Graph* m_graph;

    static void Placeholder(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void ScalarConst(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void Add(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void Run(const Nan::FunctionCallbackInfo<v8::Value>& args);
};

}

#endif // NAN_GRAPH_H
