#include "v8_cxt.h"
#include "v8_msg.h"
#include "v8_obj.h"
#include "v8_template.h"
#include "converters.h"

using namespace v8;

VALUE V8_C_Context;

//TODO: rename everything to Context_
//TODO: do the object init from within here

VALUE v8_cxt_new(int argc, VALUE *argv, VALUE self) {
  HandleScope handles;
  VALUE scope;
  rb_scan_args(argc,argv, "01", &scope);
  if (NIL_P(scope)) {
    return V8_Ref_Create(self, Context::New());
  } else {
    Persistent<Context> context = Context::New(0, Racer_Create_V8_ObjectTemplate(scope));
    Context::Scope enter(context);
    context->Global()->SetHiddenValue(String::New("TheRubyRacer::RubyObject"), External::Wrap((void *)scope));
    VALUE ref = V8_Ref_Create(self, context, scope);
    context.Dispose();
    return ref;
  }
}

VALUE racer_error_message(TryCatch& exception) {
  VALUE msg = V8_Ref_Create(V8_C_Message, exception.Message());
  Local<Value> stack = exception.StackTrace();
  if (!stack.IsEmpty()) {
    rb_iv_set(msg,"@stack",V82RB(stack));    
  }
  return msg;  
}

VALUE v8_cxt_enter(VALUE self) {
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  printf("v8_cxt_enter: %d\n", __LINE__);
  cxt->Enter();
  return self;
}

VALUE v8_cxt_exit(VALUE self) {
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  printf("v8_cxt_exit: %d\n", __LINE__);
  cxt->Exit();
  return self;
}

VALUE v8_cxt_get_global_val(VALUE self, VALUE key) {
  HandleScope handles;
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  Local<Object> global = *cxt->Global();
  return v8_object_get_from_handle(global, key);
}

VALUE v8_cxt_set_global_val(VALUE self, VALUE key, VALUE value) {
  printf("v8_cxt_set_global_val %d\n", __LINE__);
  HandleScope handles;
  printf("v8_cxt_set_global_val %d\n", __LINE__);
  Local<Context> cxt = V8_Ref_Get<Context>(self);
  printf("v8_cxt_set_global_val %d\n", __LINE__);
  Local<Object> global = cxt->Global();
  printf("v8_cxt_set_global_val %d\n", __LINE__);
  return v8_object_set_from_handle(global, key, value);
}

VALUE v8_cxt_is_entered(VALUE self) {
  return INT2FIX(!Context::GetEntered().IsEmpty()); 
}

VALUE v8_cxt_eval(VALUE self, VALUE source, VALUE filename) {
  HandleScope mustHave;
  printf("v8_cxt_eval: %d\n", __LINE__);
  Handle<Value> source_str = RB2V8(source);
  printf("v8_cxt_eval: %d\n", __LINE__);
  Local<Value> source_name = RTEST(filename) ? RB2V8(filename) : *String::New("<eval>");
  printf("v8_cxt_eval: %d\n", __LINE__);
  Local<Script> script;
  printf("v8_cxt_eval: %d\n", __LINE__);
  {
    printf("v8_cxt_eval: compile\n");
    TryCatch exceptions;
    script = Script::Compile(source_str->ToString(), source_name);
    if (exceptions.HasCaught()) {	  
      return racer_error_message(exceptions);
    }
  } 

  printf("v8_cxt_eval: run\n");
  TryCatch exceptions;
  Local<Value> result = script->Run();
  if (exceptions.HasCaught()) {
    return racer_error_message(exceptions);
  } else {
    return V82RB(result);
  }
}

VALUE v8_cxt_eql(VALUE self, VALUE other) {
  if (RTEST(CLASS_OF(other) != V8_C_Context)) {
    return Qnil;
  } else {
    Local<Context> cxt = V8_Ref_Get<Context>(self);
    Local<Context> that = V8_Ref_Get<Context>(other);
    return cxt == that ? Qtrue : Qfalse;
  }
  return Qnil;
}
