#ifndef BRIDGE_RUBY_TYPES_H_OX4ZG25S
#define BRIDGE_RUBY_TYPES_H_OX4ZG25S

#include "bridge_types.h"
#include <ruby.h>

const BridgeType* rb2bt(VALUE value);
VALUE bt2rb(const BridgeType* bt);

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
  virtual void visit(const BridgeFunction* bf);
  virtual void visit(const BridgeObject* bf);
  virtual ~RubyValue();
};

class RubyFunction : public BridgeFunction {
  VALUE functionHandle;

public:
  RubyFunction(VALUE handle);
    
  virtual bool isExternallyManaged() const;
  virtual std::string toString() const;
  virtual const BridgeType* invoke(int argc, const BridgeType** argv) const;
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~RubyFunction();
  
};

#endif /* end of include guard: BRIDGE_RUBY_TYPES_H_OX4ZG25S */
