#include "v8_cxt.h"
#include "v8_msg.h"
#include "bridge_rv.h"

#include "v8.h"
#include "v8_ref.h"

#include <cstdio>

using namespace v8;
using namespace std;

VALUE V8__C__Context;

RacerContext::RacerContext(v8::Handle<Context> handl) : handle(handl) {}
RacerContext::~RacerContext() {
  handle.Dispose();
}

VALUE v8_ctx_new(int argc, VALUE *argv, VALUE self) {
  HandleScope handles;
  VALUE scope;
  rb_scan_args(argc,argv, "01", &scope);
  if (NIL_P(scope)) {
    printf("%s:%d new context\n", __FILE__, __LINE__);
    return associateWithRuby(V8__C__Context, new RacerContext(Context::New()));
  } else {
    printf("%s:%d new context\n", __FILE__, __LINE__);
    Local<ObjectTemplate> t = V8_Ref_Get<ObjectTemplate>(scope);    
    return associateWithRuby(V8__C__Context, new RacerContext(Context::New(0, t)));
  }
}

VALUE v8_ctx_global(VALUE self) {
  HandleScope handles;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Local<Value> global = *cxt->Global();
  VALUE glob = v82ruby(global);
  int isNil = TYPE(glob) == T_NIL;
  printf("%s:%d nil? %d\n", __FILE__, __LINE__, isNil);  
  return glob;
}

VALUE v8_cxt_open(VALUE self) {
  HandleScope handles;
  TryCatch exceptions;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Context::Scope enter(cxt);
  printf("%s:%d open context\n", __FILE__, __LINE__);
  if (rb_block_given_p()) {
    VALUE result = rb_yield(self);
    if (exceptions.HasCaught()) {
      return V8_Wrap_Message(exceptions.Message());
    } else {
      return result;
    }
    return result;
  } else {
    return Qnil;
  }
}

VALUE v8_cxt_eval(VALUE self, VALUE source) {
  HandleScope handles;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Context::Scope enter(cxt);
    
  Local<Value> source_val = ruby2v8(source);
  Local<Script> script = Script::Compile(source_val->ToString());
  Local<Value> result = script->Run();
  return v82ruby(result);
}


