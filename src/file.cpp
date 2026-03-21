#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "file.h"

namespace file {
  char const * source_path = NULL;
  int source_path_length = 0;

#ifdef READ_PACK_FILE
#include "pack.h"
  extern "C" {
    extern uint8_t const _binary_test_pack_start[];
    extern uint8_t const _binary_test_pack_end[];
    extern int const _binary_test_pack_size;
  };

  void const * read_file(const char * r_filename, int * out_size)
  {
    pack::header const * header = (pack::header const *)&_binary_test_pack_start[0];
    assert(header->magic == pack::magic_value);
    ptrdiff_t data = (ptrdiff_t)&_binary_test_pack_start[header->header_size];

    for (unsigned int i = 0; i < header->entry_count; i++) {
      if (strcmp(header->entry[i].filename, r_filename) == 0) {
        *out_size = header->entry[i].size;
        return (void const *)(data + header->entry[i].offset);
      }
    }
    fprintf(stderr, "filename not found in pack file %s\n", r_filename);
    assert(false);
  }

  void free(void const * buf)
  {
    (void)buf;
  }
#else
  static char const * join_path(char * buf, const char * filename)
  {
    if (filename[0] == '/')
      return filename;

    int filename_length = strlen(filename);
    assert(filename_length + source_path_length + 2 < 1024);

    memcpy(buf, source_path, source_path_length);
    buf[source_path_length] = '/';

    memcpy(&buf[source_path_length + 1], filename, filename_length);
    buf[source_path_length + 1 + filename_length] = 0;
    return buf;
  }

  void const * read_file(const char * r_filename, int * out_size)
  {
    fprintf(stderr, "r_filename: %s\n", r_filename);

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

    size_t size = ftell(f);
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

  void free(void const * buf)
  {
    ::free((void *)buf);
  }
#endif
}
