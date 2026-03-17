#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geometry_buffer.h"
#include "glad/gl.h"
#include "opengl.h"
#include "directxmath/directxmath.h"
#include "test.h"
#include "font.h"
#include "window.h"
#include "bresenham.h"
#include "file.h"
#include "world.h"
#include "view.h"
#include "non_block.h"
#include "minecraft.h"
#include "hud.h"
#include "lighting.h"
#include "line_art.h"
#include "collision_scene.h"
#include "collision.h"
#include "boids_scene.h"
#include "collada/effect.h"
#include "collada/scene.h"
#include "collada/types.h"
#include "collada/instance_types.h"

#include "data/scenes/ship20.h"
#include "data/scenes/noodle.h"
#include "data/scenes/shadow_test.h"

struct line_location {
  struct {
    unsigned int position;
    unsigned int normal;
    unsigned int texture;
    unsigned int block_position;
  } attrib;
  struct {
    unsigned int transform;
  } uniform;
};
static unsigned int line_program;
static line_location line_location;
static unsigned int line_vertex_array_object;
static unsigned int line_instance_buffer;

struct quad_location {
  struct {
    unsigned int texture_sampler;
  } uniform;
};
static unsigned int quad_program;
static quad_location quad_location;

//////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////

static collada::scene::state scene_state;

unsigned int empty_vertex_array_object = -1;
unsigned int quad_index_buffer = -1;

float current_time;
float last_frame_time;

font::font * terminus_fonts;

geometry_buffer<3> geometry_buffer_pnc = {};
static target_type const geometry_buffer_pnc_types[3] = {
  [target_name::POSITION] = { GL_RGBA16F, GL_COLOR_ATTACHMENT0 },
  [target_name::NORMAL] = { GL_RGBA16F, GL_COLOR_ATTACHMENT1 },
  [target_name::COLOR] = { GL_RGBA8, GL_COLOR_ATTACHMENT2 },
};

collada::instance_types::node * node_eye;
collada::instance_types::node * node_at;

