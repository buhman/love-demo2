#pragma once

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/node_state.h"

namespace collada::scene {
  struct static_skinned {
    unsigned int static_mesh;
    unsigned int skinned_mesh;
  };

  struct state {
    types::descriptor const * descriptor;
    node_state::state node_state;

    unsigned int vertex_buffer_pnt;
    unsigned int vertex_buffer_jw;
    unsigned int index_buffer;

    static_skinned * vertex_arrays;
    int * vertex_buffer_strides_pnt;

    unsigned int * textures;

    // drawing
    void load_layouts();
    void load_images();
    void load_scene(types::descriptor const * const descriptor);

    void set_color_or_texture(types::color_or_texture const& color_or_texture,
                              unsigned int color_uniform,
                              unsigned int texture_unit);
    void set_instance_material(types::instance_material const& instance_material);

    void draw_geometry(types::geometry const & geometry,
                       types::instance_material const * const instance_materials,
                       int const instance_materials_count);
    void draw_instance_geometries(types::instance_geometry const * const instance_geometries,
                                  int const instance_geometries_count);
    void draw_skin(types::skin const& skin,
                   types::instance_material const * const instance_materials,
                   int const instance_materials_count);
    void draw_instance_controllers(types::instance_controller const * const instance_controllers,
                                   int const instance_controllers_count);

    void draw_node(types::node const & node, instance_types::node const & node_instance);
    void draw();

    // state updates
    void update(float t);

    // query
    instance_types::node * find_node_by_name(char const * name);
  };
}
