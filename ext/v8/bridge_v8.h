#ifndef BRIDGE_V8_H_5WYPG904
#define BRIDGE_V8_H_5WYPG904

#include "bridge_types.h"
#include <v8.h>

class V8Local : public BridgeVisitor {
  
  v8::Local<v8::Value> result;
  
public:
  
  v8::Local<v8::Value> getResult() {return result;}
  
  virtual void visit(const BridgeDouble* bd) = 0;
  virtual void visit(const BridgeInt* bi) = 0;
  virtual void visit(const BridgeBoolean* bb) = 0;
  virtual void visit(const BridgeString* bs) = 0;
  virtual void visit(const BridgeNull* bn) = 0;
  virtual void visit(const BridgeUndefined* bu) = 0;
  virtual ~V8Local();
};


#endif /* end of include guard: BRIDGE_V8_H_5WYPG904 */
