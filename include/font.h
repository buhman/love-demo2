#pragma once

namespace font {

  struct font_desc {
    char const * const path;
    int const texture_width;
    int const texture_height;
    int const glyph_width;
    int const glyph_height;
  };

  font_desc const ter_6x12 = {
    .path = "font/terminus_128x64_6x12.data",
    .texture_width = 128,
    .texture_height = 64,
    .glyph_width = 6,
    .glyph_height = 12,
  };
  font_desc const ter_8x16 = {
    .path = "font/terminus_128x128_8x16.data",
    .texture_width = 128,
    .texture_height = 128,
    .glyph_width = 8,
    .glyph_height = 16,
  };
  font_desc const ter_10x18 = {
    .path = "font/terminus_256x128_10x18.data",
    .texture_width = 256,
    .texture_height = 128,
    .glyph_width = 10,
    .glyph_height = 18,
  };
  font_desc const ter_12x24 = {
    .path = "font/terminus_256x128_12x24.data",
    .texture_width = 256,
    .texture_height = 128,
    .glyph_width = 12,
    .glyph_height = 24,
  };

  struct font {
    font_desc const * desc;
    unsigned int texture;
    int stride;
    struct {
      float width;
      float height;
    } cell;
  };

  void load_element_buffer();
  void load_shader();
  font load_font(font_desc const& desc);
  void draw_string(font const& font, char const * const s, int x, int y);
}
