#include "bridge_ruby.h"

const BridgeObject* rb2bo(VALUE value) {
  switch (TYPE(value)) {
  case T_FIXNUM:
    return new BridgeInt(FIX2INT(value));
  case T_FLOAT:
    return new BridgeDouble(NUM2DBL(value));
  case T_STRING:
    return new BridgeString(RSTRING(value)->ptr);
  case T_NIL:
    return new BridgeNull;
  case T_TRUE:
    return new BridgeBoolean(true);
  case T_FALSE:
    return new BridgeBoolean(false);
    
  // case T_DATA:
  //   VALUE clsProc = rb_eval("::Proc");
  //   VALUE clsMethod = rb_eval("::Method");
  //   VALUE smartMatch = rb_intern("===");
  //   if (RTEST(rb_funcall(clsProc, smartMatch, value)) || RTEST(rbfuncall(clsMethod, smartMatch, value))) {
  //     
  //   }
  }
  return new BridgeUndefined;
}