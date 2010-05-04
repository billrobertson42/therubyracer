#ifndef _RUBY_V8_OBJECT_
#define _RUBY_V8_OBJECT_ 

#include "ruby.h"
#include "v8.h"

extern VALUE V8_C_object;

VALUE v8_object_new(VALUE clazz);
VALUE v8_object_get(VALUE self, VALUE key);
VALUE v8_object_get_from_handle(v8::Local<v8::Object>& obj, VALUE key);
VALUE v8_object_set(VALUE self, VALUE key, VALUE value);
VALUE v8_object_set_from_handle(v8::Local<v8::Object>& obj, VALUE key, VALUE value);
VALUE v8_object_get_property_names(VALUE self);
VALUE v8_object_context(VALUE self);
VALUE v8_object_to_string(VALUE self);
#endif