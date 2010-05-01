#include "v8_obj.h"
#include "v8_ref.h"
#include "converters.h"

using namespace v8;

#include <cstdio>

VALUE V8_C_Object;

namespace {
  Local<Object> unwrap(VALUE robj) {
    return V8_Ref_Get<Object>(robj);
  }
}

VALUE v8_object_new(VALUE clazz) {
  HandleScope handles;
  return V8_Ref_Create(clazz, Object::New());
}

VALUE v8_object_get(VALUE self, VALUE key) {
  HandleScope handles;  
  printf("v8_object_get: %d\n", __LINE__);
  Local<Object> obj = unwrap(self);
  printf("v8_object_get: %d\n", __LINE__);
  return v8_object_get_from_handle(obj, key);
}

VALUE v8_object_get_from_handle(Local<Object>& obj, VALUE key) {
  VALUE keystr = rb_str_to_str(key);
  Local<Value> value = obj->Get(RB2V8(keystr));
  return V82RB(value);
}

VALUE v8_object_set(VALUE self, VALUE key, VALUE value) {
  HandleScope handles;
  Local<Object> obj = unwrap(self);
  return v8_object_set_from_handle(obj, key, value);
}

VALUE v8_object_set_from_handle(Local<Object>& obj, VALUE key, VALUE value) {
  VALUE keystr = rb_funcall(key, rb_intern("to_s"), 0);
  obj->Set(RB2V8(keystr), RB2V8(value));
  return Qnil;
}

VALUE v8_object_get_property_names(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);  
  Local<Value> names = object->GetPropertyNames();
  return V82RB(names);
}

VALUE v8_object_context(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);
  Local<Value> cxt = object->GetHiddenValue(String::New("TheRubyRacer::Context"));
  return cxt.IsEmpty() ? Qnil : (VALUE)External::Unwrap(cxt);
}

VALUE v8_object_to_string(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);
  Local<Value> string = object->ToString();
  return V82RB(string);
}