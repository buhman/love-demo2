#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "file.h"

char const * g_source_path = NULL;
int g_source_path_length = 0;

char const * join_path(char * buf, const char * filename)
{
  if (filename[0] == '/')
    return filename;

  int filename_length = strlen(filename);
  assert(filename_length + g_source_path_length + 2 < 1024);

  memcpy(buf, g_source_path, g_source_path_length);
  buf[g_source_path_length] = '/';

  memcpy(&buf[g_source_path_length + 1], filename, filename_length);
  buf[g_source_path_length + 1 + filename_length] = 0;
  return buf;
}

void * read_file(const char * r_filename, int * out_size)
{
  char tmp[1024];
  char const * filename = join_path(tmp, r_filename);

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
