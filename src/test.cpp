#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glad/gl.h"
#include "opengl.h"
#include "directxmath/directxmath.h"
#include "test.h"
#include "font.h"
#include "window.h"

#include "data.inc"

struct test_location {
  struct {
    unsigned int position;
    unsigned int normal;
    unsigned int texture;
    unsigned int block_position;
    unsigned int block_id;
    //unsigned int configuration;
  } attrib;
  struct {
    unsigned int transform;
    unsigned int terrain_sampler;
  } uniform;
};
static unsigned int test_program;
static test_location test_location;

struct quad_location {
  struct {
    unsigned int texture_sampler;
  } uniform;
};
static unsigned int quad_program;
static quad_location quad_location;

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

static const int custom_block_types = 3;
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
  printf("test program:\n");
  printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n  block_id %u\n",
         test_location.attrib.position,
         test_location.attrib.normal,
         test_location.attrib.texture,
         test_location.attrib.block_position,
         test_location.attrib.block_id);

  test_location.uniform.transform = glGetUniformLocation(program, "Transform");
  test_location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
  printf(" uniforms:\n  transform %u\n  terrain_sampler %u\n",
         test_location.uniform.transform,
         test_location.uniform.terrain_sampler);

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
  int width = g_window_width;
  int height = g_window_height;

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

void load_light_uniform_buffer()
{
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_UNIFORM_BUFFER, buffer);

  int data_size;
  void * data = read_file("minecraft/global.lights.vtx", &data_size);
  assert(data != NULL);

  glBufferData(GL_UNIFORM_BUFFER, data_size, data, GL_STATIC_DRAW);
  free(data);

  light_uniform_buffer = buffer;

  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

extern "C" {
  void * SDL_GL_GetProcAddress(const char *proc);
}

struct view_state {
  XMVECTOR up;
  XMVECTOR eye;
  XMVECTOR forward;
  XMVECTOR direction;
  float fov;
  float pitch;
};

view_state view_state;

font::font * terminus_fonts;

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

  view_state.up = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
  view_state.eye = XMVectorSet(0, 0, 0, 1);
  view_state.forward = XMVectorSet(1, 0, 0, 0);
  view_state.direction = view_state.forward;
  view_state.pitch = 0.0;

  view_state.fov = 1.5;

  load_light_uniform_buffer();

  //location.uniform.light_block = glGetUniformBlockIndex(test_program, "TexturesLayout");
  //glUniformBlockBinding(ProgramName, location.uniform.light_block, bindingPoint);
  //printf("textures_layout %d\n", textures_layout);

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
}

float _ry = 0.0;

void update(float lx, float ly, float rx, float ry, float tl, float tr,
            int up, int down, int left, int right)
{
  //view_state.yaw += rx;
  XMMATRIX mrz = XMMatrixRotationZ(rx * -0.035);

  view_state.forward = XMVector3Transform(view_state.forward, mrz);
  XMVECTOR normal = XMVector3NormalizeEst(XMVector3Cross(view_state.forward, view_state.up));

  view_state.pitch += ry * -0.035;
  if (view_state.pitch > 1.5f) view_state.pitch = 1.5f;
  if (view_state.pitch < -1.5f) view_state.pitch = -1.5f;

  XMMATRIX mrn = XMMatrixRotationAxis(normal, view_state.pitch);
  view_state.direction = XMVector3Transform(view_state.forward, mrn);

  view_state.eye += view_state.forward * -ly + normal * lx + view_state.up * (tl - tr);

  float new_fov = view_state.fov + 0.01 * up + -0.01 * down;
  if (new_fov > 0.00001f) {
    view_state.fov = new_fov;
  }
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

void draw_hud()
{
  char buf[512];

  float y = 10.0f;

  int font_ix = font::best_font(font::terminus, font::terminus_length);
  font::font const& ter_best = terminus_fonts[font_ix];

  font::draw_start(ter_best, empty_vertex_array_object, quad_index_buffer);

  labeled_value<float>(buf, "fov: ", "%.3f", view_state.fov);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  labeled_value<float>(buf, "pitch: ", "%.9f", view_state.pitch);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;

  labeled_value<int>(buf, "font_height: ", "%d", ter_best.desc->glyph_height);
  font::draw_string(ter_best, buf, 10, y);
  y += ter_best.desc->glyph_height;
}

void draw_minecraft()
{
  // possibly re-initialize geometry buffer if window width/height changes
  init_geometry_buffer(geometry_buffer_pnc, geometry_buffer_pnc_types);

  XMVECTOR at = XMVectorAdd(view_state.eye, view_state.direction);
  XMMATRIX view = XMMatrixLookAtRH(view_state.eye, at, view_state.up);

  float fov_angle_y = XMConvertToRadians(45 * view_state.fov);
  float aspect_ratio = g_window_width / g_window_height;
  float near_z = 1.0;
  float far_z = 0.1;
  XMMATRIX projection = XMMatrixPerspectiveFovRH(fov_angle_y, aspect_ratio, near_z, far_z);
  XMMATRIX transform = view * projection;

  glUseProgram(test_program);

  glBlendFunc(GL_ONE, GL_ZERO);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GREATER);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUniformMatrix4fv(test_location.uniform.transform, 1, false, (float *)&transform);
  glUniform1i(test_location.uniform.terrain_sampler, 0);

  //glBindBufferBase(GL_UNIFORM_BUFFER, location.binding.light_block, light_uniform_buffer);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);
  //glFrontFace(GL_CCW);

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

void draw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(-1.0f);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer_pnc.framebuffer);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_minecraft();

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_quad();
  //draw_hud();
}
