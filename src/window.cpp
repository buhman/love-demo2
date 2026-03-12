#include "window.h"

namespace window {
  float width = 1;
  float height = 1;
}

// C ABI called from Lua
void update_window(int width, int height)
{
  window::width = width;
  window::height = height;
}
