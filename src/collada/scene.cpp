#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "glad/gl.h"
#include "directxmath/directxmath.h"

#include "new.h"
#include "file.h"
#include "view.h"
#include "opengl.h"

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/scene.h"
#include "collada/effect.h"

namespace collada::scene {

  struct layout {
    struct {
      unsigned int position;
      unsigned int normal;
      unsigned int texture;
      unsigned int blend_indices;
      unsigned int blend_weight;
    } attribute;
    struct {
      // vertex
      unsigned int transform;
      // fragment
      unsigned int emission_color;
      unsigned int ambient_color;
      unsigned int diffuse_color;
      unsigned int specular_color;

      unsigned int shininess;

      unsigned int emission_sampler;
      unsigned int ambient_sampler;
      unsigned int diffuse_sampler;
      unsigned int specular_sampler;

      unsigned int texture_channels;
    } uniform;
    struct {
      unsigned int emission;
      unsigned int ambient;
      unsigned int diffuse;
      unsigned int specular;
    } texture_unit;
  };

  const layout layout = {
    .attribute = {
      .position = 0,
      .normal = 1,
      .texture = 2,
      .blend_indices = 3,
      .blend_weight = 4,
    },
    .uniform = {
      // vertex
      .transform = 0,
      // fragment
      .emission_color = 10,
      .ambient_color = 11,
      .diffuse_color = 12,
      .specular_color = 13,

      .shininess = 14,

      .emission_sampler = 15,
      .ambient_sampler = 16,
      .diffuse_sampler = 17,
      .specular_sampler = 18,

      .texture_channels = 19,
    },
    .texture_unit {
      .emission = GL_TEXTURE0,
      .ambient = GL_TEXTURE1,
      .diffuse = GL_TEXTURE2,
      .specular = GL_TEXTURE3,
    },
  };

  unsigned int attribute_location(char const * const semantic,
                                  int semantic_index)
  {
    if (strcmp(semantic, "POSITION") == 0 && semantic_index == 0) {
      return layout.attribute.position;
    }
    if (strcmp(semantic, "NORMAL") == 0 && semantic_index == 0) {
      return layout.attribute.normal;
    }
    if (strcmp(semantic, "TEXCOORD") == 0 && semantic_index == 0) {
      return layout.attribute.texture;
    }
    if (strcmp(semantic, "BLENDINDICES") == 0 && semantic_index == 0) {
      return layout.attribute.blend_indices;
    }
    if (strcmp(semantic, "BLENDWEIGHT") == 0 && semantic_index == 0) {
      return layout.attribute.blend_weight;
    }
    printf("unknown semantic %s index %d\n",semantic, semantic_index);
    assert(false);
  }

  unsigned int input_format_gl_size(types::input_format format)
  {
    switch (format) {
    case types::input_format::FLOAT1: return 1;
    case types::input_format::FLOAT2: return 2;
    case types::input_format::FLOAT3: return 3;
    case types::input_format::FLOAT4: return 4;
    case types::input_format::INT1: return 1;
    case types::input_format::INT2: return 2;
    case types::input_format::INT3: return 3;
    case types::input_format::INT4: return 4;
    default: assert(false);
    }
  }

  unsigned int input_format_gl_type(types::input_format format)
  {
    switch (format) {
    case types::input_format::FLOAT1: return GL_FLOAT;
    case types::input_format::FLOAT2: return GL_FLOAT;
    case types::input_format::FLOAT3: return GL_FLOAT;
    case types::input_format::FLOAT4: return GL_FLOAT;
    case types::input_format::INT1: return GL_INT;
    case types::input_format::INT2: return GL_INT;
    case types::input_format::INT3: return GL_INT;
    case types::input_format::INT4: return GL_INT;
    default: assert(false);
    }
  }

  // return stride
  static inline int load_layout(types::inputs const & inputs,
                                int binding,
                                int start_offset,
                                unsigned int vertex_array)
  {
    glBindVertexArray(vertex_array);
    int offset = start_offset;
    for (int i = 0; i < inputs.elements_count; i++) {
      unsigned int location = attribute_location(inputs.elements[i].semantic, inputs.elements[i].semantic_index);
      glEnableVertexAttribArray(location);
      unsigned int gl_size = input_format_gl_size(inputs.elements[i].format);
      unsigned int gl_type = input_format_gl_type(inputs.elements[i].format);
      glVertexAttribFormat(location, gl_size, gl_type, GL_FALSE, offset);
      glVertexAttribBinding(location, binding);
      offset += gl_size * 4;
    }
    int stride = offset - start_offset;
    glBindVertexArray(0);
    return stride;
  }

