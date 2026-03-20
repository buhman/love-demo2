#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geometry_buffer.h"
#include "glad/gl.h"
#include "opengl.h"
#include "directxmath/directxmath.h"
#include "test.h"
#include "font/bitmap.h"
#include "font/outline.h"
#include "window.h"
#include "bresenham.h"
#include "file.h"
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
#include "pixel_line_art.h"
#include "flame.h"
#include "new.h"

#include "world/entry_table.h"
#include "world/world.h"

#include "data/scenes/ship20.h"
#include "data/scenes/noodle.h"
#include "data/scenes/shadow_test.h"
#include "data/scenes/book.h"

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

font::bitmap::font * terminus_fonts;
font::outline::font * uncial_antiqua_fonts;

geometry_buffer<4> geometry_buffer_pnc = {};
static target_type const geometry_buffer_pnc_types[4] = {
  [target_name::POSITION] = { GL_RGBA16F, GL_COLOR_ATTACHMENT0 },
  [target_name::NORMAL] = { GL_RGBA16F, GL_COLOR_ATTACHMENT1 },
  [target_name::COLOR] = { GL_RGBA8, GL_COLOR_ATTACHMENT2 },
  [target_name::BLOCK] = { GL_RGBA16F, GL_COLOR_ATTACHMENT3 },
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

void load(const char * source_path)
{
  g_source_path_length = strlen(source_path);
  assert(source_path[g_source_path_length - 1] != '/');
  g_source_path = source_path;

  fprintf(stderr, "getproc %p\n", SDL_GL_GetProcAddress);
  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  //

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //////////////////////////////////////////////////////////////////////
  // minecraft (drawing data)
  //////////////////////////////////////////////////////////////////////

  minecraft::load();

  //////////////////////////////////////////////////////////////////////
  // view
  //////////////////////////////////////////////////////////////////////

  view::load();

  //////////////////////////////////////////////////////////////////////
  // font
  //////////////////////////////////////////////////////////////////////

  font::bitmap::load_shader();
  terminus_fonts = New<font::bitmap::font>(font::bitmap::terminus_length);
  font::bitmap::load_fonts(terminus_fonts, font::bitmap::terminus, font::bitmap::terminus_length);

  font::outline::load_shader();
  uncial_antiqua_fonts = New<font::outline::font>(font::outline::uncial_antiqua_length);
  font::outline::load_fonts(uncial_antiqua_fonts, font::outline::uncial_antiqua, font::outline::uncial_antiqua_length);

  //////////////////////////////////////////////////////////////////////
  // pixel_line_art
  //////////////////////////////////////////////////////////////////////

  pixel_line_art::load();

  //////////////////////////////////////////////////////////////////////
  // quad
  //////////////////////////////////////////////////////////////////////

  glGenVertexArrays(1, &empty_vertex_array_object);
  load_quad_program();
  load_quad_index_buffer();

  //////////////////////////////////////////////////////////////////////
  // lighting
  //////////////////////////////////////////////////////////////////////

  lighting::load();

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
  scene_state.load_scene(&book::descriptor);
  node_eye = scene_state.find_node_by_name("Camera");
  assert(node_eye != nullptr);
  //view::state.eye = XMVector3Transform(XMVectorZero(), node_eye->world);

  //node_at = scene_state.find_node_by_name("Camera001.Target");
  //assert(node_at != nullptr);

  //////////////////////////////////////////////////////////////////////
  // flame
  //////////////////////////////////////////////////////////////////////

  flame::load_program();
  flame::load_texture();
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
        world::entry_table::global_entry * const entry = world_lookup(minecraft::current_world->descriptor->hash_func,
                                                                      minecraft::current_world->entry_table,
                                                                      minecraft::current_world->entry_table_length,
                                                                      x, y, z);
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

void minecraft_view_update(XMVECTOR direction)
{
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
  view::state.eye = view::state.at - view::state.direction * view::at_distance;
}

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

  if (true) {
    minecraft_view_update(direction);
  }

  //view::state.eye = view::state.eye + direction;
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
}

void update(float time)
{
  current_time = time;

  scene_state.update(time);
  /*
  view::state.eye = XMVector3Transform(XMVectorZero(), node_eye->world);
  if (node_at == nullptr)
    view::state.at = XMVectorZero();
  else
    view::state.at = XMVector3Transform(XMVectorZero(), node_at->world);
  */

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

int clamp(int n, int high)
{
  if (n < 0)
    return 0;
  if (n >= high)
    return high;
  return n;
}

float mouse_position[4] = {};
float mouse_block[4] = {};

void update_mouse(int x, int y)
{
  x = clamp(x, geometry_buffer_pnc.width);
  y = clamp(y, geometry_buffer_pnc.height);

  glBindFramebuffer(GL_READ_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
  glReadBuffer(geometry_buffer_pnc_types[target_name::POSITION].attachment);

  glReadPixels(x,
               geometry_buffer_pnc.height - y,
               1, // width
               1, // height
               GL_RGBA,
               GL_FLOAT,
               (void*)&mouse_position);

  glReadBuffer(geometry_buffer_pnc_types[target_name::BLOCK].attachment);
  glReadPixels(x,
               geometry_buffer_pnc.height - y,
               1, // width
               1, // height
               GL_RGBA,
               GL_FLOAT,
               (void*)&mouse_block);
}

void draw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(-1.0f);
  if (true) {
    // possibly re-initialize geometry buffer if window width/height changes
    init_geometry_buffer(geometry_buffer_pnc, geometry_buffer_pnc_types);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    minecraft::draw();

    non_block::draw();

    flame::draw(minecraft::current_world->light_uniform_buffer,
                minecraft::current_world->light_count);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting::draw(minecraft::current_world->light_uniform_buffer,
                   minecraft::current_world->light_count);
    //draw_quad();
    hud::draw();

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //font::outline::draw_start(uncial_antiqua_fonts[0], empty_vertex_array_object, quad_index_buffer);
    //font::outline::draw_string(uncial_antiqua_fonts[0], "test", 150, 500);

  } else {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //collision_scene::draw();
    //boids_scene::draw();
    scene_state.draw();
  }

  last_frame_time = current_time;
}
