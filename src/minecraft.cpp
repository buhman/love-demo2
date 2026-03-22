#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "glad/gl.h"
#include "directxmath/directxmath.h"

#include "opengl.h"
#include "file.h"
#include "view.h"
#include "minecraft.h"
#include "minecraft_data.inc"
#include "new.h"
#include "popcount.h"
#include "world/world.h"

namespace minecraft {
  struct location {
    struct {
      unsigned int position;
      unsigned int normal;
      unsigned int texture;
      unsigned int block_position;
      unsigned int block_id;
      unsigned int data;
      unsigned int texture_id;
      unsigned int special;
    } attrib;
    struct {
      unsigned int transform;
      unsigned int terrain_sampler;
    } uniform;
  };

  static unsigned int program;
  static location location;

  static unsigned int vertex_array_object;
  static unsigned int per_vertex_buffer;

  static const int per_instance_size = (3 + 1 + 3 + 1) * 2;
  static const int per_vertex_size = (3 + 3 + 2) * 2;

  static unsigned int index_buffer;

  static unsigned int texture;

  static const int max_world_count = 10;
  static world::state world_state[max_world_count];
  world::state * current_world;

  void load_program()
  {
    program = compile_from_files("shader/minecraft.vert",
                                 NULL,
                                 "shader/minecraft.frag");

    location.attrib.position = glGetAttribLocation(program, "Position");
    location.attrib.normal = glGetAttribLocation(program, "Normal");
    location.attrib.texture = glGetAttribLocation(program, "Texture");

    location.attrib.block_position = glGetAttribLocation(program, "BlockPosition");
    location.attrib.block_id = glGetAttribLocation(program, "BlockID");
    location.attrib.data = glGetAttribLocation(program, "Data");
    location.attrib.texture_id = glGetAttribLocation(program, "TextureID");
    location.attrib.special = glGetAttribLocation(program, "Special");
    printf("minecraft program:\n");
    printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n  block_id %u\n  data %u\n  texture_id %u\n  special %u\n",
           location.attrib.position,
           location.attrib.normal,
           location.attrib.texture,
           location.attrib.block_position,
           location.attrib.block_id,
           location.attrib.data,
           location.attrib.texture_id,
           location.attrib.special);

