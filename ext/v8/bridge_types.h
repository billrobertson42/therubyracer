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
class BridgeFunction;
class BridgeObject;

class BridgeVisitor {
public:
  virtual void visit(const BridgeDouble* bd) = 0;
  virtual void visit(const BridgeInt* bi) = 0;
  virtual void visit(const BridgeBoolean* bb) = 0;
  virtual void visit(const BridgeString* bs) = 0;
  virtual void visit(const BridgeNull* bn) = 0;
  virtual void visit(const BridgeUndefined* bu) = 0;
  virtual void visit(const BridgeFunction* bf) = 0;
  virtual void visit(const BridgeObject* bo) = 0;
  virtual ~BridgeVisitor() {}
};

class BridgeType {
public:
  virtual std::string toString() const = 0;
  virtual void accept(BridgeVisitor& visitor) const = 0;
  virtual bool isExternallyManaged() const;
};

class BridgeDouble : public BridgeType {
  const double value;
public:
  BridgeDouble(double x);
  virtual std::string toString() const;
  double getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeDouble();
};

class BridgeInt : public BridgeType {
  const int value;
public:
  BridgeInt(int x);
  virtual std::string toString() const;
  int getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeInt();
};

class BridgeBoolean : public BridgeType {
  const bool value;
public:
  BridgeBoolean(bool x);
  virtual std::string toString() const;
  bool getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeBoolean();
};

class BridgeString : public BridgeType {
  const std::string value;
public:
  BridgeString(const char* x);
  BridgeString(const std::string& s);
  virtual std::string toString() const;
  const std::string& getValue() const {return value;}
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeString();
};

class BridgeNull : public BridgeType {
public:
  virtual std::string toString() const;
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeNull();
};

class BridgeUndefined : public BridgeType {
public:
  virtual std::string toString() const;
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeUndefined();
};

class BridgeFunction : public BridgeType {
public:
  virtual const BridgeType* invoke(int argc, const BridgeType** argv) const = 0;
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeFunction();
};

class BridgeObject : BridgeType {
public:
  virtual void accept(BridgeVisitor& visitor) const;
  virtual ~BridgeObject();
};

#endif /* end of include guard: TYPES_H_LQN8MURY */
