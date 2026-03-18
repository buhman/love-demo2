#include "world/world.h"
#include "world/inthash.h"

namespace world {
  static vtx_cfg const love2dworld_vertex_paths[] = {
    { "minecraft/love2dworld/region.0.0.instance.vtx", "minecraft/love2dworld/region.0.0.instance.cfg" },
    { "minecraft/love2dworld/region.-1.0.instance.vtx", "minecraft/love2dworld/region.-1.0.instance.cfg" },
    { "minecraft/love2dworld/region.0.-1.instance.vtx", "minecraft/love2dworld/region.0.-1.instance.cfg" },
    { "minecraft/love2dworld/region.-1.-1.instance.vtx", "minecraft/love2dworld/region.-1.-1.instance.cfg" },
  };

  descriptor const descriptors[] = {
    [world_id::LOVE2DWORLD] = {
      .region_count = 4,
      .vertex_paths = love2dworld_vertex_paths,
      .entry_table_path = "minecraft/love2dworld/global.dump",
      .lights_path = "minecraft/love2dworld/global.lights.vtx",
      .hash_func = love2dworld_hash,
    },
  };
  int const descriptors_length = (sizeof (descriptors)) / (sizeof (descriptors[0]));
}
