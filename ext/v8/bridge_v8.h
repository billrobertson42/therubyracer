#ifndef BRIDGE_V8_H_5WYPG904
#define BRIDGE_V8_H_5WYPG904

#include "bridge_types.h"
#include <v8.h>

class V8Local : public BridgeVisitor {
  
  v8::Local<v8::Value> result;
  
public:
  
  v8::Local<v8::Value> getResult() {return result;}
  
  virtual void visit(const BridgeDouble* bd);
  virtual void visit(const BridgeInt* bi);
  virtual void visit(const BridgeBoolean* bb);
  virtual void visit(const BridgeString* bs);
  virtual void visit(const BridgeNull* bn);
  virtual void visit(const BridgeUndefined* bu);
  virtual ~V8Local();
};


#endif /* end of include guard: BRIDGE_V8_H_5WYPG904 */
