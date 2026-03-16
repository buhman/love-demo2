#include "glad/gl.h"
#include "directxmath/directxmath.h"
#include "opengl.h"

#include "collision.h"
#include "collision_scene.h"
#include "line_art.h"

namespace collision_scene {

  static XMVECTOR point_position[4];

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

  static const XMVECTOR cubes[] = {
    XMVectorSet(1, 1, 0, 1),
    XMVectorSet(-1, 1, 0, 1),
    XMVectorSet(-2, 1, 0, 1),
    XMVectorSet(-2, -2, 0, 1),
    XMVectorSet(-2, -3, 0, 1),
  };
  static const int cubes_length = (sizeof (cubes)) / (sizeof (cubes[0]));

  void load()
  {
    for (int i = 0; i < 4; i++)
      point_position[i] = XMVectorSet(-1, -1, 0, 1);
  }

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
    XMMATRIX transform = line_art::view() * line_art::projection();

    line_art::scene_start(transform);

    collision::Sphere sphere(point_position[0], 0.48);
    XMVECTOR direction = point_position[1] - point_position[0];

    //////////////////////////////////////////////////////////////////////
    // reset intersections
    //////////////////////////////////////////////////////////////////////

    glLineWidth(3.0f);
    for (int i = 0; i < cubes_length; i++) {
      XMVECTOR center = cubes[i];
      line_art::draw_cube(transform, center);
    }

    //////////////////////////////////////////////////////////////////////
    // collision response
    //////////////////////////////////////////////////////////////////////

    line_art::set_color(0, 0.0, 1.0);
    line_art::draw_sphere(transform, sphere.center, sphere.radius);
    line_art::set_color(0, 0.5, 1.0);
    line_art::draw_sphere(transform, sphere.center + direction, point_radius);
    line_art::draw_line(transform, sphere.center, sphere.center + direction);

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

      line_art::set_color(1.0, 0.5, 1.0);
      line_art::draw_line(transform, state.intersection_position, state.intersection_position + new_direction);

      line_art::set_color(1.0, 0.5, 0.0);
      line_art::draw_sphere(transform, state.intersection_position, sphere.radius);
      line_art::set_color(1.0, 0.0, 0.0);
      line_art::draw_sphere(transform, state.intersection_point, point_radius);

      // collide again
      sphere.center = state.intersection_position;
      direction = new_direction;
      printf("intersection %d\n", intersections);

      intersections += 1;
    }
    if (intersections == 10) {
      //direction == XMVectorZero();
    } else {
      line_art::set_color(1.0, 1.0, 0.0);
      line_art::draw_sphere(transform, sphere.center + direction, sphere.radius);
    }

    /*
    XMVECTOR pa = XMVectorSelect(sphere_aabb.min, sphere_aabb.max, g_XMSelect1000);
    XMVECTOR pb = XMVectorSelect(sphere_aabb.min, sphere_aabb.max, g_XMSelect0101);
    line_art::draw_line(transform, sphere_aabb.min, pa);
    line_art::draw_line(transform, pa, sphere_aabb.max);
    line_art::draw_line(transform, sphere_aabb.max, pb);
    line_art::draw_line(transform, pb, sphere_aabb.min);
    */
    //sphere_aabb.max,

    /*
    // segments
    line_art::set_color(0, 0.5, 1.0);
    line_art::draw_line(transform, point_position[0], point_position[1]);
    line_art::set_color(0, 1.0, 0.5);
    line_art::draw_line(transform, point_position[2], point_position[3]);

    // points
    line_art::set_color(0, 0.5, 1.0);
    line_art::draw_sphere(transform, point_position[0], point_radius);
    line_art::draw_sphere(transform, point_position[1], point_radius);

    line_art::set_color(0, 1.0, 0.5);
    line_art::draw_sphere(transform, point_position[2], point_radius);
    line_art::draw_sphere(transform, point_position[3], point_radius);

    float t1, t2;
    XMVECTOR c1, c2;
    collision::closest_point_segment_segment(point_position[0], point_position[1],
                                             point_position[2], point_position[3],
                                             t1, t2, c1, c2);
    line_art::set_color(0.0, 0.5, 1.0);
    line_art::draw_sphere(transform, c1, point_radius);
    line_art::set_color(0.0, 1.0, 0.5);
    line_art::draw_sphere(transform, c2, point_radius);

    collision::Capsule capsule1(point_position[0], point_position[1], 0.5);
    collision::Capsule capsule2(point_position[2], point_position[3], 0.0);
    line_art::set_color(0, 0.5, 1.0);
    line_art::draw_capsule(transform, capsule1.a, capsule1.b, capsule1.radius);
    line_art::set_color(0, 1.0, 0.5);
    //line_art::draw_capsule(transform, capsule2.a, capsule2.b, capsule2.radius);

    XMVECTOR c1_point;
    XMVECTOR c2_point;
    bool collided = collision::intersect_capsule_capsule(capsule1, capsule2, c1_point, c2_point);
    if (collided) {
      line_art::set_color(1.0, 0.0, 0.0);
      line_art::draw_sphere(transform, c1_point, point_radius);

      line_art::set_color(1.0, 0.5, 0.0);
      line_art::draw_sphere(transform, c2_point, point_radius);
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
    line_art::set_color(0, 0.5, 1.0);
    glUniform1i(location.uniform.use_grid_transform, 0);
    const int cube_base_vertex = 4;
    const int cube_base_index = 0;
    glDrawElementsBaseVertex(GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, (void*)(cube_base_index), cube_base_vertex);

    // circle

    line_art::set_color(1.0, 0.5, 0.0);
    draw_sphere(transform, point_position, point_radius);
    draw_sphere(transform, point_1_position, point_radius);

    XMVECTOR direction = XMVector3Normalize(point_1_position - point_position);
    collision::AABB cube_aabb = collision::cube_aabb(cube_position, cube_half);
    XMVECTOR intersection_point;
    float t;
    bool intersection = intersect_ray_aabb(point_position, direction, cube_aabb, t, intersection_point);
    if (intersection && t > 0.0f) {
      line_art::set_color(0.9, 0.0, 0.0);
      draw_line(transform, point_position, intersection_point);
      draw_sphere(transform, intersection_point, point_radius);
    } else {
      line_art::set_color(0.5, 0.5, 0.5);
      draw_line(transform, point_position, point_position + direction * 20.0f);
    }

    line_art::set_color(0.5, 0.0, 0.5);
    XMVECTOR ca = XMVectorSet(1, 2.5, 0, 0);
    XMVECTOR cb = XMVectorSet(-1, 2, 0, 0);
    draw_capsule(transform, ca, cb, 0.5);
    */
  }
}
