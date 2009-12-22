#include "bridge_types.h"

using namespace std;

namespace {
    const string TRUE_STR("true");
    const string FALSE_STR("false");
    const string NULL_STR("null");
    const string UNDEF_STR("undefined");
}

BridgeDouble::BridgeDouble(double d) : value(d) {}
BridgeInt::BridgeInt(int i) : value(i) {}
BridgeBoolean::BridgeBoolean(bool b) : value(b) {}
BridgeString::BridgeString(const char* s) : value(s) {}
BridgeString::BridgeString(const string& s) : value(s) {}

BridgeDouble::~BridgeDouble() {}
BridgeInt::~BridgeInt() {}
BridgeBoolean::~BridgeBoolean() {}
BridgeString::~BridgeString() {}
BridgeNull::~BridgeNull() {}
BridgeUndefined::~BridgeUndefined() {}
BridgeFunction::~BridgeFunction() {}
BridgeObject::~BridgeObject() {}

bool BridgeType::isExternallyManaged() const {
  return false;
}

void BridgeDouble::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeInt::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeBoolean::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeString::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeNull::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeUndefined::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeFunction::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

void BridgeObject::accept(BridgeVisitor& visitor ) const {
  visitor.visit(this);
}

string BridgeDouble::toString() const {
  char buffer[64];
  sprintf(buffer, "%g", value);
  string convertedValue(buffer);   
  return convertedValue;
}

string BridgeInt::toString() const {
}

string BridgeBoolean::toString() const {
  return value ? TRUE_STR : FALSE_STR;
}

string BridgeString::toString() const {
  return value;
}

string BridgeNull::toString() const {
  return NULL_STR;
}

string BridgeUndefined::toString() const {
  return UNDEF_STR;
}
