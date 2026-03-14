#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  void load(const char * source_path);
  void draw();
  void update_keyboard(int up, int down, int left, int right,
                       int w, int s, int a, int d);
  void update_mouse(int x, int y);
  void update_joystick(int joystick_index,
                       float lx, float ly, float rx, float ry, float tl, float tr,
                       int up, int down, int left, int right,
                       int a, int b, int x, int y,
                       int leftshoulder, int rightshoulder,
                       int start);
  void update(float time);

#ifdef __cplusplus
}
#endif
