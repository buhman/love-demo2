#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#include "data.inc"

struct test_location {
  struct {
    unsigned int position;
    unsigned int normal;
    unsigned int texture;
    unsigned int block_position;
    unsigned int block_id;
    unsigned int data;
  } attrib;
  struct {
    unsigned int transform;
    unsigned int terrain_sampler;
    unsigned int mouse_position;

    unsigned int texture_id;
  } uniform;
  struct {
    unsigned int texture_id;
  } binding;
};
static unsigned int test_program;
static test_location test_location;

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

struct lighting_location {
  struct {
    unsigned int position_sampler;
    unsigned int normal_sampler;
    unsigned int color_sampler;
    unsigned int quadratic;
    unsigned int linear;
    unsigned int eye;
    unsigned int mouse_position;
    unsigned int mouse_position2;

    unsigned int lights;
  } uniform;
  struct {
    unsigned int lights;
  } binding;
};
static unsigned int lighting_program;
static lighting_location lighting_location;

struct char_tpl {
  const char * vtx;
  const char * cfg;
};

static const int region_count = 4;
static const char_tpl vertex_paths[] = {
  { "minecraft/region.0.0.instance.vtx", "minecraft/region.0.0.instance.cfg" },
  { "minecraft/region.-1.0.instance.vtx", "minecraft/region.-1.0.instance.cfg" },
  { "minecraft/region.0.-1.instance.vtx", "minecraft/region.0.-1.instance.cfg" },
  { "minecraft/region.-1.-1.instance.vtx", "minecraft/region.-1.-1.instance.cfg" },
};

static unsigned int vertex_array_object;
static unsigned int per_instance_vertex_buffers[region_count];
static unsigned int index_buffer;
static unsigned int per_vertex_buffer;

static const int vertex_size = 8;
static const int per_vertex_size = (3 + 3 + 2) * 2;

// also update index_buffer_custom_offsets in data.inc
static const int custom_block_types = 4;
static const int instance_cfg_length = 64 + custom_block_types;

struct instance_cfg {
  struct region_instance {
    int instance_count;
    int offset;
  } cfg[instance_cfg_length];
};

static instance_cfg instance_cfg[region_count];

static unsigned int empty_vertex_array_object = -1;
static unsigned int quad_index_buffer = -1;

static XMFLOAT3 mouse_position;
static bool mouse_position_sample = true;
static XMVECTOR mouse_ray_position;

static float current_time;
static float last_frame_time;

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

  glGenVertexArrays(1, &empty_vertex_array_object);
}

void load_test_program()
{
  unsigned int program = compile_from_files("shader/test.vert",
                                            NULL,
                                            "shader/test.frag");

  test_location.attrib.position = glGetAttribLocation(program, "Position");
  test_location.attrib.normal = glGetAttribLocation(program, "Normal");
  test_location.attrib.texture = glGetAttribLocation(program, "Texture");

  test_location.attrib.block_position = glGetAttribLocation(program, "BlockPosition");
  test_location.attrib.block_id = glGetAttribLocation(program, "BlockID");
  test_location.attrib.data = glGetAttribLocation(program, "Data");
  printf("test program:\n");
  printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n  block_id %u\n  block_id %u\n",
         test_location.attrib.position,
         test_location.attrib.normal,
         test_location.attrib.texture,
         test_location.attrib.block_position,
         test_location.attrib.block_id,
         test_location.attrib.data);

  test_location.uniform.transform = glGetUniformLocation(program, "Transform");
  test_location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
  test_location.uniform.texture_id = glGetUniformBlockIndex(program, "TextureID");
  test_location.uniform.mouse_position = glGetUniformLocation(program, "MousePosition");
  printf(" uniforms:\n  transform %u\n  terrain_sampler %u\n  texture_id %u\n  mouse_position %u\n",
         test_location.uniform.transform,
         test_location.uniform.terrain_sampler,
         test_location.uniform.texture_id,
         test_location.uniform.mouse_position);

  test_location.binding.texture_id = 0;
  glUniformBlockBinding(program, test_location.uniform.texture_id, test_location.binding.texture_id);

  test_program = program;
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

