#pragma once

#include <stdint.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct global_entry {
    int global_index;
    uint8_t block_id;
    uint8_t block_data;
    uint16_t _padding;
  } global_entry_t;
  static_assert((sizeof (global_entry_t)) == 8);

  void load_world();
  global_entry_t * const world_lookup(int x, int y, int z);

#ifdef __cplusplus
}
#endif
