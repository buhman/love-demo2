#include "glad/gl.h"
#include "directxmath/directxmath.h"
#include "opengl.h"

#include "collision.h"
#include "collision_scene.h"

namespace collision_scene {

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

  static XMVECTOR point_position;
  static XMVECTOR point_1_position;

  static unsigned int ray_vertex_buffer;

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wnarrowing"
  const _Float16 vertex_data[] = {
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
  #pragma GCC diagnostic pop
  const int vertex_data_size = (sizeof (vertex_data));

  const int per_vertex_size = (sizeof (_Float16)) * 2;

  const unsigned short index_data[] = {
    // "cube" (line strip)
    0, 1, 2, 3, 0,

    // "circle" (line strip)
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     0,
  };
  const int index_data_size = (sizeof (index_data));

  void load_program()
  {
    program = compile_from_files("shader/collision_scene.vert",
                                 nullptr,
                                 "shader/collision_scene.frag");

    location.attrib.position = glGetAttribLocation(program, "Position");

    location.uniform.transform = glGetUniformLocation(program, "Transform");
    location.uniform.use_grid_transform = glGetUniformLocation(program, "UseGridTransform");
    location.uniform.base_color = glGetUniformLocation(program, "BaseColor");
  }

  void load_vertex_attributes()
  {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glVertexBindingDivisor(0, 0);

    glEnableVertexAttribArray(location.attrib.position);
    glVertexAttribFormat(location.attrib.position, 2, GL_HALF_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(location.attrib.position, 0);

    glBindVertexArray(0);
  }

  void load_per_vertex_buffer()
  {
    glGenBuffers(1, &per_vertex_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load_index_buffer()
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

    point_position = XMVectorSet(0, 0, 0, 1);
    point_1_position = XMVectorSet(0, 0, 0, 1);

    // ray buffer
    glGenBuffers(1, &ray_vertex_buffer);
  }

  void load_ray_vertex_buffer(XMVECTOR const & a, XMVECTOR const & b)
  {
    _Float16 data[] = {
      (_Float16)XMVectorGetX(a), (_Float16)XMVectorGetY(a),
      (_Float16)XMVectorGetX(b), (_Float16)XMVectorGetY(b),
    };

    glBindBuffer(GL_ARRAY_BUFFER, ray_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4, data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  static inline XMMATRIX view()
  {
    XMVECTOR eye = XMVectorSet(0, 0, 1, 0);
    XMVECTOR at = XMVectorSet(0, 0, 0, 0);
    XMVECTOR up = XMVectorSet(0, 1, 0, 0);
    return XMMatrixLookAtRH(eye, at, up);
  }

  static inline XMMATRIX projection()
  {
    return XMMatrixOrthographicRH(10, 10, 0, 10);
  }

  void update(int up, int down, int left, int right,
              int w, int s, int a, int d)
  {
    float rate = 0.05f;
    float forward = (rate * up + -rate * down);
    float strafe = (-rate * left + rate * right);

    float forward_1 = (rate * w + -rate * s);
    float strafe_1 = (-rate * a + rate * d);

    point_position = XMVector3Transform(point_position, XMMatrixTranslation(strafe, forward, 0));

    point_1_position = XMVector3Transform(point_1_position, XMMatrixTranslation(strafe_1, forward_1, 0));
  }

  static inline void set_transform(XMMATRIX const & transform)
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

  void draw_capsule(XMVECTOR a, XMVECTOR b, float radius)
  {

  }

  void draw()
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glBindVertexArray(vertex_array_object);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    XMMATRIX transform = view() * projection();
    XMFLOAT4X4 float_transform;
    XMStoreFloat4x4(&float_transform, transform);

    // grid
    glUniformMatrix4fv(location.uniform.transform, 1, false, (float *)&float_transform);
    glUniform3f(location.uniform.base_color, 0, 1, 0);
    glUniform1i(location.uniform.use_grid_transform, 1);
    glDrawArraysInstanced(GL_LINES, 0, 4, 7);

    // cube
    float cube_half = 0.5;
    XMVECTOR cube_position = XMVectorSet(1, 0, 0, 0);
    XMMATRIX cube_transform
      = XMMatrixScaling(cube_half, cube_half, cube_half)
      * XMMatrixTranslationFromVector(cube_position)
      * transform;
    set_transform(cube_transform);
    glUniform3f(location.uniform.base_color, 0, 0.5, 1.0);
    glUniform1i(location.uniform.use_grid_transform, 0);
    const int cube_base_vertex = 4;
    const int cube_base_index = 0;
    glDrawElementsBaseVertex(GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, (void*)(cube_base_index), cube_base_vertex);

    // circle
    const float point_radius = 0.05f;

    glUniform3f(location.uniform.base_color, 1.0, 0.5, 0.0);
    draw_sphere(transform, point_position, point_radius);
    draw_sphere(transform, point_1_position, point_radius);

    XMVECTOR direction = XMVector3Normalize(point_1_position - point_position);
    collision::AABB cube_aabb = collision::cube_aabb(cube_position, cube_half);
    XMVECTOR intersection_point;
    float t;
    bool intersection = intersect_ray_aabb(point_position, direction, cube_aabb, t, intersection_point);
    if (intersection && t > 0.0f) {
      glUniform3f(location.uniform.base_color, 0.9, 0.0, 0.0);
      draw_line(transform, point_position, intersection_point);
      draw_sphere(transform, intersection_point, point_radius);
    } else {
      glUniform3f(location.uniform.base_color, 0.5, 0.5, 0.5);
      draw_line(transform, point_position, point_position + direction * 20.0f);
    }
  }
}