void load_lighting_program()
{
  unsigned int program = compile_from_files("shader/quad.vert",
                                            NULL,
                                            "shader/lighting.frag");

  lighting_location.uniform.position_sampler = glGetUniformLocation(program, "PositionSampler");
  lighting_location.uniform.normal_sampler = glGetUniformLocation(program, "NormalSampler");
  lighting_location.uniform.color_sampler = glGetUniformLocation(program, "ColorSampler");
  lighting_location.uniform.quadratic = glGetUniformLocation(program, "Quadratic");
  lighting_location.uniform.linear = glGetUniformLocation(program, "Linear");
  lighting_location.uniform.eye = glGetUniformLocation(program, "Eye");
  lighting_location.uniform.mouse_position = glGetUniformLocation(program, "MousePosition");
  lighting_location.uniform.mouse_position2 = glGetUniformLocation(program, "MousePosition2");
  lighting_location.uniform.lights = glGetUniformBlockIndex(program, "Lights");

  fprintf(stderr, "lighting program:\n");
  fprintf(stderr, " uniforms:\n  position_sampler %u  normal_sampler %u  color_sampler %u  lights %u\n",
          lighting_location.uniform.position_sampler,
          lighting_location.uniform.normal_sampler,
          lighting_location.uniform.color_sampler,
          lighting_location.uniform.lights);

  lighting_location.binding.lights = 0;
  glUniformBlockBinding(program, lighting_location.uniform.lights, lighting_location.binding.lights);

  lighting_program = program;
}

