#pragma once

namespace line_art {
  void load();

  void load_ray_vertex_buffer(XMVECTOR const & a, XMVECTOR const & b);

  XMMATRIX view();
  XMMATRIX projection();

  void set_transform(XMMATRIX const & transform);
  void draw_line(XMMATRIX const & transform, XMVECTOR const & a, XMVECTOR const & b);
  void draw_sphere(XMMATRIX const & transform, XMVECTOR const & center, float radius);
  void draw_capsule(XMMATRIX const & transform, XMVECTOR a, XMVECTOR b, float radius);
  void draw_cube(XMMATRIX const & transform, XMVECTOR const & position);
  void scene_start(XMMATRIX const & transform);
  void set_color(float r, float g, float b);
}
