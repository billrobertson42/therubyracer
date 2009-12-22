#ifndef BRIDGE_V8_H_5WYPG904
#define BRIDGE_V8_H_5WYPG904

#include "bridge_types.h"
#include <v8.h>

const BridgeType* v82bt(v8::Handle<v8::Value>& value);

class V8Value : public BridgeVisitor {
  
  v8::Local<v8::Value> result;
  
public:
  
  v8::Local<v8::Value> getResult() {return result;}
  
  virtual void visit(const BridgeDouble* bd);
  virtual void visit(const BridgeInt* bi);
  virtual void visit(const BridgeBoolean* bb);
  virtual void visit(const BridgeString* bs);
  virtual void visit(const BridgeNull* bn);
  virtual void visit(const BridgeUndefined* bu);
  virtual void visit(const BridgeFunction* bf);
  virtual void visit(const BridgeObject* bo);
  virtual ~V8Value();
};


#endif /* end of include guard: BRIDGE_V8_H_5WYPG904 */