  types::input_element const input_elements_blendindices_0_4_blendweight_0_4[] = {
    {
      .semantic = "BLENDINDICES",
      .semantic_index = 0,
      .format = types::input_format::INT4,
    },
    {
      .semantic = "BLENDWEIGHT",
      .semantic_index = 0,
      .format = types::input_format::FLOAT4,
    },
  };

  types::inputs const skin_inputs = {
    .elements = input_elements_blendindices_0_4_blendweight_0_4,
    .elements_count = 2,
  };

  void state::load_layouts()
  {
    vertex_arrays = New<static_skinned>(descriptor->inputs_list_count);
    vertex_buffer_strides = New<int>(descriptor->inputs_list_count);

    glGenVertexArrays(2 * descriptor->inputs_list_count, (unsigned int *)vertex_arrays);

    for (int i = 0; i < descriptor->inputs_list_count; i++) {
      // static
      int stride = load_layout(descriptor->inputs_list[i],
                               0, // binding
                               0, // start_offset
                               vertex_arrays[i].static_mesh);
      vertex_buffer_strides[i] = stride;

      // skinned
      load_layout(descriptor->inputs_list[i],
                  0, // binding
                  0, // start_offset
                  vertex_arrays[i].skinned_mesh);
      load_layout(skin_inputs,
                  1, // binding
                  0, // start_offset
                  vertex_arrays[i].skinned_mesh);
    }
  }

