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

void RubyValue::visit(const BridgeDouble* bd) {
  result = rb_float_new(bd->getValue());
}

void RubyValue::visit(const BridgeInt* bi) {
  result = INT2FIX(bi->getValue());
}

void RubyValue::visit(const BridgeBoolean* bb) {
  result = bb->getValue() ? Qtrue : Qfalse;
}

void RubyValue::visit(const BridgeString* bs) {
  result = rb_str_new2(bs->getValue().c_str());
}

void RubyValue::visit(const BridgeNull* bn) {
  result = Qnil;
}

void RubyValue::visit(const BridgeUndefined* bu) {
  result = Qnil;
}

// void RubyValue::visit(const BridgeObjectInstance* bo) {
//   result = V8_Ref_Create(V8_C_Object, value);
// }

RubyValue::~RubyValue() {
  
}