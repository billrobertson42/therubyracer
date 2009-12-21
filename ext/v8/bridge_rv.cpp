#include "bridge_rv.h"
#include "bridge_ruby.h"
#include "bridge_v8.h"
#include <memory>

using namespace v8;
using namespace std;

Local<Value> ruby2v8(VALUE value) {
  auto_ptr<const BridgeObject> bo(rb2bo(value));
  V8Value v8Val;
  bo->accept(v8Val);
  return v8Val.getResult();  
}
