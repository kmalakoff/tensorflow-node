#ifndef GraphWrapper_H
#define GraphWrapper_H

#include <nan.h>

class Graph;

class GraphWrapper : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);

  private:
    explicit GraphWrapper();
    ~GraphWrapper();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void Placeholder(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void ScalarConst(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void Add(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void Run(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static Nan::Persistent<v8::Function> constructor;
    Graph* m_graph;
};

#endif

