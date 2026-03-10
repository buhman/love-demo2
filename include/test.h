#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  void load(const char * source_path);
  void draw();
  void kb_update(int up, int down, int left, int right);
  void update(float lx, float ly, float rx, float ry, float tl, float tr,
              int up, int down, int left, int right,
              int a, int b, int x, int y,
              int leftshoulder, int rightshoulder);

#ifdef __cplusplus
}
#endif
