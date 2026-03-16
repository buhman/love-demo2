#include "glad/gl.h"
#include "directxmath/directxmath.h"
#include "opengl.h"
#include "line_art.h"

namespace line_art {

  const float vertex_data[] = {
    // 0: lines
    -1.0, 0.0,  1.0,  0.0, // horizontal, left to right
     0.0, 1.0,  0.0, -1.0, // vertical, top to bottom

    // 4: "cube"
    -1.0,  1.0,  // tl
     1.0,  1.0,  // tr
     1.0, -1.0,  // br
    -1.0, -1.0,  // bl

    // 8: "circle"
     0.000000, -1.000000,
    -0.195090, -0.980785,
    -0.382683, -0.923880,
    -0.555570, -0.831470,
    -0.707107, -0.707107,
    -0.831470, -0.555570,
    -0.923880, -0.382683,
    -0.980785, -0.195090,
    -1.000000,  0.000000,
    -0.980785,  0.195090,
    -0.923880,  0.382683,
    -0.831470,  0.555570,
    -0.707107,  0.707107,
    -0.555570,  0.831470,
    -0.382683,  0.923880,
    -0.195090,  0.980785,
     0.000000,  1.000000,
     0.195090,  0.980785,
     0.382683,  0.923880,
     0.555570,  0.831470,
     0.707107,  0.707107,
     0.831470,  0.555570,
     0.923880,  0.382683,
     0.980785,  0.195090,
     1.000000,  0.000000,
     0.980785, -0.195090,
     0.923880, -0.382683,
     0.831470, -0.555570,
     0.707107, -0.707107,
     0.555570, -0.831470,
     0.382683, -0.923880,
     0.195090, -0.980785,
  };
  const int vertex_data_size = (sizeof (vertex_data));

  const int per_vertex_size = (sizeof (vertex_data[0])) * 2;

  const unsigned short index_data[] = {
    // "cube" (line strip)
    0, 1, 2, 3, 0,

    // "circle" (line strip)
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     0,
  };
  const int index_data_size = (sizeof (index_data));

  struct location {
    struct {
      unsigned int position;
    } attrib;
    struct {
      unsigned int transform;
      unsigned int use_grid_transform;
      unsigned int base_color;
    } uniform;
  };

  static unsigned int program;
  static location location;

  static unsigned int vertex_array_object;
  static unsigned int per_vertex_buffer;

  static unsigned int index_buffer;

  static unsigned int ray_vertex_buffer;

  static void load_program()
  {
    program = compile_from_files("shader/line_art.vert",
                                 nullptr,
                                 "shader/line_art.frag");

    location.attrib.position = glGetAttribLocation(program, "Position");

    location.uniform.transform = glGetUniformLocation(program, "Transform");
    location.uniform.use_grid_transform = glGetUniformLocation(program, "UseGridTransform");
    location.uniform.base_color = glGetUniformLocation(program, "BaseColor");
  }

  static void load_vertex_attributes()
  {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glVertexBindingDivisor(0, 0);

    glEnableVertexAttribArray(location.attrib.position);
    glVertexAttribFormat(location.attrib.position, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(location.attrib.position, 0);

    glBindVertexArray(0);
  }

  static void load_per_vertex_buffer()
  {
    glGenBuffers(1, &per_vertex_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  static void load_index_buffer()
  {
    glGenBuffers(1, &index_buffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data_size, index_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void load()
  {
    load_program();
    load_vertex_attributes();

    load_per_vertex_buffer();

    load_index_buffer();

    // ray buffer
    glGenBuffers(1, &ray_vertex_buffer);
  }

  void load_ray_vertex_buffer(XMVECTOR const & a, XMVECTOR const & b)
  {
    float data[] = {
      XMVectorGetX(a), XMVectorGetY(a),
      XMVectorGetX(b), XMVectorGetY(b),
    };

    glBindBuffer(GL_ARRAY_BUFFER, ray_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof (data)), data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  XMMATRIX view()
  {
    XMVECTOR eye = XMVectorSet(0, 0, 1, 0);
    XMVECTOR at = XMVectorSet(0, 0, 0, 0);
    XMVECTOR up = XMVectorSet(0, 1, 0, 0);
    return XMMatrixLookAtRH(eye, at, up);
  }

  XMMATRIX projection()
  {
    return XMMatrixOrthographicRH(10, 10, 0, 10);
  }

  void set_transform(XMMATRIX const & transform)
  {
    XMFLOAT4X4 float_transform;
    XMStoreFloat4x4(&float_transform, transform);
    glUniformMatrix4fv(location.uniform.transform, 1, false, (float *)&float_transform);
  }

  const int circle_base_vertex = 8;
  const int circle_base_index = 5 * (sizeof (unsigned short));

  void draw_line(XMMATRIX const & transform, XMVECTOR const & a, XMVECTOR const & b)
  {
    load_ray_vertex_buffer(a, b);
    set_transform(transform);
    glBindVertexBuffer(0, ray_vertex_buffer, 0, per_vertex_size);
    glDrawArrays(GL_LINES, 0, 4);
  }

  void draw_sphere(XMMATRIX const & transform, XMVECTOR const & center, float radius)
  {
    XMMATRIX sphere_transform
      = XMMatrixScaling(radius, radius, radius)
      * XMMatrixTranslationFromVector(center)
      * transform;
    set_transform(sphere_transform);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glDrawElementsBaseVertex(GL_LINE_STRIP, 33, GL_UNSIGNED_SHORT, (void*)(circle_base_index), circle_base_vertex);
  }

  void draw_capsule(XMMATRIX const & transform, XMVECTOR a, XMVECTOR b, float radius)
  {
    draw_sphere(transform, a, radius);
    draw_sphere(transform, b, radius);

    XMVECTOR abn = XMVector3Normalize(a - b);
    XMVECTOR p = XMVectorSet(0, 0, 1, 0);
    XMVECTOR pxabn = XMVector3Cross(abn, p);

    draw_line(transform, a + pxabn * radius, b + pxabn * radius);
    draw_line(transform, a - pxabn * radius, b - pxabn * radius);
  }

  void draw_cube(XMMATRIX const & transform, XMVECTOR const & position)
  {
    float cube_half = 0.5;
    XMMATRIX cube_transform
      = XMMatrixScaling(cube_half, cube_half, cube_half)
      * XMMatrixTranslationFromVector(position)
      * transform;
    set_transform(cube_transform);
    const int cube_base_vertex = 4;
    const int cube_base_index = 0;
    glDrawElementsBaseVertex(GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, (void*)(cube_base_index), cube_base_vertex);
  }

  void scene_start(XMMATRIX const & transform)
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glBindVertexArray(vertex_array_object);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    // grid
    glLineWidth(1.0f);
    set_transform(transform);
    glUniform3f(location.uniform.base_color, 0, 1, 0);
    glUniform1i(location.uniform.use_grid_transform, 1);
    glDrawArraysInstanced(GL_LINES, 0, 4, 7);

    glUniform1i(location.uniform.use_grid_transform, 0);
  }

  void set_color(float r, float g, float b)
  {
    glUniform3f(location.uniform.base_color, r, g, b);
  }
}
