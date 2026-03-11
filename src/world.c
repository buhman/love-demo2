#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inthash.h"
#include "file.h"
#include "world.h"

static global_entry_t * global_entry_table = NULL;
static int global_entry_table_length = 0;

void load_world()
{
  int global_size;
  global_entry_t * entry = (global_entry_t *)read_file("minecraft/global.dump", &global_size);
  assert(entry != NULL);
  global_entry_table_length = global_size / (sizeof (global_entry_t));

  global_entry_table = calloc(global_entry_table_length, (sizeof (global_entry_t)));

  for (int i = 0; i < global_entry_table_length; i++) {
    uint32_t ix = inthash(entry[i].global_index);
    assert(global_entry_table[ix].global_index == 0);
    memcpy(&global_entry_table[ix], &entry[i], (sizeof (global_entry_t)));
  }

  free(entry);
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

global_entry_t * const world_lookup(int x, int y, int z)
{
  int global_index = global_index_from_xyz(x, y, z);
  int table_index = inthash(global_index);
  if (table_index < 0 || table_index >= global_entry_table_length)
    return NULL;
  global_entry_t * const entry = &global_entry_table[table_index];
  if (entry->global_index != global_index)
    return NULL;
  return entry;
}
