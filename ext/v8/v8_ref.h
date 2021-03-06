#ifndef _RUBY_V8_REF_
#define _RUBY_V8_REF_

#include <v8.h>
#include "ruby.h"

//the v8_ref wraps a v8 handle so that ruby can hold a reference to it.

struct v8_ref  {
  //takes a handle object and adds a new persistent handle for 
  //the referenced object
  v8_ref(v8::Handle<void> object, VALUE ref = 0);
  virtual ~v8_ref();
  v8::Persistent<void> handle;
  VALUE references;
};


//memory management
void v8_ref_mark(v8_ref* ref);
void v8_ref_free(v8_ref* ref);

VALUE V8_Ref_Create(VALUE ruby_class, v8::Handle<void> handle, VALUE ref = 0);

template <class T> v8::Local<T> V8_Ref_Get(VALUE object) {
  v8_ref* ref = 0;
  Data_Get_Struct(object, struct v8_ref, ref); 
  return (T *)*ref->handle;  
}

#endif