    location.uniform.transform = glGetUniformLocation(program, "Transform");
    location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
    printf(" uniforms:\n  transform %u\n  terrain_sampler %u\n",
           location.uniform.transform,
           location.uniform.terrain_sampler);
  }

  void load_vertex_attributes()
  {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glVertexBindingDivisor(0, 0);
    glVertexBindingDivisor(1, 1);

    glEnableVertexAttribArray(location.attrib.position);
    glVertexAttribFormat(location.attrib.position, 3, GL_HALF_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(location.attrib.position, 0);

    glEnableVertexAttribArray(location.attrib.normal);
    glVertexAttribFormat(location.attrib.normal, 3, GL_HALF_FLOAT, GL_FALSE, 6);
    glVertexAttribBinding(location.attrib.normal, 0);

    glEnableVertexAttribArray(location.attrib.texture);
    glVertexAttribFormat(location.attrib.texture, 2, GL_HALF_FLOAT, GL_FALSE, 12);
    glVertexAttribBinding(location.attrib.texture, 0);

    glEnableVertexAttribArray(location.attrib.block_position);
    glVertexAttribFormat(location.attrib.block_position, 3, GL_SHORT, GL_FALSE, 0);
    glVertexAttribBinding(location.attrib.block_position, 1);

    glEnableVertexAttribArray(location.attrib.block_id);
    glVertexAttribIFormat(location.attrib.block_id, 1, GL_SHORT, 8);
    glVertexAttribBinding(location.attrib.block_id, 1);

    glEnableVertexAttribArray(location.attrib.data);
    glVertexAttribIFormat(location.attrib.data, 1, GL_SHORT, 10);
    glVertexAttribBinding(location.attrib.data, 1);

    glEnableVertexAttribArray(location.attrib.texture_id);
    glVertexAttribIFormat(location.attrib.texture_id, 1, GL_SHORT, 12);
    glVertexAttribBinding(location.attrib.texture_id, 1);

    glEnableVertexAttribArray(location.attrib.special);
    glVertexAttribIFormat(location.attrib.special, 1, GL_SHORT, 14);
    glVertexAttribBinding(location.attrib.special, 1);

    glBindVertexArray(0);
  }

  void load_per_vertex_buffer()
  {
    glGenBuffers(1, &per_vertex_buffer);

    int vertex_buffer_data_size;
    void const * vertex_buffer_data = file::read_file("minecraft/per_vertex.vtx", &vertex_buffer_data_size);

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

    file::free(vertex_buffer_data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load_index_buffer()
  {
    glGenBuffers(1, &index_buffer);

    int index_buffer_data_size;
    void const * index_buffer_data = file::read_file("minecraft/configuration.idx", &index_buffer_data_size);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);

    file::free(index_buffer_data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void load_texture()
  {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int texture_data_size;
    void const * texture_data = file::read_file("minecraft/terrain2.data", &texture_data_size);
    assert(texture_data != NULL);

    int width = 128;
    int height = 128;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    file::free(texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  //////////////////////////////////////////////////////////////////////
  // per-world load
  //////////////////////////////////////////////////////////////////////
  namespace per_world {
    static void load_instance_cfg(char const * path, world::instance_cfg_entry * entries)
    {
      int data_size;
      void const * data = file::read_file(path, &data_size);
      assert(data_size == (sizeof (struct world::instance_cfg_entry)) * world::instance_cfg_length);
      memcpy(entries, data, data_size);
      file::free(data);
    }

    static void load_per_instance_vertex_buffer(char const * path, unsigned int vertex_buffer)
    {
      int vertex_buffer_data_size;
      void const * vertex_buffer_data = file::read_file(path, &vertex_buffer_data_size); // vertex_paths[i].vtx

      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer); //per_instance_vertex_buffers[i]
      glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

      file::free(vertex_buffer_data);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    static void load_regions(world::descriptor const * const descriptor, world::region * region)
    {
      static int const max_region_count = 128;
      static unsigned int per_instance_vertex_buffers[max_region_count];

      assert(descriptor->region_count < max_region_count);
      glGenBuffers(descriptor->region_count, per_instance_vertex_buffers);
      for (int i = 0; i < descriptor->region_count; i++) {
        // vtx
        load_per_instance_vertex_buffer(descriptor->vertex_paths[i].vtx, per_instance_vertex_buffers[i]);
        region[i].per_instance_vertex_buffer = per_instance_vertex_buffers[i];

        // cfg
        load_instance_cfg(descriptor->vertex_paths[i].cfg, region[i].instance_cfg);
      }
    }

    void load_world(world::descriptor const * const descriptor, world::state & state)
    {
      state.descriptor = descriptor;
      state.region = New<world::region>(descriptor->region_count);
      load_regions(descriptor, state.region);

      int light_buffer_size;
      state.light_uniform_buffer = load_uniform_buffer(descriptor->lights_path, &light_buffer_size);
      state.light_count = light_buffer_size / ((sizeof (float)) * 4);

      // collision data
      world::entry_table::load_entry_table(descriptor->entry_table_path,
                                           &state.entry_table,
                                           &state.entry_table_length,
                                           descriptor->hash_func);
    }
  }

  void load()
  {
    //////////////////////////////////////////////////////////////////////
    // program
    //////////////////////////////////////////////////////////////////////

    load_program();
    load_vertex_attributes();

    //////////////////////////////////////////////////////////////////////
    // vertex/index buffers
    //////////////////////////////////////////////////////////////////////

    // per-vertex buffer
    load_per_vertex_buffer();

    // index buffer
    load_index_buffer();

    //////////////////////////////////////////////////////////////////////
    // textures
    //////////////////////////////////////////////////////////////////////

    load_texture();

    //////////////////////////////////////////////////////////////////////
    // worlds
    //////////////////////////////////////////////////////////////////////

    assert(max_world_count > world::descriptors_length);
    for (int i = 0; i < world::descriptors_length; i++) {
      per_world::load_world(&world::descriptors[i], world_state[i]);
    }
    current_world = &world_state[world::world_id::MIDNIGHTMEADOW];
  }

  static inline int popcount(int x)
  {
    return __builtin_popcount(x);
  }

  void draw()
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniformMatrix4fv(location.uniform.transform, 1, false, (float *)&view::state.float_transform);
    glUniform1i(location.uniform.terrain_sampler, 0);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    glBindVertexArray(vertex_array_object);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    for (int region_index = 0; region_index < current_world->descriptor->region_count; region_index++) {
      glBindVertexBuffer(1, current_world->region[region_index].per_instance_vertex_buffer, 0, per_instance_size);

      //////////////////////////////////////////////////////////////////////
      // cube blocks
      //////////////////////////////////////////////////////////////////////
      for (int configuration = 1; configuration < 64; configuration++) {
        int element_count = 6 * popcount(configuration);
        const void * indices = (void *)(2 * (ptrdiff_t)index_buffer_configuration_offsets[configuration]); // index into configuration.idx

        int instance_count = current_world->region[region_index].instance_cfg[configuration].count;
        int base_instance = current_world->region[region_index].instance_cfg[configuration].offset / per_instance_size; // index into region.0.0.instance.vtx

        if (instance_count == 0)
          continue;

        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, indices, instance_count, base_instance);
      }

      //////////////////////////////////////////////////////////////////////
      // custom blocks
      //////////////////////////////////////////////////////////////////////
      for (int i = 0; i < world::custom_block_types; i++) {
        int element_count = index_buffer_custom_offsets[i].count;
        const void * indices = (void *)(2 * (ptrdiff_t)index_buffer_custom_offsets[i].offset);
        int instance_count = current_world->region[region_index].instance_cfg[64 + i].count;
        int base_instance = current_world->region[region_index].instance_cfg[64 + i].offset / per_instance_size; // index into region.0.0.instance.vtx
        if (instance_count == 0)
          continue;
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, indices, instance_count, base_instance);
      }
    }
  }
}
