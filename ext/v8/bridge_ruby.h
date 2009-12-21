#ifndef BRIDGE_RUBY_TYPES_H_OX4ZG25S
#define BRIDGE_RUBY_TYPES_H_OX4ZG25S

#include "bridge_types.h"
#include <ruby.h>

const BridgeObject* rb2bo(VALUE value);

class RubyValue : public BridgeVisitor {
  
  VALUE result;
  
public:
  
  VALUE getResult() {return result;}
  
  virtual void visit(const BridgeDouble* bd);
  virtual void visit(const BridgeInt* bi);
  virtual void visit(const BridgeBoolean* bb);
  virtual void visit(const BridgeString* bs);
  virtual void visit(const BridgeNull* bn);
  virtual void visit(const BridgeUndefined* bu);
  virtual ~RubyValue();
};

#endif /* end of include guard: BRIDGE_RUBY_TYPES_H_OX4ZG25S */
