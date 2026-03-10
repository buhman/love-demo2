#include <stdlib.h>
#include "bresenham.h"

void bresenham(int x1, int y1, int z1,
               int x2, int y2, int z2,
               void (*func)(int x, int y, int z))
{
  int pt_x = x1;
  int pt_y = y1;
  int pt_z = z1;

  int dx = x2 - x1;
  int dy = y2 - y1;
  int dz = z2 - z1;
  int x_inc = (dx < 0) ? -1 : 1;
  int y_inc = (dy < 0) ? -1 : 1;
  int z_inc = (dz < 0) ? -1 : 1;
  int l = abs(dx);
  int m = abs(dy);
  int n = abs(dz);
  int dx2 = l << 1;
  int dy2 = m << 1;
  int dz2 = n << 1;

  if ((l >= m) && (l >= n)) {
    int err_1 = dy2 - l;
    int err_2 = dz2 - l;
    for (int i = 0; i < l; i++) {
      func(pt_x, pt_y, pt_z);
      if (err_1 > 0) {
        pt_y += y_inc;
        err_1 -= dx2;
      }
      if (err_2 > 0) {
        pt_z += z_inc;
        err_2 -= dx2;
      }
      err_1 += dy2;
      err_2 += dz2;
      pt_x += x_inc;
    }
  } else if ((m >= l) && (m >= n)) {
    int err_1 = dx2 - m;
    int err_2 = dz2 - m;
    for (int i = 0; i < m; i++) {
      func(pt_x, pt_y, pt_z);
      if (err_1 > 0) {
        pt_x += x_inc;
        err_1 -= dy2;
      }
      if (err_2 > 0) {
        pt_z += z_inc;
        err_2 -= dy2;
      }
      err_1 += dx2;
      err_2 += dz2;
      pt_y += y_inc;
    }
  } else {
    int err_1 = dy2 - n;
    int err_2 = dx2 - n;
    for (int i = 0; i < n; i++) {
      func(pt_x, pt_y, pt_z);
      if (err_1 > 0) {
        pt_y += y_inc;
        err_1 -= dz2;
      }
      if (err_2 > 0) {
        pt_x += x_inc;
        err_2 -= dz2;
      }
      err_1 += dy2;
      err_2 += dx2;
      pt_z += z_inc;
    }
  }
  func(pt_x, pt_y, pt_z);
}