  unsigned int load_vertex_buffer(const char * filename)
  {
    int size;
    void * data = read_file(filename, &size);
    assert(data != NULL);
    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    free(data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertex_buffer;
  }

  unsigned int load_index_buffer(const char * filename)
  {
    int size;
    void * data = read_file(filename, &size);
    assert(data != NULL);
    printf("%s %d\n", filename, size);

    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    free(data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return index_buffer;
  }

  void state::load_images()
  {
    textures = New<unsigned int>(descriptor->images_count);
    glGenTextures(descriptor->images_count, textures);

    for (int i = 0; i < descriptor->images_count; i++) {
      types::image const * const image = descriptor->images[i];

      glBindTexture(GL_TEXTURE_2D, textures[i]);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      load_dds_texture_2D(image->resource_name);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void state::load_scene(types::descriptor const * const descriptor)
  {
    this->descriptor = descriptor;

    load_layouts();

    vertex_buffer_pnt = load_vertex_buffer(descriptor->position_normal_texture_buffer);
    vertex_buffer_jw = load_vertex_buffer(descriptor->joint_weight_buffer);
    index_buffer = load_index_buffer(descriptor->index_buffer);

    load_images();
  }

  void state::set_color_or_texture(types::color_or_texture const& color_or_texture,
                                   unsigned int color_uniform,
                                   unsigned int texture_unit)
  {
    switch (color_or_texture.type) {
    case types::color_or_texture_type::COLOR:
      glUniform4fv(color_uniform, 1, (float *)&color_or_texture.color);
      break;
    case types::color_or_texture_type::TEXTURE:
      glActiveTexture(texture_unit);
      glBindTexture(GL_TEXTURE_2D, textures[color_or_texture.texture.image_index]);
      break;
    default:
      assert(false);
    }
  }

  void state::set_instance_material(types::instance_material const& instance_material)
  {
    types::effect const& effect = *instance_material.material->effect;
    switch (effect.type) {
    case types::effect_type::BLINN:
      set_color_or_texture(effect.blinn.emission, layout.uniform.emission_color, layout.texture_unit.emission);
      set_color_or_texture(effect.blinn.ambient, layout.uniform.ambient_color, layout.texture_unit.ambient);
      set_color_or_texture(effect.blinn.diffuse, layout.uniform.diffuse_color, layout.texture_unit.diffuse);
      set_color_or_texture(effect.blinn.specular, layout.uniform.specular_color, layout.texture_unit.specular);
      glUniform1f(layout.uniform.shininess, effect.blinn.shininess);
      break;
    case types::effect_type::LAMBERT:
      set_color_or_texture(effect.lambert.emission, layout.uniform.emission_color, layout.texture_unit.emission);
      set_color_or_texture(effect.lambert.ambient, layout.uniform.ambient_color, layout.texture_unit.ambient);
      set_color_or_texture(effect.lambert.diffuse, layout.uniform.diffuse_color, layout.texture_unit.diffuse);
      break;
    case types::effect_type::PHONG:
      set_color_or_texture(effect.phong.emission, layout.uniform.emission_color, layout.texture_unit.emission);
      set_color_or_texture(effect.phong.ambient, layout.uniform.ambient_color, layout.texture_unit.ambient);
      set_color_or_texture(effect.phong.diffuse, layout.uniform.diffuse_color, layout.texture_unit.diffuse);
      set_color_or_texture(effect.phong.specular, layout.uniform.specular_color, layout.texture_unit.specular);
      glUniform1f(layout.uniform.shininess, effect.phong.shininess);
      break;
    case types::effect_type::CONSTANT:
      glUniform4fv(layout.uniform.emission_color, 1, (float *)&effect.constant.color);
      break;
    default:
      break;
    }

    int texture_channels[4] = {
      instance_material.emission.input_set,
      instance_material.ambient.input_set,
      instance_material.diffuse.input_set,
      instance_material.specular.input_set,
    };
    glUniform4iv(layout.uniform.texture_channels, 1, texture_channels);
  }

  void state::draw_geometry(types::geometry const & geometry,
                            types::instance_material const * const instance_materials,
                            int const instance_materials_count)
  {
    glUseProgram(collada::effect::program_static);

    types::mesh const& mesh = geometry.mesh;

    for (int j = 0; j < instance_materials_count; j++) {
      //if (j != 1)
      //continue;

      types::instance_material const& instance_material = instance_materials[j];
      types::triangles const& triangles = mesh.triangles[instance_material.element_index];

      set_instance_material(instance_material);

      unsigned int vertex_buffer_offset = mesh.vertex_buffer_offset;
      unsigned int vertex_buffer_stride = vertex_buffer_strides[triangles.inputs_index];
      unsigned int vertex_array = vertex_arrays[triangles.inputs_index].static_mesh;

      glBindVertexArray(vertex_array);
      glBindVertexBuffer(0, vertex_buffer_pnt, vertex_buffer_offset, vertex_buffer_stride);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

      unsigned int index_count = triangles.count * 3;
      unsigned int indices = triangles.index_offset * (sizeof (unsigned int)) + mesh.index_buffer_offset;

      unsigned int instance_count = 1;
      unsigned int base_vertex = 0;
      unsigned int base_instance = 0;
      glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES,
                                                    index_count,
                                                    GL_UNSIGNED_INT,
                                                    (void *)((ptrdiff_t)indices),
                                                    instance_count,
                                                    base_vertex,
                                                    base_instance);
    }
  }

  void state::draw_instance_geometries(types::instance_geometry const * const instance_geometries,
                                       int const instance_geometries_count)
  {
    for (int i = 0; i < instance_geometries_count; i++) {
      types::instance_geometry const &instance_geometry = instance_geometries[i];
      draw_geometry(*instance_geometry.geometry,
                    instance_geometry.instance_materials,
                    instance_geometry.instance_materials_count);
    }
  }

  void state::draw_node(types::node const & node)
  {
    draw_instance_geometries(node.instance_geometries, node.instance_geometries_count);
  }

  void state::draw()
  {
    glUseProgram(collada::effect::program_static);
    glUniformMatrix4fv(layout.uniform.transform, 1, false, (float *)&view::state.float_transform);
    glUniform1i(layout.uniform.emission_sampler, 0);
    glUniform1i(layout.uniform.ambient_sampler, 1);
    glUniform1i(layout.uniform.diffuse_sampler, 2);
    glUniform1i(layout.uniform.specular_sampler, 3);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    for (int i = 0; i < descriptor->nodes_count; i++) {
      types::node const & node = *descriptor->nodes[i];

      // joints are not drawn
      if (node.type != types::node_type::NODE)
        continue;

      draw_node(node);
    }
  }
}
