#pragma once

#include <stdint.h>
#include <assert.h>

namespace world::entry_table {

  typedef struct global_entry {
    int global_index;
    uint8_t block_id;
    uint8_t block_data;
    uint16_t _padding;
  } global_entry_t;
  static_assert((sizeof (global_entry_t)) == 8);

  typedef uint32_t (hash_func_t)(const int32_t key);

  void load_entry_table(char const * const path,
                        global_entry_t ** out_entry_table,
                        int * out_entry_table_length,
                        hash_func_t * hash_func);

  global_entry_t * const world_lookup(hash_func_t * hash_func,
                                      global_entry_t * entry_table,
                                      int entry_table_length,
                                      int x, int y, int z);
}
