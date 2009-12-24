#include "bridge_v8.h"
#include <v8.h>

const BridgeType* v82bt(v8::Handle<v8::Value>& value) {
  if (value.IsEmpty()) {
    return new BridgeNull;
  }

  if (value->IsUndefined()) {
    return new BridgeNull;
  }

  if(value->IsNull()) {
    return new BridgeNull;
  }
  
  if(value->IsTrue()) {
    return new BridgeBoolean(true);
  }

  if(value->IsFalse()) {
    return new BridgeBoolean(false);
  }

  if(value->IsString()) {
    v8::Local<v8::String> str = value->ToString();
    char buffer[1024];
    int strlen = str->Length();
    std::string output(strlen, 0);
    for (int total = 0; total < strlen;) {
      int written = str->WriteAscii(buffer, total, 1024);
      output.replace(total, written, buffer);
      total += written;
    }
    return new BridgeString(output);
  }

  if(value->IsInt32()) {
    return new BridgeInt(value->Int32Value());
  }

  if(value->IsNumber()) {
    return new BridgeDouble(value->NumberValue());
  }
  
  if (value->IsObject()) {
    v8::Local<v8::Object> object(v8::Object::Cast(*value));
//    return dest.pushObject(object);
  }
  
  return new BridgeUndefined;
  
}


void V8Value::visit(const BridgeDouble* bd) {
  result = v8::Local<v8::Value>::New(v8::Number::New(bd->getValue()));
}

void V8Value::visit(const BridgeInt* bi) {
  result = v8::Local<v8::Value>::New(v8::Integer::New(bi->getValue()));
}

void V8Value::visit(const BridgeBoolean* bb) {
  result = v8::Local<v8::Value>::New(v8::Boolean::New(bb->getValue()));
}

void V8Value::visit(const BridgeString* bs) {
  result = v8::Local<v8::Value>::New(v8::String::New(bs->getValue().c_str()));
}

void V8Value::visit(const BridgeNull* bn) {
  result = v8::Local<v8::Value>::New(v8::Null());
}

void V8Value::visit(const BridgeUndefined* bu) {
  result = v8::Local<v8::Value>::New(v8::Undefined());
}

void V8Value::visit(const BridgeFunction* bu) {
  result = v8::Local<v8::Value>::New(v8::Undefined());
}

void V8Value::visit(const BridgeObject* bo) {
  result = v8::Local<v8::Value>::New(v8::Undefined());
}

V8Value::~V8Value() {
}
