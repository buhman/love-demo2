#pragma once

#include "world/world.h"

namespace minecraft {
  extern world::state * current_world;

  void load();
  void draw();
}
