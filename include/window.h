#pragma once

namespace window {
  extern float width;
  extern float height;
}

#ifdef __cplusplus
extern "C" {
#endif
  void update_window(int width, int height);
#ifdef __cplusplus
}
#endif
