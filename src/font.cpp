#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "directxmath/directxmath.h"
#include "glad/gl.h"
#include "opengl.h"

#include "font.h"

namespace font {

  struct location {
    struct {
      unsigned int transform;
      unsigned int texture_sampler;
      unsigned int cell;
      unsigned int glyph;
    } uniform;
  };

  static location location;

  static unsigned int font_program = -1;

  static unsigned int vertex_array_object = -1;
  static unsigned int index_buffer = -1;

  void load_element_buffer()
  {
    uint8_t const data[] = {
      1, 0, 2, 3,
    };
    int const data_size = (sizeof (data));

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vertex_array_object);
  }

  void load_shader()
  {
    unsigned int program = compile_from_files("shader/font.vert",
                                              NULL, // geom
                                              "shader/font.frag");

    location.uniform.transform = glGetUniformLocation(program, "Transform");
    location.uniform.texture_sampler = glGetUniformLocation(program, "TextureSampler");
    location.uniform.cell = glGetUniformLocation(program, "Cell");
    location.uniform.glyph = glGetUniformLocation(program, "Glyph");
    printf("font uniforms:\n  transform %u\n  texture_sampler %u\n  cell %u\n  glyph %u\n",
           location.uniform.transform,
           location.uniform.texture_sampler,
           location.uniform.cell,
           location.uniform.glyph
           );

    font_program = program;
  }

  font load_font(font_desc const& desc)
  {
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int texture_data_size;
    void * texture_data = read_file(desc.path, &texture_data_size);
    assert(texture_data != nullptr);

    int width = desc.texture_width;
    int height = desc.texture_height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture_data);

    free(texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return (font){
      .desc = &desc,
      .texture = texture,
      .stride = desc.texture_width / desc.glyph_width,
      .cell = { (float)desc.glyph_width / (float)desc.texture_width,
                (float)desc.glyph_height / (float)desc.texture_height },
    };
  }

  inline static XMFLOAT2 glyph_coordinate(font const& font, int ord)
  {
    int c = ord - 32;
    int x = c % font.stride;
    int y = c / font.stride;
    XMVECTOR coord = XMVectorSet(x, y, 0, 0);
    XMFLOAT2 coordf;
    XMStoreFloat2(&coordf, coord);
    return coordf;
  }

  inline static XMFLOAT4X4 glyph_transform(font const& font, int x, int y)
  {
    XMMATRIX transform =
      XMMatrixScaling(font.desc->glyph_width, font.desc->glyph_height, 0)
      * XMMatrixTranslation(x, -y, 0)
      * XMMatrixScaling(2.0f / 1024.0f, 2.0f / 1024.0f, 0)
      * XMMatrixTranslation(-1, 1, 0);
    XMFLOAT4X4 transformf;
    XMStoreFloat4x4(&transformf, transform);
    return transformf;
  }

  void draw_string(font const& font, char const * const s, int x, int y)
  {
    glUseProgram(font_program);
    glDepthFunc(GL_ALWAYS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.texture);

    glUniform1i(location.uniform.texture_sampler, 0);
    glUniform2fv(location.uniform.cell, 1, (float *)&font.cell);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    int i = 0;
    while (s[i] != 0) {
      char c = s[i];
      if (c <= 0x20 || c > 0x7f)
        continue;

      XMFLOAT4X4 transform = glyph_transform(font, x, y);
      glUniformMatrix4fv(location.uniform.transform, 1, GL_FALSE, (float *)&transform);
      XMFLOAT2 glyph = glyph_coordinate(font, c);
      glUniform2fv(location.uniform.glyph, 1, (float *)&glyph);

      glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);

      x += font.desc->glyph_width;

      i += 1;
    }
  }
}
