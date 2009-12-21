#ifndef BRIDGE_RV_H_PTQKOZSO
#define BRIDGE_RV_H_PTQKOZSO

#include <ruby.h>
#include <v8.h>
#include <memory>

/**
 * Simple conversion from a ruby value to a v8 value
 */
v8::Local<v8::Value> ruby2v8(VALUE value);

#endif /* end of include guard: BRIDGE_H_PTQKOZSO */
