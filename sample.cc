#include <node.h>
#include <string>
#include "ArrayBuffer.h"

using namespace v8;

#if NODE_MINOR_VERSION > 11

void CreateArrayBuffer(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  
  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, "Hello World!");
 
  args.GetReturnValue().Set(buffer->ToArrayBuffer());
}

void PrintArrayBuffer(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();

  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, args[0]);
  
  printf("node::ArrayBuffer: '%s', %zu\n", buffer->ToUtf8(), buffer->Length());
}

void DisposeMemory(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  isolate->LowMemoryNotification();
}

void SampleInit(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  
  exports->Set(String::NewFromUtf8(isolate, "CreateArrayBuffer"), 
               FunctionTemplate::New(isolate, CreateArrayBuffer)->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "PrintArrayBuffer"), 
               FunctionTemplate::New(isolate, PrintArrayBuffer)->GetFunction());
               
  exports->Set(String::NewFromUtf8(isolate, "DisposeMemory"), 
               FunctionTemplate::New(isolate, DisposeMemory)->GetFunction());
}

#else

static Handle<Value> CreateArrayBuffer(const Arguments& args) {
  HandleScope scope;
  node::ArrayBuffer *buffer = node::ArrayBuffer::New("Hello World!");
  return scope.Close(buffer->ToArrayBuffer());
}

static Handle<Value> PrintArrayBuffer(const Arguments& args) {
  HandleScope scope;
  
  node::ArrayBuffer *buffer = node::ArrayBuffer::New(args[0]);
  
  printf("node::ArrayBuffer: '%s', %zu\n", buffer->ToUtf8(), buffer->Length());
  
  return scope.Close(Undefined());
}

static Handle<Value> DisposeMemory(const Arguments& args) {
  HandleScope scope;
  V8::LowMemoryNotification();
  return scope.Close(Undefined());
}

void SampleInit(Handle<Object> exports) {
  HandleScope scope;
  
  exports->Set(String::New("CreateArrayBuffer"), 
               FunctionTemplate::New(CreateArrayBuffer)->GetFunction());
  
  exports->Set(String::New("PrintArrayBuffer"), 
               FunctionTemplate::New(PrintArrayBuffer)->GetFunction());
               
  exports->Set(String::New("DisposeMemory"), 
               FunctionTemplate::New(DisposeMemory)->GetFunction());
}

#endif

NODE_MODULE(sample, SampleInit);
