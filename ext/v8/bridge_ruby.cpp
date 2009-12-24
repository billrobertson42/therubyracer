#include "bridge_ruby.h"

const BridgeType* rb2bt(VALUE value) {
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

VALUE bt2rb(const BridgeType* bt) {
  RubyValue value;
  bt->accept(value);
  return value.getResult();
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

void RubyValue::visit(const BridgeFunction* bu) {
  result = Qnil;
}

void RubyValue::visit(const BridgeObject* bf) {
  result = Qnil;
}

// void RubyValue::visit(const BridgeTypeInstance* bo) {
//   result = V8_Ref_Create(V8_C_Object, value);
// }

RubyValue::~RubyValue() {
   
}

RubyFunction::RubyFunction(VALUE val) : functionHandle(val) {
  
}

bool RubyFunction::isExternallyManaged() const {
  return true;
}

std::string RubyFunction::toString() const {
  return "Ruby Function";
}

void RubyFunction::accept(BridgeVisitor& visitor) const {
  visitor.visit(this);
}

const BridgeType* RubyFunction::invoke(int argc, const BridgeType** argv) const {
  VALUE* arguments = new VALUE[argc];
  
  for(int c=0;c<argc; ++c) {
    arguments[c] = bt2rb(argv[c]);
  }
    
  VALUE result = rb_funcall2(functionHandle, rb_intern("call"), argc, arguments);
  delete [] arguments;
  
  const BridgeType* convertedResult = rb2bt(result);
  return convertedResult;
}

RubyFunction::~RubyFunction() {
  
}

RubyRefable::~RubyRefable() {
}

void RubyRefable::mark() {
  
}

static void markWrapperObject(RubyRefable* objectToMark) {
  objectToMark->mark();
}

static void freeWrapperObject(RubyRefable* objectToDelete) {
  delete objectToDelete;
}

VALUE associateWithRuby(VALUE ruby_class, const RubyRefable* object) {
  return Data_Wrap_Struct(ruby_class, markWrapperObject, freeWrapperObject, (void*)object);
}

const RubyRefable* getAssociatedObjectFromRuby(VALUE handle) {
  return 0; 
}
