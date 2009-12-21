#ifndef BRIDGE_RUBY_TYPES_H_OX4ZG25S
#define BRIDGE_RUBY_TYPES_H_OX4ZG25S

#include "bridge_types.h"
#include <ruby.h>

class RubyToBridge {
public:
  const BridgeObject* create(VALUE value) const;
private:
};

#endif /* end of include guard: BRIDGE_RUBY_TYPES_H_OX4ZG25S */
