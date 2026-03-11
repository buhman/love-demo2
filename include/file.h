#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern char const * g_source_path;
extern int g_source_path_length;

void * read_file(const char * filename, int * out_size);

#ifdef __cplusplus
}
#endif
