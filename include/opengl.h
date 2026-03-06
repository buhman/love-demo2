#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void * read_file(const char * filename, int * out_size);

unsigned int compile_from_files(const char * vertex_path,
                                const char * geometry_path,
                                const char * fragment_path);

#ifdef __cplusplus
}
#endif
