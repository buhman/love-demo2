#pragma once

#include "world/world.h"

namespace minecraft {
  extern world::state * current_world;
  static const int max_world_count = 10;
  extern world::state world_state[max_world_count];

  void load();
  void draw();
}
