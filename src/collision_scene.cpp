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

  static XMVECTOR point_position[4];

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

    for (int i = 0; i < 4; i++)
      point_position[i] = XMVectorSet(-1, -1, 0, 1);

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

  const float point_radius = 0.05f;

  void update(int up, int down, int left, int right,
              int w, int s, int a, int d,
              int t, int g, int f, int h,
              int i, int k, int j, int l)
  {
    float rate = 0.05f;

    float forward[4];
    float strafe[4];

    forward[0] = (rate * up + -rate * down);
    strafe[0] = (-rate * left + rate * right);

    forward[1] = (rate * w + -rate * s);
    strafe[1] = (-rate * a + rate * d);

    forward[2] = (rate * t + -rate * g);
    strafe[2] = (-rate * f + rate * h);

    forward[3] = (rate * i + -rate * k);
    strafe[3] = (-rate * j + rate * l);

    for (int i = 0; i < 4; i++)
      point_position[i] = XMVector3Transform(point_position[i], XMMatrixTranslation(strafe[i], forward[i], 0));
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

  static const XMVECTOR cubes[] = {
    XMVectorSet(1, 1, 0, 1),
    XMVectorSet(-1, 1, 0, 1),
    XMVectorSet(-2, 1, 0, 1),
    XMVectorSet(-2, -2, 0, 1),
    XMVectorSet(-2, -3, 0, 1),
  };
  static const int cubes_length = (sizeof (cubes)) / (sizeof (cubes[0]));

  void check_collisions(collision::Sphere const & sphere, XMVECTOR const & direction,
                        collision::state & state)
  {
    state.t = FLT_MAX;
    state.intersected = false;

    collision::AABB sphere_aabb = collision::moving_sphere_aabb(sphere, direction);
    XMVECTOR min_floor = XMVectorFloor(sphere_aabb.min);
    XMVECTOR max_ceiling = XMVectorCeiling(sphere_aabb.max);

    for (int i = 0; i < cubes_length; i++) {
      XMVECTOR cube_center = cubes[i];
      // coarse filter
      XMVECTOR le = XMVectorLessOrEqual(min_floor, cube_center);
      XMVECTOR ge = XMVectorGreaterOrEqual(max_ceiling, cube_center);
      if (XMVectorGetX(le) == 0 || XMVectorGetY(le) == 0 || XMVectorGetZ(le) == 0 ||
          XMVectorGetX(ge) == 0 || XMVectorGetY(ge) == 0 || XMVectorGetZ(ge) == 0) {
        continue;
      }

      float cube_half = 0.5;
      collision::check_collision(sphere, direction, cube_center, cube_half, state);
    }
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

    // grid
    glLineWidth(1.0f);
    set_transform(transform);
    glUniform3f(location.uniform.base_color, 0, 1, 0);
    glUniform1i(location.uniform.use_grid_transform, 1);
    glDrawArraysInstanced(GL_LINES, 0, 4, 7);

    glUniform1i(location.uniform.use_grid_transform, 0);

    collision::Sphere sphere(point_position[0], 0.48);
    XMVECTOR direction = point_position[1] - point_position[0];

    //////////////////////////////////////////////////////////////////////
    // reset intersections
    //////////////////////////////////////////////////////////////////////

    glLineWidth(3.0f);
    for (int i = 0; i < cubes_length; i++) {
      XMVECTOR center = cubes[i];
      draw_cube(transform, center);
    }

    //////////////////////////////////////////////////////////////////////
    // collision response
    //////////////////////////////////////////////////////////////////////


    glUniform3f(location.uniform.base_color, 0, 0.0, 1.0);
    draw_sphere(transform, sphere.center, sphere.radius);
    glUniform3f(location.uniform.base_color, 0, 0.5, 1.0);
    draw_sphere(transform, sphere.center + direction, point_radius);
    draw_line(transform, sphere.center, sphere.center + direction);

    int intersections = 0;
    while (intersections < 10) {

      collision::state state;
      check_collisions(sphere, direction, state);
      if (!state.intersected)
        break;

      XMVECTOR intersection_normal;
      XMVECTOR new_direction = collision::sphere_collision_response(sphere, direction,
                                                                    state.intersection_point,
                                                                    state.intersection_position,
                                                                    intersection_normal);

      glUniform3f(location.uniform.base_color, 1.0, 0.5, 1.0);
      draw_line(transform, state.intersection_position, state.intersection_position + new_direction);

      glUniform3f(location.uniform.base_color, 1.0, 0.5, 0.0);
      draw_sphere(transform, state.intersection_position, sphere.radius);
      glUniform3f(location.uniform.base_color, 1.0, 0.0, 0.0);
      draw_sphere(transform, state.intersection_point, point_radius);

      // collide again
      sphere.center = state.intersection_position;
      direction = new_direction;
      printf("intersection %d\n", intersections);

      intersections += 1;
    }
    if (intersections == 10) {
      //direction == XMVectorZero();
    } else {
      glUniform3f(location.uniform.base_color, 1.0, 1.0, 0.0);
      draw_sphere(transform, sphere.center + direction, sphere.radius);
    }

    /*
    XMVECTOR pa = XMVectorSelect(sphere_aabb.min, sphere_aabb.max, g_XMSelect1000);
    XMVECTOR pb = XMVectorSelect(sphere_aabb.min, sphere_aabb.max, g_XMSelect0101);
    draw_line(transform, sphere_aabb.min, pa);
    draw_line(transform, pa, sphere_aabb.max);
    draw_line(transform, sphere_aabb.max, pb);
    draw_line(transform, pb, sphere_aabb.min);
    */
    //sphere_aabb.max,

    /*
    // segments
    glUniform3f(location.uniform.base_color, 0, 0.5, 1.0);
    draw_line(transform, point_position[0], point_position[1]);
    glUniform3f(location.uniform.base_color, 0, 1.0, 0.5);
    draw_line(transform, point_position[2], point_position[3]);

    // points
    glUniform3f(location.uniform.base_color, 0, 0.5, 1.0);
    draw_sphere(transform, point_position[0], point_radius);
    draw_sphere(transform, point_position[1], point_radius);

    glUniform3f(location.uniform.base_color, 0, 1.0, 0.5);
    draw_sphere(transform, point_position[2], point_radius);
    draw_sphere(transform, point_position[3], point_radius);

    float t1, t2;
    XMVECTOR c1, c2;
    collision::closest_point_segment_segment(point_position[0], point_position[1],
                                             point_position[2], point_position[3],
                                             t1, t2, c1, c2);
    glUniform3f(location.uniform.base_color, 0.0, 0.5, 1.0);
    draw_sphere(transform, c1, point_radius);
    glUniform3f(location.uniform.base_color, 0.0, 1.0, 0.5);
    draw_sphere(transform, c2, point_radius);

    collision::Capsule capsule1(point_position[0], point_position[1], 0.5);
    collision::Capsule capsule2(point_position[2], point_position[3], 0.0);
    glUniform3f(location.uniform.base_color, 0, 0.5, 1.0);
    draw_capsule(transform, capsule1.a, capsule1.b, capsule1.radius);
    glUniform3f(location.uniform.base_color, 0, 1.0, 0.5);
    //draw_capsule(transform, capsule2.a, capsule2.b, capsule2.radius);

    XMVECTOR c1_point;
    XMVECTOR c2_point;
    bool collided = collision::intersect_capsule_capsule(capsule1, capsule2, c1_point, c2_point);
    if (collided) {
      glUniform3f(location.uniform.base_color, 1.0, 0.0, 0.0);
      draw_sphere(transform, c1_point, point_radius);

      glUniform3f(location.uniform.base_color, 1.0, 0.5, 0.0);
      draw_sphere(transform, c2_point, point_radius);
    }
    */

    // cube
    /*
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

    glUniform3f(location.uniform.base_color, 0.5, 0.0, 0.5);
    XMVECTOR ca = XMVectorSet(1, 2.5, 0, 0);
    XMVECTOR cb = XMVectorSet(-1, 2, 0, 0);
    draw_capsule(transform, ca, cb, 0.5);
    */
  }
}
