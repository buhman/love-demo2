#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "directxmath/directxmath.h"
#include "glad/gl.h"
#include "opengl.h"
#include "file.h"

#include "font/outline.h"
#include "font/outline_types.h"
#include "window.h"

namespace font::outline {

  struct layout {
    struct {
      unsigned int transform;
      unsigned int texture_size;
      unsigned int width_height_xy;
      unsigned int texture_sampler;
    } uniform;
  };

  static layout const layout = {
    .uniform = {
      .transform = 0,
      .texture_size = 1,
      .width_height_xy = 2,
      .texture_sampler = 3,
    }
  };

  static unsigned int font_program = -1;

  void load_shader()
  {
    unsigned int program = compile_from_files("shader/font.vert",
                                              NULL, // geom
                                              "shader/font_outline.frag");

    font_program = program;
  }

  static inline font load_font(font_desc const& desc)
  {
    int font_data_size;
    void const * font_data = file::read_file(desc.path, &font_data_size);
    assert(font_data != nullptr);

    types::font * font = (types::font *)font_data;
    types::glyph * glyphs = (types::glyph *)(((ptrdiff_t)font_data) + (sizeof (types::font)));

    void * texture_data = (void *)(((ptrdiff_t)glyphs) + (sizeof (types::glyph)) * font->glyph_count);

    ptrdiff_t font_end = ((ptrdiff_t)font_data) + font_data_size;
    int texture_size = font->texture_width * font->texture_height;
    assert(font_end - ((ptrdiff_t)texture_data) == texture_size);

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int width = font->texture_width;
    int height = font->texture_height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    // font_data intentionally not free'd

    return (outline::font){
      .texture = texture,
      .font = font,
      .glyphs = glyphs,
    };
  }

  void load_fonts(font * const fonts, font_desc const * const descs, int length)
  {
    for (int i = 0; i < length; i++) {
      fonts[i] = load_font(descs[i]);
    }
  }

  void draw_start(font const& font, unsigned int vertex_array_object, unsigned int index_buffer)
  {
    glUseProgram(font_program);
    glDepthFunc(GL_ALWAYS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.texture);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    XMFLOAT2 texture_size = {1.0f / font.font->texture_width, 1.0f / font.font->texture_height};
    glUniform2fv(layout.uniform.texture_size, 1, (float *)&texture_size);
  }

  inline static XMFLOAT4X4 glyph_transform(float width, float height, float x, float y)
  {
    XMMATRIX transform
      = XMMatrixScaling(width, height, 0)
      * XMMatrixTranslation(x, -y, 0)
      * XMMatrixScaling(2.0f / window::width, 2.0f / window::height, 0)
      * XMMatrixTranslation(-1, 1, 0);
    XMFLOAT4X4 transformf;
    XMStoreFloat4x4(&transformf, transform);
    return transformf;
  }

  int draw_string(font const& font, char const * const s, int x, int y)
  {
    int advance = 0;
    const float fp = 1.0f / 64.0f;

    int i = 0;
    while (s[i] != 0) {
      char c = s[i++];

      if (!(c >= 0x20 && c <= 0x7f))
        continue;

      types::glyph const & glyph = font.glyphs[c - 0x20];

      if (c > 0x20 && c <= 0x7f) {
        XMFLOAT4 width_height_xy = {
          (float)glyph.bitmap.width, (float)glyph.bitmap.height,
          (float)glyph.bitmap.x, (float)glyph.bitmap.y,
        };
        XMFLOAT4X4 transform = glyph_transform(glyph.bitmap.width, glyph.bitmap.height,
                                               x + ((float)(advance + glyph.metrics.horiBearingX) * fp),
                                               y - ((float)(glyph.metrics.horiBearingY) * fp));

        glUniform4fv(layout.uniform.width_height_xy, 1, (float *)&width_height_xy);
        glUniformMatrix4fv(layout.uniform.transform, 1, GL_FALSE, (float *)&transform);

        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);
      }

      advance += glyph.metrics.horiAdvance;
    }

    return x + (advance >> 6);
  }
}