void load_quad_index_buffer()
{
  uint8_t const data[] = {
    1, 0, 2, 3,
  };
  int const data_size = (sizeof (data));

  glGenBuffers(1, &quad_index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void load_quad_program()
{
  unsigned int program = compile_from_files("shader/quad.vert",
                                            NULL,
                                            "shader/quad.frag");

  quad_location.uniform.texture_sampler = glGetUniformLocation(program, "TextureSampler");
  printf("quad program:\n");
  printf(" uniforms:\n  texture_sampler %u\n",
         quad_location.uniform.texture_sampler);

  quad_program = program;
}

extern "C" {
  void * SDL_GL_GetProcAddress(const char *proc);
}

struct short_point {
  short x;
  short y;
  short z;
};
static_assert((sizeof (short_point)) == 6);

short_point line_points[128];
static int line_point_ix = 0;

void append_line_point(int x, int y, int z)
{
  if (line_point_ix == 1)
    return;

  global_entry * const entry = world_lookup(x, y, z);
  if (entry != NULL) {
    line_points[line_point_ix].x = x;
    line_points[line_point_ix].y = y;
    line_points[line_point_ix].z = z;
    line_point_ix += 1;
  }
}

void load_line_program()
{
  unsigned int program = compile_from_files("shader/line.vert",
                                            NULL,
                                            "shader/line.frag");

  line_location.attrib.position = glGetAttribLocation(program, "Position");
  line_location.attrib.normal = glGetAttribLocation(program, "Normal");
  line_location.attrib.texture = glGetAttribLocation(program, "Texture");

  line_location.attrib.block_position = glGetAttribLocation(program, "BlockPosition");

  printf("line program:\n");
  printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n",
         line_location.attrib.position,
         line_location.attrib.normal,
         line_location.attrib.texture,
         line_location.attrib.block_position);

  line_location.uniform.transform = glGetUniformLocation(program, "Transform");
  printf(" uniforms:\n  transform %u\n\n",
         line_location.uniform.transform);

  line_program = program;
}

void load_line_vertex_attributes()
{
  glGenVertexArrays(1, &line_vertex_array_object);
  glBindVertexArray(line_vertex_array_object);

  glVertexBindingDivisor(0, 0);
  glVertexBindingDivisor(1, 1);

  glEnableVertexAttribArray(line_location.attrib.position);
  glVertexAttribFormat(line_location.attrib.position, 3, GL_HALF_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(line_location.attrib.position, 0);

  glEnableVertexAttribArray(line_location.attrib.normal);
  glVertexAttribFormat(line_location.attrib.normal, 3, GL_HALF_FLOAT, GL_FALSE, 6);
  glVertexAttribBinding(line_location.attrib.normal, 0);

  glEnableVertexAttribArray(line_location.attrib.texture);
  glVertexAttribFormat(line_location.attrib.texture, 2, GL_HALF_FLOAT, GL_FALSE, 12);
  glVertexAttribBinding(line_location.attrib.texture, 0);

  glEnableVertexAttribArray(line_location.attrib.block_position);
  glVertexAttribFormat(line_location.attrib.block_position, 3, GL_SHORT, GL_FALSE, 0);
  glVertexAttribBinding(line_location.attrib.block_position, 1);

  glBindVertexArray(0);
}

void load_line_instance_buffer()
{
  glBindBuffer(GL_ARRAY_BUFFER, line_instance_buffer);
  glBufferData(GL_ARRAY_BUFFER, (sizeof (short_point)) * line_point_ix, line_points, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

struct line_state {
  struct {
    int x;
    int y;
    int z;
  } point[2];
};
static line_state line_state = {};

void load_line()
{
  line_point_ix = 0;
  bresenham(line_state.point[0].x, line_state.point[0].y, line_state.point[0].z,
            line_state.point[1].x, line_state.point[1].y, line_state.point[1].z,
            append_line_point);

  load_line_instance_buffer();
}

void load_line_point_from_eye(int point_ix)
{
  int x = XMVectorGetX(view::state.eye);
  int y = XMVectorGetY(view::state.eye);
  int z = XMVectorGetZ(view::state.eye);

  line_state.point[point_ix].x = x;
  line_state.point[point_ix].y = z;
  line_state.point[point_ix].z = y;

  load_line();
}

void load(const char * source_path)
{
  g_source_path_length = strlen(source_path);
  assert(source_path[g_source_path_length - 1] != '/');
  g_source_path = source_path;

  fprintf(stderr, "getproc %p\n", SDL_GL_GetProcAddress);
  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  //////////////////////////////////////////////////////////////////////
  // minecraft (drawing data)
  //////////////////////////////////////////////////////////////////////

  minecraft::load();

  //////////////////////////////////////////////////////////////////////
  // world (collision data)
  //////////////////////////////////////////////////////////////////////

  load_world();

  //////////////////////////////////////////////////////////////////////
  // view
  //////////////////////////////////////////////////////////////////////

  view::load();

  //////////////////////////////////////////////////////////////////////
  // font
  //////////////////////////////////////////////////////////////////////

  font::load_shader();

  terminus_fonts = (font::font *)malloc((sizeof (font::font)) * font::terminus_length);
  font::load_fonts(terminus_fonts, font::terminus, font::terminus_length);

  //////////////////////////////////////////////////////////////////////
  // quad
  //////////////////////////////////////////////////////////////////////

  glGenVertexArrays(1, &empty_vertex_array_object);
  load_quad_program();
  load_quad_index_buffer();

  //////////////////////////////////////////////////////////////////////
  // lighting
  //////////////////////////////////////////////////////////////////////

  lighting::load_program();
  lighting::load_light_uniform_buffer();

  //////////////////////////////////////////////////////////////////////
  // line
  //////////////////////////////////////////////////////////////////////

  load_line_program();
  load_line_vertex_attributes();

  glGenBuffers(1, &line_instance_buffer);

  //////////////////////////////////////////////////////////////////////
  // non_block
  //////////////////////////////////////////////////////////////////////

  non_block::load_program();
  non_block::load_index_buffer();
  non_block::load_per_vertex_buffer();
  non_block::load_vertex_attributes();

  //////////////////////////////////////////////////////////////////////
  // debug scenes
  //////////////////////////////////////////////////////////////////////

  line_art::load();
  collision_scene::load();
  boids_scene::load();

  //////////////////////////////////////////////////////////////////////
  // collada
  //////////////////////////////////////////////////////////////////////

  collada::effect::load_effects();
  scene_state.load_scene(&noodle::descriptor);
  node_eye = scene_state.find_node_by_name("Camera001");
  assert(node_eye != nullptr);
  node_at = scene_state.find_node_by_name("Camera001.Target");
  assert(node_at != nullptr);
}

void update_keyboard(int up, int down, int left, int right,
                     int w, int s, int a, int d,
                     int t, int g, int f, int h,
                     int i, int k, int j, int l)
{
  //float forward = (0.1f * up + -0.1f * down);
  //float strafe = (-0.1f * left + 0.1f * right);
  //view::third_person::apply_translation(forward, strafe, 0);
  /*
  collision_scene::update(up, down, left, right,
                          w, s, a, d,
                          t, g, f, h,
                          i, k, j, l);
  */
  boids_scene::update(up, down, left, right,
                      w, s, a, d,
                      t, g, f, h,
                      i, k, j, l);
}

void check_collisions(collision::Sphere const & sphere, XMVECTOR const & direction,
                      collision::state & state)
{
  state.t = FLT_MAX;
  state.intersected = false;

  collision::AABB sphere_aabb = collision::moving_sphere_aabb(sphere, direction);
  XMVECTOR min_floor = XMVectorFloor(sphere_aabb.min);
  XMVECTOR max_ceiling = XMVectorCeiling(sphere_aabb.max);

  int min_x = XMVectorGetX(min_floor);
  int min_y = XMVectorGetZ(min_floor); // swizzle
  int min_z = XMVectorGetY(min_floor); // swizzle

  int max_x = XMVectorGetX(max_ceiling);
  int max_y = XMVectorGetZ(max_ceiling); // swizzle
  int max_z = XMVectorGetY(max_ceiling); // swizzle

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      for (int z = min_z; z <= max_z; z++) {
        global_entry * const entry = world_lookup(x, y, z);
        if (entry == NULL)
          continue;

        // there is a block at x, y, z
        XMVECTOR cube_center = XMVectorSet(x, z, y, 1); // swizzle
        float cube_half = 0.5f;
        collision::check_collision(sphere, direction,
                                   cube_center, cube_half,
                                   state);
      }
    }
  }
}

const int max_joysticks = 8;

void update_joystick(int joystick_index,
                     float lx, float ly, float rx, float ry, float tl, float tr,
                     int up, int down, int left, int right,
                     int a, int b, int x, int y,
                     int leftshoulder, int rightshoulder,
                     int start)
{
  float forward = -ly * 0.5;
  float strafe = lx * 0.5;
  float elevation = (tl - tr) * 0.5;
  float delta_yaw = rx * -0.035;
  float delta_pitch = ry * -0.035;

  XMVECTOR direction = view::third_person::apply_transform(forward, strafe, elevation,
                                                           delta_yaw, delta_pitch);
  view::apply_fov(0.01 * up + -0.01 * down);

  /*
  XMVECTOR sphere_position = view::state.at;

  float sphere_radius = 0.48;
  collision::Sphere sphere(sphere_position, sphere_radius);
  int intersections = 0;
  collision::state state;
  while (intersections < 500) {
    check_collisions(sphere, direction, state);
    if (!state.intersected)
      break;

    XMVECTOR intersection_normal;
    XMVECTOR new_direction = collision::sphere_collision_response(sphere, direction,
                                                                  state.intersection_point,
                                                                  state.intersection_position,
                                                                  intersection_normal);
    // collide again
    sphere.center = state.intersection_position + intersection_normal * 0.01f;
    direction = new_direction * 0.9f;
    if (XMVectorGetX(XMVector3Length(direction)) < 0.001f) {
      direction = XMVectorZero();
      break;
    }
    intersections += 1;
  }
  if (intersections == 500) { // too many recursive collisions
    printf("too many recursive collisions\n");
  } else {
    // apply the last direction impulse
    view::state.at = sphere.center + direction;
  }
  */

  view::state.eye = view::state.eye + direction;
  //view::state.at = view::state.at - view::state.direction * view::at_distance;

  //view::state.at = view::state.at + direction;
  //view::state.eye = view::state.at - view::state.direction * view::at_distance;

  /*
  lighting.quadratic += 0.01 * a + -0.01 * b;
  if (lighting.quadratic < 0.0f)
    lighting.quadratic = 0.0f;
  lighting.linear += 0.01 * x + -0.01 * y;
  if (lighting.linear < 0.0f)
    lighting.linear = 0.0f;
  */

  if (leftshoulder) {
    load_line_point_from_eye(0);
  }
  if (rightshoulder) {
    load_line_point_from_eye(1);
  }
}

void update(float time)
{
  current_time = time;

  scene_state.update(time);
  view::state.eye = XMVector3Transform(XMVectorZero(), node_eye->world);
  view::state.at = XMVector3Transform(XMVectorZero(), node_at->world);

  view::update_transforms();
}

void draw_quad()
{
  glUseProgram(quad_program);
  glDepthFunc(GL_ALWAYS);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[1]);

  glUniform1i(quad_location.uniform.texture_sampler, 0);

  glBindVertexArray(empty_vertex_array_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);
}

static inline int popcount(int x)
{
  return __builtin_popcount(x);
}

/*
void draw_line()
{
  if (line_point_ix == 0)
    return;

  glUseProgram(line_program);

  glBlendFunc(GL_ONE, GL_ZERO);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);

  glUniformMatrix4fv(line_location.uniform.transform, 1, false, (float *)&view::state.float_transform);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);
  //glFrontFace(GL_CCW);

  glBindVertexArray(line_vertex_array_object);
  glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
  int line_instance_vertex_size = (sizeof (short_point));
  glBindVertexBuffer(1, line_instance_buffer, 0, line_instance_vertex_size);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

  int configuration = 63;
  int element_count = 6 * popcount(configuration);
  const void * indices = (void *)((ptrdiff_t)index_buffer_configuration_offsets[configuration]); // index into configuration.idx
  int instance_count = line_point_ix;
  int base_instance = 0;
  if (instance_count - base_instance <= 0)
    return;
  glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_BYTE, indices, instance_count - base_instance, base_instance);
}
*/

int clamp(int n, int high)
{
  if (n < 0)
    return 0;
  if (n >= high)
    return high;
  return n;
}

void update_mouse(int x, int y)
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
  glReadBuffer(geometry_buffer_pnc_types[target_name::POSITION].attachment);

  /*
  x = clamp(x, geometry_buffer_pnc.width);
  y = clamp(y, geometry_buffer_pnc.height);
  glReadPixels(x,
               geometry_buffer_pnc.height - y,
               1, // width
               1, // height
               GL_RGB,
               GL_FLOAT,
               (void*)&mouse_position);
  */

  {
    float mx = (2.0f * (float)x) / geometry_buffer_pnc.width - 1.0f;
    float my = 1.0f - (2.0f * (float)y) / geometry_buffer_pnc.height;
    /*
    XMVECTOR mouse_world = XMVector3Transform(mouse_clip, inverse);
    XMVECTOR ray = XMVector3Normalize(mouse_world - view::state.eye);
    mouse_ray_position = ray;

    XMVECTOR ray_start = view::state.eye;
    XMVECTOR ray_end = ray_start + ray * 20.0f;
    */

    XMVECTOR mouse_clip = XMVectorSet(mx, my, -1, 0);

    XMMATRIX projection_inverse = XMMatrixInverse(NULL, view::state.projection_transform);
    XMMATRIX view_inverse = XMMatrixInverse(NULL, view::state.view_transform);

    XMVECTOR mouse_view = XMVector3Transform(mouse_clip, projection_inverse);

    mouse_view = XMVectorSetZ(mouse_view, -1);
    XMVECTOR ray = XMVector3Normalize(XMVector3TransformNormal(mouse_view, view_inverse));

    XMVECTOR ray_start = view::state.eye;
    XMVECTOR ray_end = ray_start + ray * 20.0f;

    line_state.point[0].x = roundf(XMVectorGetX(ray_start));
    line_state.point[0].z = roundf(XMVectorGetY(ray_start));
    line_state.point[0].y = roundf(XMVectorGetZ(ray_start));

    line_state.point[1].x = roundf(XMVectorGetX(ray_end));
    line_state.point[1].z = roundf(XMVectorGetY(ray_end));
    line_state.point[1].y = roundf(XMVectorGetZ(ray_end));
    load_line();
  }
}

void draw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(-1.0f);
  if (false) {
    // possibly re-initialize geometry buffer if window width/height changes
    init_geometry_buffer(geometry_buffer_pnc, geometry_buffer_pnc_types);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    minecraft::draw();
    //draw_line();
    non_block::draw();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting::draw();
    //draw_quad();
    hud::draw();
  } else {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //collision_scene::draw();
    //boids_scene::draw();
    scene_state.draw();
  }

  last_frame_time = current_time;
}
