#ifndef NAN_SESSION_H
#define NAN_SESSION_H

#include "../../lib/nan.h"

// forward declarations
struct TF_SessionWithGraph;

// forward declarations
namespace addons { class Graph; }

namespace addons {

class Session: public Nan::ObjectWrap {
  public:
    Session(Graph* graph);
    ~Session();
    TF_SessionWithGraph* ref() { return m_ref; }

    v8::Local<v8::Value> ToValue() {
      // const int argc = 1;
      // v8::Local<v8::Value> argv[argc] = {Nan::New(this->m_ref)};
      // v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Session::constructor)->GetFunction(), argc, argv).ToLocalChecked();
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Session::constructor)->GetFunction()).ToLocalChecked();
      this->Wrap(result);
      return result;
    }

  private:
    TF_SessionWithGraph* m_ref;
    Graph* m_graph; // TODO: safe references

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(run);
    static NAN_METHOD(runNoOut);
};

} // namespace addons

#endif // NAN_SESSION_H
