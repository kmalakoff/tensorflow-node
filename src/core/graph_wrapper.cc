#include "graph_wrapper.h"
#include "graph.h"
#include "tensorflow/c/c_api.h"
#include "operation_wrapper.h"
#include "operation.h"

// v8::Handle<v8::Object> WrapOperation(TF_Operation *operation) {
//   Nan::HandleScope scope;

//   v8::Local<v8::ObjectTemplate> class_templ = v8::ObjectTemplate::New(v8::Isolate::GetCurrent());
//   v8::Handle<v8::ObjectTemplate> inst_templ = class_templ->InstanceTemplate();
//   inst_templ->SetInternalFieldCount(1);

//   v8::Persistent<v8::ObjectTemplate> object_templ = v8::Persistent<v8::ObjectTemplate>::New(v8::Isolate::GetCurrent(), class_templ)
//   v8::Handle<v8::Object> result = object_templ->NewInstance();
//   v8::Handle<Nan::External> class_ptr = Nan::External::New(operation); 
//   result->SetInternalField(0, class_ptr);
//   return scope.Escape(result);
// }

Nan::Persistent<v8::Function> GraphWrapper::constructor;

GraphWrapper::GraphWrapper() { m_graph = new Graph(); }
GraphWrapper::~GraphWrapper() {}

void GraphWrapper::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Graph").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "Placeholder", Placeholder);
  Nan::SetPrototypeMethod(tpl, "ScalarConst", ScalarConst);
  Nan::SetPrototypeMethod(tpl, "Add", Add);
  Nan::SetPrototypeMethod(tpl, "Run", Run);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Graph").ToLocalChecked(), tpl->GetFunction());
}

void GraphWrapper::New(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new GraphWrapper(...)`
    GraphWrapper* obj = new GraphWrapper();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    args.GetReturnValue().Set(cons->NewInstance(0, {}));
  }
}

void GraphWrapper::Placeholder(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  GraphWrapper* obj = ObjectWrap::Unwrap<GraphWrapper>(args.Holder());
  TF_Operation* result = obj->m_graph->Placeholder();
  
  v8::Local<v8::Object> n = Nan::New(OperationWrapper::constructor)->GetFunction()->NewInstance();
  OperationWrapper *i = new OperationWrapper(result);
  i->DoWrap(n);
  args.GetReturnValue().Set(n);
}

void GraphWrapper::ScalarConst(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  GraphWrapper* obj = ObjectWrap::Unwrap<GraphWrapper>(args.Holder());
  int arg0 = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  TF_Operation* result = obj->m_graph->ScalarConst(arg0);
  v8::Local<v8::Object> n = Nan::New(OperationWrapper::constructor)->GetFunction()->NewInstance();
  OperationWrapper *i = new OperationWrapper(result);
  i->DoWrap(n);
  args.GetReturnValue().Set(n);
}

void GraphWrapper::Add(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  GraphWrapper* obj = ObjectWrap::Unwrap<GraphWrapper>(args.Holder());
  TF_Operation* arg0 = Nan::ObjectWrap::Unwrap<OperationWrapper>(args[0]->ToObject())->m_operation;
  TF_Operation* arg1 = Nan::ObjectWrap::Unwrap<OperationWrapper>(args[1]->ToObject())->m_operation;

  TF_Operation* result = obj->m_graph->Add(arg0, arg1);
  v8::Local<v8::Object> n = Nan::New(OperationWrapper::constructor)->GetFunction()->NewInstance();
  OperationWrapper *i = new OperationWrapper(result);
  i->DoWrap(n);
  args.GetReturnValue().Set(n);
}

void GraphWrapper::Run(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  GraphWrapper* obj = ObjectWrap::Unwrap<GraphWrapper>(args.Holder());
  int arg0 = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  args.GetReturnValue().Set(Nan::New(obj->m_graph->Run(arg0)));
}