void load_per_instance_vertex_buffer(int i)
{
  int vertex_buffer_data_size;
  void * vertex_buffer_data = read_file(vertex_paths[i].vtx, &vertex_buffer_data_size);

  glBindBuffer(GL_ARRAY_BUFFER, per_instance_vertex_buffers[i]);
  glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

  free(vertex_buffer_data);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void load_per_vertex_buffer()
{
  glGenBuffers(1, &per_vertex_buffer);

  int vertex_buffer_data_size;
  void * vertex_buffer_data = read_file("minecraft/per_vertex.vtx", &vertex_buffer_data_size);

  glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

  free(vertex_buffer_data);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void load_index_buffer()
{
  glGenBuffers(1, &index_buffer);

  int index_buffer_data_size;
  void * index_buffer_data = read_file("minecraft/configuration.idx", &index_buffer_data_size);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);

  free(index_buffer_data);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void load_test_vertex_attributes()
{
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  glVertexBindingDivisor(0, 0);
  glVertexBindingDivisor(1, 1);

  glEnableVertexAttribArray(test_location.attrib.position);
  glVertexAttribFormat(test_location.attrib.position, 3, GL_HALF_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(test_location.attrib.position, 0);

  glEnableVertexAttribArray(test_location.attrib.normal);
  glVertexAttribFormat(test_location.attrib.normal, 3, GL_HALF_FLOAT, GL_FALSE, 6);
  glVertexAttribBinding(test_location.attrib.normal, 0);

  glEnableVertexAttribArray(test_location.attrib.texture);
  glVertexAttribFormat(test_location.attrib.texture, 2, GL_HALF_FLOAT, GL_FALSE, 12);
  glVertexAttribBinding(test_location.attrib.texture, 0);

  glEnableVertexAttribArray(test_location.attrib.block_position);
  glVertexAttribFormat(test_location.attrib.block_position, 3, GL_SHORT, GL_FALSE, 0);
  glVertexAttribBinding(test_location.attrib.block_position, 1);

  glEnableVertexAttribArray(test_location.attrib.block_id);
  glVertexAttribFormat(test_location.attrib.block_id, 1, GL_UNSIGNED_BYTE, GL_FALSE, 6);
  glVertexAttribBinding(test_location.attrib.block_id, 1);

  glEnableVertexAttribArray(test_location.attrib.data);
  glVertexAttribFormat(test_location.attrib.data, 1, GL_UNSIGNED_BYTE, GL_FALSE, 7);
  glVertexAttribBinding(test_location.attrib.data, 1);

  glBindVertexArray(0);
}

void load_instance_cfg(int i)
{
  int data_size;
  void * data = read_file(vertex_paths[i].cfg, &data_size);
  assert(data_size == (sizeof (struct instance_cfg)));

  memcpy(&instance_cfg[i], data, data_size);
}

struct target_name {
  enum {
    POSITION = 0,
    NORMAL = 1,
    COLOR = 2,
  };
};

template <int render_target_count>
struct geometry_buffer {
  unsigned int framebuffer;
  unsigned int target[render_target_count]; // textures
  unsigned int renderbuffer;
  int initialized;
  int width;
  int height;
};

struct target_type {
  GLint internal_format;
  GLenum attachment;
};

static geometry_buffer<3> geometry_buffer_pnc = {};
static target_type const geometry_buffer_pnc_types[3] = {
  [target_name::POSITION] = { GL_RGBA16F, GL_COLOR_ATTACHMENT0 },
  [target_name::NORMAL] = { GL_RGBA16F, GL_COLOR_ATTACHMENT1 },
  [target_name::COLOR] = { GL_RGBA8, GL_COLOR_ATTACHMENT2 },
};

template <int render_target_count>
void init_geometry_buffer(geometry_buffer<render_target_count>& geometry_buffer, target_type const * const types)
{
  int width = window::width;
  int height = window::height;

  if ((geometry_buffer.initialized == 1) && (width == geometry_buffer.width) && (height == geometry_buffer.height)) {
    return;
  }

  if (geometry_buffer.initialized) {
    glDeleteFramebuffers(1, &geometry_buffer.framebuffer);
    glDeleteTextures(render_target_count, geometry_buffer.target);
    glDeleteRenderbuffers(1, &geometry_buffer.renderbuffer);
  }
  glGenFramebuffers(1, &geometry_buffer.framebuffer);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer.framebuffer);

  glGenTextures(render_target_count, geometry_buffer.target);
  for (int i = 0; i < render_target_count; i++) {
    glBindTexture(GL_TEXTURE_2D, geometry_buffer.target[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, types[i].internal_format, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, types[i].attachment, GL_TEXTURE_2D, geometry_buffer.target[i], 0);
  }
  static_assert(render_target_count == 3);
  GLenum attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
  glDrawBuffers(3, attachments); // bound to GL_DRAW_FRAMEBUFFER

  glGenRenderbuffers(1, &geometry_buffer.renderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, geometry_buffer.renderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, geometry_buffer.renderbuffer);

  assert(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  geometry_buffer.initialized = 1;
  geometry_buffer.width = width;
  geometry_buffer.height = height;
}

void load_buffers()
{
  load_test_vertex_attributes();

  // per-vertex buffer
  load_per_vertex_buffer();

  // per-instance buffer
  glGenBuffers(region_count, per_instance_vertex_buffers);
  for (int i = 0; i < region_count; i++) {
    load_per_instance_vertex_buffer(i);
    load_instance_cfg(i);
  }

  // index buffer
  load_index_buffer();
}

static unsigned int texture;

void load_textures()
{
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int texture_data_size;
  void * texture_data = read_file("minecraft/terrain.data", &texture_data_size);
  assert(texture_data != NULL);

  int width = 256;
  int height = 256;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

  free(texture_data);

  glBindTexture(GL_TEXTURE_2D, 0);
}

static unsigned int light_uniform_buffer;
static unsigned int texture_id_uniform_buffer;

unsigned int load_uniform_buffer(char const * const path)
{
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_UNIFORM_BUFFER, buffer);

  int data_size;
  void * data = read_file(path, &data_size);
  assert(data != NULL);

  glBufferData(GL_UNIFORM_BUFFER, data_size, data, GL_STATIC_DRAW);
  free(data);

  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  return buffer;
}

void load_light_uniform_buffer()
{
  light_uniform_buffer = load_uniform_buffer("minecraft/global.lights.vtx");
}

void load_texture_id_uniform_buffer()
{
  texture_id_uniform_buffer = load_uniform_buffer("minecraft/block_id_to_texture_id.data");
}

extern "C" {
  void * SDL_GL_GetProcAddress(const char *proc);
}

font::font * terminus_fonts;

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

  load_test_program();
  load_buffers();
  load_textures();
  load_texture_id_uniform_buffer();

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

  load_quad_program();
  load_quad_index_buffer();

  //////////////////////////////////////////////////////////////////////
  // lighting
  //////////////////////////////////////////////////////////////////////

  load_lighting_program();
  load_light_uniform_buffer();

  //////////////////////////////////////////////////////////////////////
  // line
  //////////////////////////////////////////////////////////////////////

  load_line_program();
  load_line_vertex_attributes();

  glGenBuffers(1, &line_instance_buffer);

  //////////////////////////////////////////////////////////////////////
  // world
  //////////////////////////////////////////////////////////////////////

  load_world();

  //////////////////////////////////////////////////////////////////////
  // non_block
  //////////////////////////////////////////////////////////////////////

  non_block::load_program();
  non_block::load_index_buffer();
  non_block::load_per_vertex_buffer();
  non_block::load_vertex_attributes();
}

float _ry = 0.0;

struct light_parameters {
  float quadratic;
  float linear;
};
light_parameters lighting = {
  .quadratic = 1.0,
  .linear = 1.0
};

void update_keyboard(int up, int down, int left, int right)
{
  float forward = (0.1f * up + -0.1f * down);
  float strafe = (-0.1f * left + 0.1f * right);
  view::apply_translation(forward, strafe, 0);
}

const int max_joysticks = 8;
static int last_frame_start[max_joysticks] = {};

void update_joystick(int joystick_index,
                     float lx, float ly, float rx, float ry, float tl, float tr,
                     int up, int down, int left, int right,
                     int a, int b, int x, int y,
                     int leftshoulder, int rightshoulder,
                     int start)
{
  float forward = -ly;
  float strafe = lx;
  float elevation = tl - tr;
  view::apply_yaw_pitch(rx * -0.035, ry * -0.035);
  view::apply_translation(forward, strafe, elevation);
  view::apply_fov(0.01 * up + -0.01 * down);

  lighting.quadratic += 0.01 * a + -0.01 * b;
  if (lighting.quadratic < 0.0f)
    lighting.quadratic = 0.0f;
  lighting.linear += 0.01 * x + -0.01 * y;
  if (lighting.linear < 0.0f)
    lighting.linear = 0.0f;

  if (leftshoulder) {
    load_line_point_from_eye(0);
  }
  if (rightshoulder) {
    load_line_point_from_eye(1);
  }
  if (start && (start != last_frame_start[joystick_index])) {
    mouse_position_sample = !mouse_position_sample;
    printf("mouse_position_sample: %d\n", mouse_position_sample);
  }
  last_frame_start[joystick_index] = start;
}

void update(float time)
{
  current_time = time;

  view::update_transforms();
}

static inline int popcount(int x)
{
  return __builtin_popcount(x);
}

template <typename T>
void labeled_value(char * const buf, char const * const label, char const * const format, T value)
{
  const int label_length = strlen(label);
  memcpy(buf, label, label_length);
  int len = snprintf(&buf[label_length], 511 - label_length, format, value);
  buf[label_length + len] = 0;
}

inline static float draw_vector(font::font const& ter_best, char * const buf, float y, char const * const label, XMVECTOR vec)
{
  labeled_value<float>(buf, label, ".x: %.2f", XMVectorGetX(vec));
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;
  labeled_value<float>(buf, label, ".y: %.2f", XMVectorGetY(vec));
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;
  labeled_value<float>(buf, label, ".z: %.2f", XMVectorGetZ(vec));
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;
  return y;
}

static int average_init = 0;
static int average_ix = 0;
static float rolling_sum = 0;
static float averages[16] = {};

const int frame_warmup = 10;

float update_average(float value)
{
  if (average_init < frame_warmup) {
    average_init += 1;
    return 0.0f;
  }
  if (average_init == frame_warmup) {
    assert(average_ix == 0);
    rolling_sum = value * 16.0f;
    for (int i = 0; i < 16; i++) {
      averages[i] = value;
    }
    average_init += 1;
  } else {
    rolling_sum -= averages[average_ix];
    rolling_sum += value;

    averages[average_ix] = value;
    average_ix = (average_ix + 1) % 16;
  }

  return rolling_sum * (1.0f / 16.0f);
}

void draw_hud()
{
  char buf[512];

  float y = 10.0f;

  int font_ix = font::best_font(font::terminus, font::terminus_length);
  font::font const& ter_best = terminus_fonts[font_ix];

  font::draw_start(ter_best, empty_vertex_array_object, quad_index_buffer);

  labeled_value<float>(buf, "fov: ", "%.3f", view::state.fov);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  labeled_value<int>(buf, "font_height: ", "%d", ter_best.desc->glyph_height);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  labeled_value<float>(buf, "lighting.quadratic: ", "%.2f", lighting.quadratic);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  labeled_value<float>(buf, "lighting.linear: ", "%.2f", lighting.linear);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  y = draw_vector(ter_best, buf, y, "eye", view::state.eye);
  y = draw_vector(ter_best, buf, y, "forward", view::state.forward);

  labeled_value<float>(buf, "pitch: ", "%.9f", view::state.pitch);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  XMVECTOR position = XMLoadFloat3(&mouse_position);
  y = draw_vector(ter_best, buf, y, "mouse_position", position);

  y = draw_vector(ter_best, buf, y, "mouse_ray_position", mouse_ray_position);

  labeled_value<float>(buf, "frame_rate_avg: ", "%.2f", 1.0f / update_average(current_time - last_frame_time));
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;
}

void draw_minecraft()
{
  glUseProgram(test_program);

  glBlendFunc(GL_ONE, GL_ZERO);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GREATER);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUniformMatrix4fv(test_location.uniform.transform, 1, false, (float *)&view::state.float_transform);
  glUniform1i(test_location.uniform.terrain_sampler, 0);

  glBindBufferBase(GL_UNIFORM_BUFFER, test_location.binding.texture_id, texture_id_uniform_buffer);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);
  //glFrontFace(GL_CCW);

  XMFLOAT3 position2 = {(float)line_points[0].x, (float)line_points[0].z, (float)line_points[0].y};
  glUniform3fv(test_location.uniform.mouse_position, 1, (float*)&position2);

  glBindVertexArray(vertex_array_object);
  glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

  for (int region_index = 0; region_index < region_count; region_index++) {
    glBindVertexBuffer(1, per_instance_vertex_buffers[region_index], 0, vertex_size);

    //////////////////////////////////////////////////////////////////////
    // cube blocks
    //////////////////////////////////////////////////////////////////////
    for (int configuration = 1; configuration < 64; configuration++) {
      int element_count = 6 * popcount(configuration);
      const void * indices = (void *)((ptrdiff_t)index_buffer_configuration_offsets[configuration]); // index into configuration.idx

      int instance_count = instance_cfg[region_index].cfg[configuration].instance_count;
      int base_instance = instance_cfg[region_index].cfg[configuration].offset / vertex_size; // index into region.0.0.instance.vtx

      if (instance_count == 0)
        continue;

      glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_BYTE, indices, instance_count, base_instance);
    }

    //////////////////////////////////////////////////////////////////////
    // custom blocks
    //////////////////////////////////////////////////////////////////////
    for (int i = 0; i < custom_block_types; i++) {
      int element_count = index_buffer_custom_offsets[i].count;
      const void * indices = (void *)((ptrdiff_t)index_buffer_custom_offsets[i].offset);
      int instance_count = instance_cfg[region_index].cfg[64 + i].instance_count;
      int base_instance = instance_cfg[region_index].cfg[64 + i].offset / vertex_size; // index into region.0.0.instance.vtx
      if (instance_count == 0)
        continue;
      glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_BYTE, indices, instance_count, base_instance);
    }
  }
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

