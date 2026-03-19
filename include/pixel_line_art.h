#pragma once

namespace pixel_line_art {

  void load();

  void draw_line_quad_start();
  void draw_line(int x1, int y1, int x2, int y2);
  void draw_set_color(float r, float g, float b);
  void draw_quad(int x1, int y1, int x2, int y2,
                 int x3, int y3, int x4, int y4);
}
