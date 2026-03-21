#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "glad/gl.h"
#include "opengl.h"
#include "file.h"
#include "dds_validate.h"

unsigned int compile(char const * vertex_source,
                     int vertex_source_size,
                     char const * geometry_source,
                     int geometry_source_size,
                     char const * fragment_source,
                     int fragment_source_size)
{
  int compile_status;
  char info_log[512];

  // program
  unsigned int shader_program = glCreateProgram();
  unsigned int vertex_shader = -1;
  unsigned int geometry_shader = -1;
  unsigned int fragment_shader = -1;

  // vertex shader
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, &vertex_source_size);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
  if (!compile_status) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    fprintf(stderr, "vertex shader compile: %s\n", info_log);
  }
  glAttachShader(shader_program, vertex_shader);

  // geometry shader
  if (geometry_source_size != 0) {
    geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_shader, 1, &geometry_source, &geometry_source_size);
    glCompileShader(geometry_shader);
    glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &compile_status);
    if (!compile_status) {
      glGetShaderInfoLog(geometry_shader, 512, NULL, info_log);
      fprintf(stderr, "geometry shader compile: %s\n", info_log);
    }
    glAttachShader(shader_program, geometry_shader);
  }

  // fragment shader
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, &fragment_source_size);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
  if (!compile_status) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    fprintf(stderr, "fragment shader compile: %s\n", info_log);
  }
  glAttachShader(shader_program, fragment_shader);

  // link shaders
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &compile_status);
  if (!compile_status) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    fprintf(stderr, "shader link: %s\n", info_log);
  }

  glDeleteShader(vertex_shader);
  if (geometry_source_size != 0)
    glDeleteShader(geometry_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

unsigned int compile_from_files(char const * vertex_path,
                                char const * geometry_path,
                                char const * fragment_path)
{
  int vertex_source_size = 0;
  void const * vertex_source = NULL;
  int geometry_source_size = 0;
  void const * geometry_source = NULL;
  int fragment_source_size = 0;
  void const * fragment_source = NULL;

  vertex_source = file::read_file(vertex_path, &vertex_source_size);
  assert(vertex_source != NULL);

  if (geometry_path != NULL) {
    geometry_source = file::read_file(geometry_path, &geometry_source_size);
    assert(geometry_source != NULL);
  }

  fragment_source = file::read_file(fragment_path, &fragment_source_size);
  assert(fragment_source != NULL);

  unsigned int program = compile((char const *)vertex_source, vertex_source_size,
                                 (char const *)geometry_source, geometry_source_size,
                                 (char const *)fragment_source, fragment_source_size);

  file::free(vertex_source);
  file::free(geometry_source);
  file::free(fragment_source);

  return program;
}

unsigned int load_uniform_buffer(char const * const path, int * out_size)
{
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_UNIFORM_BUFFER, buffer);

  int data_size;
  void const * data = file::read_file(path, &data_size);
  assert(data != NULL);

  glBufferData(GL_UNIFORM_BUFFER, data_size, data, GL_STATIC_DRAW);
  file::free(data);

  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  *out_size = data_size;

  return buffer;
}

void load_dds_texture_2D(char const * const path)
{
  fprintf(stderr, "load DDS texture: %s\n", path);

  int size;
  void const * data = file::read_file(path, &size);
  assert(data != NULL);

  void * image_data;
  int image_size;
  DDS_FILE const * dds = dds_validate(data, size, &image_data, &image_size);

  glCompressedTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
                         dds->header.dwWidth,
                         dds->header.dwHeight,
                         0,
                         image_size,
                         image_data);

  file::free(data);
}
