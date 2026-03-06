#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "glad/gl.h"
#include "opengl.h"

void * read_file(const char * filename, int * out_size)
{
  FILE * f = fopen(filename, "rb");
  if (f == NULL) {
    fprintf(stderr, "fopen(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  int fseek_end_ret = fseek(f, 0, SEEK_END);
  if (fseek_end_ret < 0) {
    fprintf(stderr, "fseek(%s, SEEK_END): %s\n", filename, strerror(errno));
    return NULL;
  }

  long size = ftell(f);
  if (size < 0) {
    fprintf(stderr, "ftell(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  int fseek_set_ret = fseek(f, 0, SEEK_SET);
  if (fseek_set_ret < 0) {
    fprintf(stderr, "lseek(%s, SEEK_SET): %s\n", filename, strerror(errno));
    return NULL;
  }
  rewind(f);

  void * buf = malloc(size);

  size_t read_size = fread(buf, 1, size, f);
  if (read_size != size) {
    fprintf(stderr, "fread(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  *out_size = size;

  return buf;
}

unsigned int compile(const char * vertex_source,
                     int vertex_source_size,
                     const char * geometry_source,
                     int geometry_source_size,
                     const char * fragment_source,
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

unsigned int compile_from_files(const char * vertex_path,
                                const char * geometry_path,
                                const char * fragment_path)
{
  int vertex_source_size = 0;
  char * vertex_source = NULL;
  int geometry_source_size = 0;
  char * geometry_source = NULL;
  int fragment_source_size = 0;
  char * fragment_source = NULL;

  vertex_source = read_file(vertex_path, &vertex_source_size);
  assert(vertex_source != NULL);

  if (geometry_path != NULL) {
    geometry_source = read_file(geometry_path, &geometry_source_size);
    assert(geometry_source != NULL);
  }

  fragment_source = read_file(fragment_path, &fragment_source_size);
  assert(fragment_source != NULL);

  unsigned int program = compile(vertex_source, vertex_source_size,
                                 geometry_source, geometry_source_size,
                                 fragment_source, fragment_source_size);

  free(vertex_source);
  free(geometry_source);
  free(fragment_source);

  return program;
}