static inline bool near_zero(float a)
{
  return (fabsf(a) < 0.00001f);
}

void draw_lighting()
{
  glUseProgram(lighting_program);
  glDepthFunc(GL_ALWAYS);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[1]);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[2]);

  glUniform1i(lighting_location.uniform.position_sampler, 0);
  glUniform1i(lighting_location.uniform.normal_sampler, 1);
  glUniform1i(lighting_location.uniform.color_sampler, 2);

  float quadratic = near_zero(lighting.quadratic) ? 0.0 : 1.0f / lighting.quadratic;
  float linear = near_zero(lighting.linear) ? 0.0 : 1.0f / lighting.linear;
  glUniform1f(lighting_location.uniform.quadratic, quadratic);
  glUniform1f(lighting_location.uniform.linear, linear);


  XMFLOAT3 eye;
  XMStoreFloat3(&eye, view::state.eye);
  glUniform3fv(lighting_location.uniform.eye, 1, (float*)&eye);
  glUniform3fv(lighting_location.uniform.mouse_position, 1, (float*)&mouse_position);
  /*
  printf("m0: %f %f %f\nm1: %f %f %f\n",
         mouse_position.x, mouse_position.y, mouse_position.z,
         position2.x, position2.y, position2.z);
  */

  glBindBufferBase(GL_UNIFORM_BUFFER, lighting_location.binding.lights, light_uniform_buffer);

  glBindVertexArray(empty_vertex_array_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);
}

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
  if (!mouse_position_sample)
    return;

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
    mouse_ray_position = mouse_view;

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

  // possibly re-initialize geometry buffer if window width/height changes
  init_geometry_buffer(geometry_buffer_pnc, geometry_buffer_pnc_types);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_minecraft();
  //draw_line();
  non_block::draw();

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_lighting();
  //draw_quad();
  draw_hud();

  last_frame_time = current_time;
}
