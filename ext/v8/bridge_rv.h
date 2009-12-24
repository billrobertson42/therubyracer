#ifndef BRIDGE_RV_H_PTQKOZSO
#define BRIDGE_RV_H_PTQKOZSO

#include <ruby.h>
#include <v8.h>
#include <memory>

/**
 * Simple conversion from a ruby value to a v8 value
 */
v8::Local<v8::Value> ruby2v8(VALUE value);

/**
 * Simple converstion from v8 value to value to ruby value
 */
VALUE v82ruby(v8::Handle<v8::Value>& value);


#endif /* end of include guard: BRIDGE_H_PTQKOZSO */
