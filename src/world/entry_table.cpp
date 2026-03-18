#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "file.h"
#include "new.h"
#include "world/entry_table.h"

namespace world::entry_table {

  void load_entry_table(char const * const path,
                        global_entry_t ** out_entry_table,
                        int * out_entry_table_length,
                        hash_func_t * hash_func)
  {
    int global_size;
    global_entry_t * entry = (global_entry_t *)read_file(path, &global_size);
    assert(entry != NULL);
    int entry_table_length = global_size / (sizeof (global_entry_t));

    global_entry_t * entry_table = New<global_entry_t>(entry_table_length);
    memset(entry_table, 0, global_size);

    for (int i = 0; i < entry_table_length; i++) {
      uint32_t ix = hash_func(entry[i].global_index);
      assert(entry_table[ix].global_index == 0);
      memcpy(&entry_table[ix], &entry[i], (sizeof (global_entry_t)));
    }

    free(entry);

    *out_entry_table = entry_table;
    *out_entry_table_length = entry_table_length;
  }

  static inline int global_index_from_xyz(int x, int y, int z)
  {
    const int g_stride = 512 * 2;
    if (x < 0)
      x = -(x - 511);
    if (z < 0)
      z = -(z - 511);
    return x + z * g_stride + y * g_stride * g_stride;
  }

  global_entry_t * const world_lookup(hash_func_t * hash_func,
                                      global_entry_t * entry_table,
                                      int entry_table_length,
                                      int x, int y, int z)
  {
    int global_index = global_index_from_xyz(x, y, z);
    int table_index = hash_func(global_index);
    if (table_index < 0 || table_index >= entry_table_length)
      return NULL;
    global_entry_t * const entry = &entry_table[table_index];
    if (entry->global_index != global_index)
      return NULL;
    return entry;
  }
}
