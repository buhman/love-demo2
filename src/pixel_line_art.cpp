#include "glad/gl.h"
#include "directxmath/directxmath.h"
#include <stdio.h>

#include "opengl.h"
#include "window.h"

#include "pixel_line_art.h"

extern unsigned int quad_index_buffer;

namespace pixel_line_art {

  struct layout {
    struct {
      unsigned int position;
    } attribute;
    struct {
      unsigned int transform;
      unsigned int base_color;
    } uniform;
  };

  const layout layout = {
    .attribute = {
      .position = 0,
    },
    .uniform = {
      .transform = 0,
      .base_color = 1,
    },
  };

  static unsigned int program;

  static unsigned int vertex_array_object;
  static unsigned int per_vertex_buffer;
  static int const per_vertex_size = (sizeof (float)) * 2;

  static void load_program()
  {
    program = compile_from_files("shader/pixel_line_art.vert",
                                 nullptr,
                                 "shader/pixel_line_art.frag");
  }

  static void load_vertex_attributes()
  {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glVertexBindingDivisor(0, 0);

    glEnableVertexAttribArray(layout.attribute.position);
    glVertexAttribFormat(layout.attribute.position, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(layout.attribute.position, 0);

    glBindVertexArray(0);
  }

  static void load_per_vertex_buffer(int x1, int y1, int x2, int y2)
  {
    float vertex_data[] = {
      (float)x1, (float)y1, (float)x2, (float)y2,
    };
    int vertex_data_size = (sizeof (vertex_data));

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  static void load_per_vertex_buffer2(int x1, int y1, int x2, int y2,
                                      int x3, int y3, int x4, int y4)
  {
    float vertex_data[] = {
      (float)x1, (float)y1, (float)x2, (float)y2,
      (float)x3, (float)y3, (float)x4, (float)y4,
    };
    int vertex_data_size = (sizeof (vertex_data));

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load()
  {
    load_program();
    load_vertex_attributes();

    glGenBuffers(1, &per_vertex_buffer);
  }

  static void set_transform(XMMATRIX const & transform)
  {
    XMFLOAT4X4 float_transform;
    XMStoreFloat4x4(&float_transform, transform);
    glUniformMatrix4fv(layout.uniform.transform, 1, false, (float *)&float_transform);
  }

  void draw_line_quad_start()
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glBindVertexArray(vertex_array_object);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

    XMMATRIX transform
      = XMMatrixScaling(2.0f / window::width, -2.0f / window::height, 0)
      * XMMatrixTranslation(-1, 1, 0);
    set_transform(transform);
  }

  void draw_line(int x1, int y1, int x2, int y2)
  {
    load_per_vertex_buffer(x1, y1, x2, y2);
    glDrawArrays(GL_LINES, 0, 2);
  }

  void draw_quad(int x1, int y1, int x2, int y2,
                 int x3, int y3, int x4, int y4)
  {
    load_per_vertex_buffer2(x1, y1, x2, y2,
                            x3, y3, x4, y4);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);
  }

  void draw_set_color(float r, float g, float b)
  {
    glUniform3f(layout.uniform.base_color, r, g, b);
  }
}
