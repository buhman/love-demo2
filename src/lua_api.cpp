#include "font/bitmap.h"
#include "pixel_line_art.h"

#include "lua_api.h"

extern font::bitmap::font * terminus_fonts;
extern unsigned int empty_vertex_array_object;
extern unsigned int quad_index_buffer;

int draw_font_start()
{
  int font_ix = font::bitmap::best_font(font::bitmap::terminus, font::bitmap::terminus_length);
  font::bitmap::font const& ter_best = terminus_fonts[font_ix];
  font::bitmap::draw_start(ter_best, empty_vertex_array_object, quad_index_buffer);
  return font_ix;
}

int draw_font(int font_ix, char const * text, int x, int y)
{
  font::bitmap::font const& ter_best = terminus_fonts[font_ix];
  font::bitmap::draw_string(ter_best, text, x, y);
  return ter_best.desc->glyph_height;
}

void draw_line_quad_start()
{
  pixel_line_art::draw_line_quad_start();
}

void draw_line(int x1, int y1, int x2, int y2)
{
  pixel_line_art::draw_line(x1, y1, x2, y2);
}

void draw_set_color(float r, float g, float b)
{
  pixel_line_art::draw_set_color(r, g, b);
}

void draw_quad(int x1, int y1, int x2, int y2,
               int x3, int y3, int x4, int y4)
{
  pixel_line_art::draw_quad(x1, y1, x2, y2,
                            x3, y3, x4, y4);
}
