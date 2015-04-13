#include <node.h>
#include <string>
#include "ArrayBuffer.h"

using namespace v8;

void StringArrayBuffer(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  
  const char *str = "!!!EHLO WORLD!!!";
  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, str);
 
  args.GetReturnValue().Set(buffer->ToArrayBuffer());
}

void CreateArrayBuffer(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  
  std::string str = "Hello World!";  
  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, str);
 
  args.GetReturnValue().Set(buffer->ToArrayBuffer());
}

void PrintWrapped(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  
  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, args[0]);       
  std::string str = buffer->Unwrap<std::string>();

  printf("node::ArrayBuffer: '%s', %zu\n", str.data(), str.length());
}

void PrintArrayBuffer(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();

  node::ArrayBuffer *buffer = node::ArrayBuffer::New(isolate, args[0]);
  
  printf("node::ArrayBuffer: '%s', %zu\n", buffer->ToUtf8(), buffer->Length());
}

void DisposeMemory(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
 
  while(!isolate->IdleNotification(1000));
}

void SampleInit(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  
  exports->Set(String::NewFromUtf8(isolate, "StringArrayBuffer"), 
               FunctionTemplate::New(isolate, StringArrayBuffer)->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "CreateArrayBuffer"), 
               FunctionTemplate::New(isolate, CreateArrayBuffer)->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "PrintWrapped"), 
               FunctionTemplate::New(isolate, PrintWrapped)->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "PrintArrayBuffer"), 
               FunctionTemplate::New(isolate, PrintArrayBuffer)->GetFunction());
               
  exports->Set(String::NewFromUtf8(isolate, "DisposeMemory"), 
               FunctionTemplate::New(isolate, DisposeMemory)->GetFunction());
}

NODE_MODULE(sample, SampleInit);
