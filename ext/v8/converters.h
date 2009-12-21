#ifndef __converters_h__
#define __converters_h__

#include "convert_ruby.h"
#include "convert_string.h"
#include "convert_v8.h"

typedef RubyValueSource<V8LocalDest, v8::Local<v8::Value> > convert_rb_to_v8_t; 
typedef V8HandleSource<RubyValueDest, VALUE> convert_v8_to_rb_t;

typedef RubyValueSource<StringDest, std::string> convert_rb_to_string_t;
typedef V8HandleSource<StringDest, std::string> convert_v8_to_string_t;

static convert_v8_to_rb_t V82RB;
static convert_rb_to_v8_t RB2V8;

#endif