#ifndef NAN_GRAPH_H
#define NAN_GRAPH_H

#include "index.h"

// forward declarations
namespace tensorflow { class Graph; }

namespace addons {

class Graph: public Nan::ObjectWrap {
  public:
    Graph();
    ~Graph();
    tensorflow::Graph* ref() { return m_ref; }

    v8::Local<v8::Value> ToValue() {
      // const int argc = 1;
      // v8::Local<v8::Value> argv[argc] = {Nan::New(this->m_ref)};
      // v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Graph::constructor)->GetFunction(), argc, argv).ToLocalChecked();
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Graph::constructor)->GetFunction()).ToLocalChecked();
      this->Wrap(result);
      return result;
    }

  private:
    tensorflow::Graph* m_ref;

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(placeholder);
    static NAN_METHOD(variable);
    static NAN_METHOD(constant);
    static NAN_METHOD(run);
};

}

#endif // NAN_GRAPH_H
