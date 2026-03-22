#pragma once

#include "declarations.h"

namespace window {
  extern float width;
  extern float height;
}

#ifdef __cplusplus
extern "C" {
#endif
  EXPORT void DECL update_window(int width, int height);
#ifdef __cplusplus
}
#endif
