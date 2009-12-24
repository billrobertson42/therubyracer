#ifndef _RUBY_V8_CXT_
#define _RUBY_V8_CXT_ 

#include "ruby.h"
#include "v8.h"
#include "bridge_ruby.h"

extern VALUE rb_cV8;
extern VALUE V8_C_Object;

/**
 * This value holds the class for the native context.  It is initialized in 
 * v8.cpp
 */
extern VALUE V8__C__Context;

VALUE v8_ctx_new(int argc, VALUE *argv, VALUE self);
VALUE v8_ctx_global(VALUE self);
VALUE v8_cxt_open(VALUE self);
VALUE v8_cxt_eval(VALUE self, VALUE source);

class RacerContext : public RubyRefable {
  v8::Persistent<v8::Context> handle;
  
public:
  RacerContext(v8::Handle<v8::Context> handle);
  virtual ~RacerContext();
};

#endif