#include "bridge_rv.h"
#include "bridge_ruby.h"
#include "bridge_v8.h"

using namespace v8;
using namespace std;

Local<Value> ruby2v8(VALUE value) {
  const BridgeType* bt = rb2bt(value);
  V8Value v8Val;
  bt->accept(v8Val);
  Local<Value> result = v8Val.getResult();
  if(!bt->isExternallyManaged()) {
    delete bt;
  }
  return result;
}

VALUE v82ruby(v8::Handle<v8::Value>& value) {
  const BridgeType* bt = v82bt(value);
  RubyValue rbVal;
  bt->accept(rbVal);
  VALUE result = rbVal.getResult();
  if(!bt->isExternallyManaged()) {
    delete bt;
  }
  return result;
}

