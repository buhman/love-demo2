#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"
#include "opengl.h"
#include "directxmath/directxmath.h"
#include "test.h"

struct location {
  struct {
    unsigned int position;
    unsigned int block_id;
    unsigned int configuration;
  } attrib;
  struct {
    unsigned int transform;
    unsigned int terrain_sampler;
  } uniform;
};

// state
static unsigned int test_program;
static struct location location;

static unsigned int vertex_array_objects[4];
static unsigned int vertex_buffers[4];
static unsigned int vertex_count[4];
//static unsigned int index_buffers[4];
//static unsigned int index_count[4];

static const int vertex_size = 8;

void load_program()
{
  unsigned int program = compile_from_files("shader/test.vert",
                                            "shader/test.geom",
                                            "shader/test.frag");

  location.attrib.position = glGetAttribLocation(program, "Position");
  location.attrib.block_id = glGetAttribLocation(program, "BlockID");
  location.attrib.configuration = glGetAttribLocation(program, "Configuration");
  printf("attributes:\n  position %u\n  block_id %u\n  configuration %u\n",
         location.attrib.position,
         location.attrib.block_id,
         location.attrib.configuration);

  location.uniform.transform = glGetUniformLocation(program, "Transform");
  location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
  printf("uniforms:\n  transform %u\n  terrain_sampler %u\n",
         location.uniform.transform,
         location.uniform.terrain_sampler);

  test_program = program;
}

const char * vertex_paths[] = {
  "minecraft/region.0.0.inst.vtx",
  "minecraft/region.0.-1.inst.vtx",
  "minecraft/region.-1.0.inst.vtx",
  "minecraft/region.-1.-1.inst.vtx",
};

void load_vertex_buffer(int i)
{
  int vertex_buffer_data_size;
  void * vertex_buffer_data = read_file(vertex_paths[i], &vertex_buffer_data_size);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[i]);
  glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);
  vertex_count[i] = vertex_buffer_data_size / vertex_size;

  free(vertex_buffer_data);
}

/*
void load_element_buffer(int i)
{
  int index_buffer_data_size;
  void * index_buffer_data = read_file(index_paths[i], &index_buffer_data_size);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffers[i]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);
  index_count[i] = index_buffer_data_size / 4;

  free(index_buffer_data);
}
*/

void load_vertex_attributes()
{
  glVertexAttribPointer(location.attrib.position,
                        3,
                        GL_SHORT,
                        GL_FALSE,
                        vertex_size,
                        (void*)(0)
                        );
  glVertexAttribPointer(location.attrib.block_id,
                        1,
                        GL_UNSIGNED_BYTE,
                        GL_FALSE,
                        vertex_size,
                        (void*)(6)
                        );
  glVertexAttribPointer(location.attrib.configuration,
                        1,
                        GL_UNSIGNED_BYTE,
                        GL_FALSE,
                        vertex_size,
                        (void*)(7)
                        );
  glEnableVertexAttribArray(location.attrib.position);
  glEnableVertexAttribArray(location.attrib.block_id);
  glEnableVertexAttribArray(location.attrib.configuration);
  glVertexAttribDivisor(location.attrib.position, 1);
  glVertexAttribDivisor(location.attrib.block_id, 1);
  glVertexAttribDivisor(location.attrib.configuration, 1);
}

void load_buffers()
{
  glGenVertexArrays(4, vertex_array_objects);
  //glGenBuffers(4, index_buffers);
  glGenBuffers(4, vertex_buffers);

  for (int i = 0; i < 4; i++) {
    glBindVertexArray(vertex_array_objects[i]);

    //load_element_buffer(i);
    load_vertex_buffer(i);
    load_vertex_attributes();
  }
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

  printf("%d\n", textures_data_size);

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

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CCW);

  for (int i = 0; i < 4; i++) {
    glBindVertexArray(vertex_array_objects[i]);

    //glDrawElements(GL_TRIANGLES, index_count[i], GL_UNSIGNED_INT, 0);

    int instance_count = vertex_count[i];
    //printf("instance_count %d\n", instance_count);

    glPointSize(10.0);
    glDrawArraysInstanced(GL_POINTS,
                          0,
                          1,
                          instance_count);
  }
}
