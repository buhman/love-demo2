#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  void load(const char * source_path);
  void draw();
  void update(float lx, float ly, float rx, float ry, float tl, float tr,
              int up, int down, int left, int right,
              int a, int b, int x, int y);

#ifdef __cplusplus
}
#endif
