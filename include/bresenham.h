#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void bresenham(int x1, int y1, int z1,
               int x2, int y2, int z2,
               void (*func)(int x, int y, int z));

#ifdef __cplusplus
}
#endif
