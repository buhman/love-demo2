#pragma once

#include "declarations.h"

#ifdef __cplusplus
extern "C" {
#endif

  EXPORT void DECL load(const char * source_path);
  EXPORT void DECL draw();
  EXPORT void DECL love2d_state_load();
  EXPORT void DECL love2d_state_restore();
  EXPORT void DECL update_keyboard(int up, int down, int left, int right,
				   int w, int s, int a, int d,
				   int t, int g, int f, int h,
				   int i, int k, int j, int l);
  EXPORT void DECL update_mouse(int x, int y);
  EXPORT void DECL update_joystick(int joystick_index,
				   float lx, float ly, float rx, float ry, float tl, float tr,
				   int up, int down, int left, int right,
				   int a, int b, int x, int y,
				   int leftshoulder, int rightshoulder,
				   int start);
  EXPORT void DECL update(float time);

#ifdef __cplusplus
}
#endif
