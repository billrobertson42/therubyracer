#ifndef TYPES_H_LQN8MURY
#define TYPES_H_LQN8MURY

#include <string>

// forward declare the type clases for the visitor
class BridgeDouble;
class BridgeInt;
class BridgeString;
class BridgeBoolean;
class BridgeNull;
class BridgeUndefined;

class BridgeVisitor {
public:
  virtual void visit(const BridgeDouble* bd) = 0;
  virtual void visit(const BridgeInt* bi) = 0;
  virtual void visit(const BridgeBoolean* bb) = 0;
  virtual void visit(const BridgeString* bs) = 0;
  virtual void visit(const BridgeNull* bn) = 0;
  virtual void visit(const BridgeUndefined* bu) = 0;
  virtual ~BridgeVisitor() {}
};

class BridgeObject {
  virtual void accept(BridgeVisitor& visitor) const = 0;  
};

class BridgeDouble : public BridgeObject {
  const double value;
public:
  BridgeDouble(double x) : value(x) {}
  double getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeDouble() {}
};

class BridgeInt : public BridgeObject {
  const int value;
public:
  BridgeInt(int x) : value(x) {}
  int getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeInt() {}
};

class BridgeBoolean : public BridgeObject {
  const bool value;
public:
  BridgeBoolean(bool x) : value(x) {}
  bool getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeBoolean() {}
};

class BridgeString : public BridgeObject {
  const std::string value;
public:
  BridgeString(const char* x) : value(x) {}
  const std::string& getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeString() {}
};

class BridgeNull : public BridgeObject {
public:
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeNull() {}
};

class BridgeUndefined : public BridgeObject {
public:
  virtual void accept(BridgeVisitor& visitor) const {
    visitor.visit(this);
  }
  virtual ~BridgeUndefined() {}  
};

#endif /* end of include guard: TYPES_H_LQN8MURY */
