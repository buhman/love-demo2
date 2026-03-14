#pragma once

namespace collision_scene {
  void load();
  void draw();
  void update(int up, int down, int left, int right,
              int w, int s, int a, int d);
}
