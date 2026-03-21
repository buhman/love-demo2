#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

#include "pack.h"

static uint8_t copy_buffer[1024 * 1024];
static int const copy_buffer_size = (sizeof (copy_buffer));

void copy_file(FILE * output, FILE * input, size_t size)
{
  size_t written = 0;

  while (true) {
    size_t read_size = fread(copy_buffer, 1, copy_buffer_size, input);
    if (read_size == 0)
      break;

    size_t write_size = fwrite(copy_buffer, 1, read_size, output);
    assert(write_size == read_size);

    written += write_size;

    if (read_size < copy_buffer_size)
      break;
  }

  assert(written == size);
}

FILE * file_size(const char * filename, uint32_t * out_size)
{
  FILE * f = fopen(filename, "rb");
  if (f == nullptr) {
    fprintf(stderr, "fopen(%s): %s\n", filename, strerror(errno));
    return nullptr;
  }

  int fseek_end_ret = fseek(f, 0, SEEK_END);
  if (fseek_end_ret < 0) {
    fprintf(stderr, "fseek(%s, SEEK_END): %s\n", filename, strerror(errno));
    return nullptr;
  }

  long size = ftell(f);
  if (size < 0) {
    fprintf(stderr, "ftell(%s): %s\n", filename, strerror(errno));
    return nullptr;
  }

  int fseek_set_ret = fseek(f, 0, SEEK_SET);
  if (fseek_set_ret < 0) {
    fprintf(stderr, "fseek(%s, SEEK_SET): %s\n", filename, strerror(errno));
    return nullptr;
  }

  *out_size = size;

  return f;
}

int main(int argc, char const * argv[])
{
  assert(argc >= 3);

  int files_count = argc - 2;
  char const * output_filename = argv[1];
  char const * const * filenames = &argv[2];
  FILE * files[files_count];

  int header_size = (sizeof (pack::header)) + (sizeof (pack::file_entry)) * files_count;
  pack::header * header = (pack::header *)malloc(header_size);
  memset(header, 0, header_size);

  header->magic = pack::magic_value;
  header->header_size = header_size;
  header->entry_count = files_count;
  int offset = 0;

  for (int i = 0; i < files_count; i++) {
    char const * filename = filenames[i];
    uint32_t size;
    FILE * file = file_size(filename, &size);
    assert(file != nullptr);
    files[i] = file;
    int filename_length = strlen(filename);
    assert(filename_length <= 127);
    memcpy(header->entry[i].filename, filename, filename_length);
    header->entry[i].offset = offset;
    header->entry[i].size = size;
    offset += size;
  }

  FILE * fout = fopen(output_filename, "wb");
  if (fout == nullptr) {
    fprintf(stderr, "fopen(%s): %s\n", output_filename, strerror(errno));
    return EXIT_FAILURE;
  }

  fwrite((void *)header, 1, header_size, fout);

  for (int i = 0; i < files_count; i++) {
    copy_file(fout, files[i], header->entry[i].size);
    int fclose_ret = fclose(files[i]);
    assert(fclose_ret == 0);
  }

  int fclose_ret = fclose(fout);
  assert(fclose_ret == 0);
}
