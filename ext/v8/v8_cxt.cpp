#include "v8_cxt.h"
#include "v8_msg.h"
#include "converters.h"
#include "bridge_ruby.h"
#include "bridge_v8.h"
#include <memory>

using namespace v8;
using namespace std;

VALUE v8_Context_New(int argc, VALUE *argv, VALUE self) {
  HandleScope handles;
  VALUE scope;
  rb_scan_args(argc,argv, "01", &scope);
  if (NIL_P(scope)) {
    return V8_Ref_Create(self, Context::New());
  } else {
    Local<ObjectTemplate> t = V8_Ref_Get<ObjectTemplate>(scope);    
    return V8_Ref_Create(self, Context::New(0, t));
  }
}

VALUE v8_cxt_Global(VALUE self) {
  HandleScope handles;
  convert_v8_to_rb_t v82rb;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Local<Value> global = *cxt->Global();
  return v82rb(global);
}

VALUE v8_cxt_open(VALUE self) {
  HandleScope handles;
  TryCatch exceptions;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Context::Scope enter(cxt);
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
  
  auto_ptr<const BridgeObject> source_br(rb2br(source));
  
  V8Local local;
  source_br->accept(local);
  std::string script_str = source_br->toString();
  
  Local<Value> source_str = local.getResult();
  Local<Script> script = Script::Compile(source_str->ToString());
  Local<Value> result = script->Run();
  return V82RB(result);
}


