#ifndef NAN_SESSION_H
#define NAN_SESSION_H

#include "../../lib/nan.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/public/session.h"

// forward declarations
namespace addons { class Graph; }

namespace addons {

class Session: public Nan::ObjectWrap {
  public:
    Session(Graph* graph);
    ~Session();

    v8::Local<v8::Value> ToValue() {
      // const int argc = 1;
      // v8::Local<v8::Value> argv[argc] = {Nan::New(this->m_ref)};
      // v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Session::constructor)->GetFunction(), argc, argv).ToLocalChecked();
      v8::Local<v8::Object> result = Nan::NewInstance(Nan::New(Session::constructor)->GetFunction()).ToLocalChecked();
      this->Wrap(result);
      return result;
    }

    static void run(tensorflow::Session* session, const Nan::FunctionCallbackInfo<v8::Value>& info);

  private:
    tensorflow::Session* m_session;
    tensorflow::Scope m_scope;

  public:
    static NAN_MODULE_INIT(Init);
  private:
    static NAN_CONSTRUCTOR(constructor);
    static NAN_NEW(New);
    static NAN_METHOD(run);
};

} // namespace addons

#endif // NAN_SESSION_H
