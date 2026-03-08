#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glad/gl.h"
#include "opengl.h"
#include "directxmath/directxmath.h"
#include "test.h"

#include "data.inc"

struct location {
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

// state
static unsigned int test_program;
static struct location location;

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

void load_program()
{
  unsigned int program = compile_from_files("shader/test.vert",
                                            NULL, //"shader/test.geom",
                                            "shader/test.frag");

  location.attrib.position = glGetAttribLocation(program, "Position");
  location.attrib.normal = glGetAttribLocation(program, "Normal");
  location.attrib.texture = glGetAttribLocation(program, "Texture");

  location.attrib.block_position = glGetAttribLocation(program, "BlockPosition");
  location.attrib.block_id = glGetAttribLocation(program, "BlockID");
  printf("attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n  block_id %u\n\n",
         location.attrib.position,
         location.attrib.normal,
         location.attrib.texture,
         location.attrib.block_position,
         location.attrib.block_id);

  location.uniform.transform = glGetUniformLocation(program, "Transform");
  location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
  printf("uniforms:\n  transform %u\n  terrain_sampler %u\n",
         location.uniform.transform,
         location.uniform.terrain_sampler);

  test_program = program;
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
  int vertex_buffer_data_size;
  void * vertex_buffer_data = read_file("minecraft/per_vertex.vtx", &vertex_buffer_data_size);

  glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

  free(vertex_buffer_data);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void load_index_buffer()
{
  int index_buffer_data_size;
  void * index_buffer_data = read_file("minecraft/configuration.idx", &index_buffer_data_size);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);

  free(index_buffer_data);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void load_vertex_attributes()
{
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  glVertexBindingDivisor(0, 0);
  glVertexBindingDivisor(1, 1);

  glEnableVertexAttribArray(location.attrib.position);
  glVertexAttribFormat(location.attrib.position, 3, GL_HALF_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(location.attrib.position, 0);

  glEnableVertexAttribArray(location.attrib.normal);
  glVertexAttribFormat(location.attrib.normal, 3, GL_HALF_FLOAT, GL_FALSE, 6);
  glVertexAttribBinding(location.attrib.normal, 0);

  glEnableVertexAttribArray(location.attrib.texture);
  glVertexAttribFormat(location.attrib.texture, 2, GL_HALF_FLOAT, GL_FALSE, 12);
  glVertexAttribBinding(location.attrib.texture, 0);

  glEnableVertexAttribArray(location.attrib.block_position);
  glVertexAttribFormat(location.attrib.block_position, 3, GL_SHORT, GL_FALSE, 0);
  glVertexAttribBinding(location.attrib.block_position, 1);

  glEnableVertexAttribArray(location.attrib.block_id);
  glVertexAttribFormat(location.attrib.block_id, 1, GL_UNSIGNED_BYTE, GL_FALSE, 6);
  glVertexAttribBinding(location.attrib.block_id, 1);

  glBindVertexArray(0);
}

void load_instance_cfg(int i)
{
  int data_size;
  void * data = read_file(vertex_paths[i].cfg, &data_size);
  assert(data_size == (sizeof (struct instance_cfg)));

  memcpy(&instance_cfg[i], data, data_size);
}

void load_buffers()
{
  load_vertex_attributes();

  // per-vertex buffer
  glGenBuffers(1, &per_vertex_buffer);
  load_per_vertex_buffer();

  // per-instance buffer
  glGenBuffers(region_count, per_instance_vertex_buffers);

  for (int i = 0; i < region_count; i++) {
    load_per_instance_vertex_buffer(i);
    load_instance_cfg(i);
  }

  // index buffer

  glGenBuffers(1, &index_buffer);
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

static unsigned int textures_ubo;

void load_texture_shader_storage()
{
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_UNIFORM_BUFFER, buffer);

  int textures_data_size;
  void * textures_data = read_file("minecraft/block_id_to_texture_id.data", &textures_data_size);
  assert(textures_data != NULL);

  glBufferData(GL_UNIFORM_BUFFER, textures_data_size, textures_data, GL_STATIC_DRAW);
  free(textures_data);

  textures_ubo = buffer;
}

extern "C" {
  void * SDL_GL_GetProcAddress(const char *proc);
}

void load()
{
  fprintf(stderr, "getproc %p\n", SDL_GL_GetProcAddress);
  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  load_program();
  load_buffers();
  load_textures();
  //load_texture_shader_storage();

  //unsigned int textures_layout = glGetUniformBlockIndex(test_program, "TexturesLayout");
  //glUniformBlockBinding(test_program, textures_layout, 0);
  //printf("textures_layout %d\n", textures_layout);
}

static float vx = 0.0;
static float vy = 0.0;
static float vz = 0.0;

void update(float lx, float ly, float ry)
{
  vx += 2.5 * lx;
  vy += -2.5 * ry;
  vz += -2.5 * ly;
}

static inline int popcount(int x)
{
  return __builtin_popcount(x);
}

void draw()
{
  XMVECTOR eye = XMVectorSet(vx + -50.0f, vz + -50.0f, vy + 150.0f, 0.0f);
  XMVECTOR at = XMVectorSet(vx + 50.0f, vz + 50.0f, vy + 50.0f, 0.0f);
  XMVECTOR up = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
  XMMATRIX view = XMMatrixLookAtRH(eye, at, up);

  float fov_angle_y = XMConvertToRadians(45 * 0.75);
  float aspect_ratio = 1.0;
  float near_z = 1.0;
  float far_z = 0.1;
  XMMATRIX projection = XMMatrixPerspectiveFovRH(fov_angle_y, aspect_ratio, near_z, far_z);
  XMMATRIX transform = view * projection;

  glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
  glClearDepth(-1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(test_program);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GREATER);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUniformMatrix4fv(location.uniform.transform, 1, false, (float *)&transform);
  glUniform1i(location.uniform.terrain_sampler, 0);

  //glBindBuffer(GL_UNIFORM_BUFFER, textures_ubo);
  //glBindBufferBase(GL_UNIFORM_BUFFER, 0, textures_ubo);

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
