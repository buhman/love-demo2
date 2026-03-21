#pragma once

namespace file {
  extern char const * source_path;
  extern int source_path_length;

  void const * read_file(const char * filename, int * out_size);

  void free(void const * buf);
}
