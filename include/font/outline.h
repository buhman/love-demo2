#pragma once

#include "outline_types.h"

namespace font::outline {

  struct font_desc {
    char const * const path;
  };

  font_desc const uncial_antiqua[] = {
    {
      .path = "font/outline/uncial_antiqua_36.data",
    },
  };
  int const uncial_antiqua_length = (sizeof (uncial_antiqua)) / (sizeof (font_desc));

  struct font {
    unsigned int texture;
    types::font const * font;
    types::glyph const * glyphs;
  };

  void load_shader();
  void load_fonts(font * const fonts, font_desc const * const descs, int length);

  void draw_start(font const& font, unsigned int vertex_array_object, unsigned int index_buffer);
  int draw_string(font const& font, char const * const s, int x, int y);
}
