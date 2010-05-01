#ifndef _RUBY_V8_CXT_
#define _RUBY_V8_CXT_ 

#include "ruby.h"
#include "v8.h"
#include "v8_ref.h"

extern VALUE rb_cV8;
extern VALUE V8_C_Object;
extern VALUE V8_C_Context;

VALUE v8_cxt_new(int argc, VALUE *argv, VALUE self);
VALUE v8_cxt_eql(VALUE self, VALUE other);
VALUE v8_cxt_get_global_val(VALUE self, VALUE key);
VALUE v8_cxt_set_global_val(VALUE self, VALUE key, VALUE value);

VALUE v8_cxt_enter(VALUE self);
VALUE v8_cxt_eval(VALUE self, VALUE source, VALUE filename);
VALUE v8_cxt_exit(VALUE self);
VALUE v8_cxt_is_entered(VALUE self);

#endif
