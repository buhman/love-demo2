#pragma once

#include <stdint.h>

#include "world/entry_table.h"

namespace world {
  struct vtx_cfg {
    const char * vtx;
    const char * cfg;
  };

  struct descriptor {
    int const region_count;
    vtx_cfg const * const vertex_paths;
    char const * const entry_table_path;
    char const * const lights_path;
    entry_table::hash_func_t * hash_func;
  };

  struct world_id {
    enum {
      GRANDLECTURN = 0,
      MIDNIGHTMEADOW = 1,
    };
  };

  // also update index_buffer_custom_offsets in include/minecraft_data.inc
  const int custom_block_types = 6;
  const int instance_cfg_length = 64 + custom_block_types;

  struct instance_cfg_entry {
    int count;
    int offset;
  };

  struct region {
    unsigned int per_instance_vertex_buffer;
    instance_cfg_entry instance_cfg[instance_cfg_length];
  };

  struct state {
    world::descriptor const * descriptor;
    world::region * region; // malloc region_count
    entry_table::global_entry_t * entry_table;
    unsigned int light_uniform_buffer;
    int light_count;
    int entry_table_length;
  };

  extern descriptor const descriptors[];
  extern int const descriptors_length;
}
