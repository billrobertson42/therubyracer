#include "bridge_v8.h"
#include <v8.h>

void V8Local::visit(const BridgeDouble* bd) {
  result = v8::Local<v8::Value>::New(v8::Number::New(bd->getValue()));
}

void V8Local::visit(const BridgeInt* bi) {
  result = v8::Local<v8::Value>::New(v8::Integer::New(bi->getValue()));
}

void V8Local::visit(const BridgeBoolean* bb) {
  result = v8::Local<v8::Value>::New(v8::Boolean::New(bb->getValue()));
}

void V8Local::visit(const BridgeString* bs) {
  result = v8::Local<v8::Value>::New(v8::String::New(bs->getValue().c_str()));
}

void V8Local::visit(const BridgeNull* bn) {
  result = v8::Local<v8::Value>::New(v8::Null());
}

void V8Local::visit(const BridgeUndefined* bu) {
  result = v8::Local<v8::Value>::New(v8::Undefined());
}

V8Local::~V8Local() {
}