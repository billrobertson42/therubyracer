#ifndef BRIDGE_RUBY_TYPES_H_OX4ZG25S
#define BRIDGE_RUBY_TYPES_H_OX4ZG25S

#include "bridge_types.h"
#include <ruby.h>

/**
 * Convert a ruby VALUE into a BridgeType
 */
const BridgeType* rb2bt(VALUE value);

/**
 * Convert a BridgeType into a Ruby Value. (uses RubyValue class).
 */
VALUE bt2rb(const BridgeType* bt);

/**
 * Convert a BridgeType into a Ruby Value.
 */
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

/**
 * Encapsulate mechanics for calling a ruby function.
 */ 
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

/**
 * Objects referenced by Ruby should extend this class
 */
class RubyRefable {
public:
  /**
   * Mark is called when the Ruby GC marks the object.  Ruby objects
   * have an added step in their life-cycle, where apparently they
   * are supposed to give up any other objects that would be eligible
   * for garbage collection.
   *
   * The default implementation does nothing.
   */
  virtual void mark();  
  virtual ~RubyRefable();
};

/**
 * Associate a BridgeObject with the Ruby VM
 */
VALUE associateWithRuby(VALUE ruby_class, const RubyRefable* rr);

/**
 * Retrieve a BridgeObject based on Ruby VM handle
 */
const RubyRefable* getAssociatedObjectFromRuby(VALUE handle);


#endif /* end of include guard: BRIDGE_RUBY_TYPES_H_OX4ZG25S */
