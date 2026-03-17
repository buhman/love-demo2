#pragma once

#include "collada/types.h"

namespace collada::scene {
  struct static_skinned {
    unsigned int static_mesh;
    unsigned int skinned_mesh;
  };

  struct state {
    types::descriptor const * descriptor;

    unsigned int vertex_buffer_pnt;
    unsigned int vertex_buffer_jw;
    unsigned int index_buffer;

    static_skinned * vertex_arrays;
    int * vertex_buffer_strides;

    void load_layouts();
    void load_scene(types::descriptor const * const descriptor);

    void draw_geometry(types::geometry const & geometry,
                       types::instance_material const * const instance_materials,
                       int const instance_materials_count);
    void draw_instance_geometries(types::instance_geometry const * const instance_geometries,
                                  int const instance_geometries_count);
    void draw_node(types::node const & node);
    void draw();
  };
}
