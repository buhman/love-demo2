#include "collada/instance_types.h"

namespace collada::animate {
  static inline float fract(float f)
  {
    return f - floorf(f);
  }

  static inline float loop(float f, float n)
  {
    return fract(f / n) * n;
  }

  void animate_node(instance_types::node& node_instance, float t);
}
