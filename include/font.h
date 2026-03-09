#pragma once

namespace font {

  struct font_desc {
    char const * const path;
    int const texture_width;
    int const texture_height;
    int const glyph_width;
    int const glyph_height;
  };

  font_desc const terminus[] = {
    {
      .path = "font/terminus_128x64_6x12.data",
      .texture_width = 128,
      .texture_height = 64,
      .glyph_width = 6,
      .glyph_height = 12,
    },
    {
      .path = "font/terminus_128x128_8x16.data",
      .texture_width = 128,
      .texture_height = 128,
      .glyph_width = 8,
      .glyph_height = 16,
    },
    {
      .path = "font/terminus_256x128_10x18.data",
      .texture_width = 256,
      .texture_height = 128,
      .glyph_width = 10,
      .glyph_height = 18,
    },
    {
      .path = "font/terminus_256x128_12x24.data",
      .texture_width = 256,
      .texture_height = 128,
      .glyph_width = 12,
      .glyph_height = 24,
    },
    {
      .path = "font/terminus_256x256_16x32.data",
      .texture_width = 256,
      .texture_height = 256,
      .glyph_width = 16,
      .glyph_height = 32,
    },
  };
  int const terminus_length = (sizeof (terminus)) / (sizeof (font_desc));

  struct font {
    font_desc const * desc;
    unsigned int texture;
    int stride;
    struct {
      float width;
      float height;
    } cell;
  };

  void load_shader();
  font load_font(font_desc const& desc);
  void load_fonts(font * const fonts, font_desc const * const descs, int length);
  int best_font(font_desc const * const descs, int length);
  void draw_start(font const& font, unsigned int vertex_array_object, unsigned int index_buffer);
  void draw_string(font const& font, char const * const s, int x, int y);
}
