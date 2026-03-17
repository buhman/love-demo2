#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  unsigned int compile_from_files(const char * vertex_path,
                                  const char * geometry_path,
                                  const char * fragment_path);

  unsigned int load_uniform_buffer(char const * const path);

  void load_dds_texture_2D(char const * const path);

#ifdef __cplusplus
}
#endif
