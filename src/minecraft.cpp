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

namespace minecraft {
  struct location {
    struct {
      unsigned int position;
      unsigned int normal;
      unsigned int texture;
      unsigned int block_position;
      unsigned int block_id;
      unsigned int data;
    } attrib;
    struct {
      unsigned int transform;
      unsigned int terrain_sampler;

      unsigned int texture_id;
    } uniform;
    struct {
      unsigned int texture_id;
    } binding;
  };

  static unsigned int program;
  static location location;

  struct char_tpl {
    const char * vtx;
    const char * cfg;
  };

  static const int region_count = 4;
  static const char_tpl vertex_paths[] = {
    { "minecraft/region.0.0.instance.vtx", "minecraft/region.0.0.instance.cfg" },
    { "minecraft/region.-1.0.instance.vtx", "minecraft/region.-1.0.instance.cfg" },
    { "minecraft/region.0.-1.instance.vtx", "minecraft/region.0.-1.instance.cfg" },
    { "minecraft/region.-1.-1.instance.vtx", "minecraft/region.-1.-1.instance.cfg" },
  };

  static unsigned int vertex_array_object;
  static unsigned int per_instance_vertex_buffers[region_count];
  static unsigned int per_vertex_buffer;

  static const int per_instance_size = 4 + (1 * 4);
  static const int per_vertex_size = (3 + 3 + 2) * 2;

  static unsigned int index_buffer;

  // also update index_buffer_custom_offsets in data.inc
  static const int custom_block_types = 5;
  static const int instance_cfg_length = 64 + custom_block_types;

  struct instance_cfg {
    struct region_instance {
      int instance_count;
      int offset;
    } cfg[instance_cfg_length];
  };

  static instance_cfg instance_cfg[region_count];

  static unsigned int texture;

  static unsigned int texture_id_uniform_buffer;

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
    printf("minecraft program:\n");
    printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n  block_position %u\n  block_id %u\n  data %u\n",
           location.attrib.position,
           location.attrib.normal,
           location.attrib.texture,
           location.attrib.block_position,
           location.attrib.block_id,
           location.attrib.data);

    location.uniform.transform = glGetUniformLocation(program, "Transform");
    location.uniform.terrain_sampler = glGetUniformLocation(program, "TerrainSampler");
    location.uniform.texture_id = glGetUniformBlockIndex(program, "TextureID");
    printf(" uniforms:\n  transform %u\n  terrain_sampler %u\n  texture_id %u\n",
           location.uniform.transform,
           location.uniform.terrain_sampler,
           location.uniform.texture_id);

    location.binding.texture_id = 0;
    glUniformBlockBinding(program, location.uniform.texture_id, location.binding.texture_id);
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
    glVertexAttribFormat(location.attrib.block_id, 1, GL_UNSIGNED_BYTE, GL_FALSE, 6);
    glVertexAttribBinding(location.attrib.block_id, 1);

    glEnableVertexAttribArray(location.attrib.data);
    glVertexAttribFormat(location.attrib.data, 1, GL_UNSIGNED_BYTE, GL_FALSE, 7);
    glVertexAttribBinding(location.attrib.data, 1);

    glBindVertexArray(0);
  }

  void load_per_instance_vertex_buffer(int i)
  {
    int vertex_buffer_data_size;
    void * vertex_buffer_data = read_file(vertex_paths[i].vtx, &vertex_buffer_data_size);

    glBindBuffer(GL_ARRAY_BUFFER, per_instance_vertex_buffers[i]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

    free(vertex_buffer_data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load_per_vertex_buffer()
  {
    glGenBuffers(1, &per_vertex_buffer);

    int vertex_buffer_data_size;
    void * vertex_buffer_data = read_file("minecraft/per_vertex.vtx", &vertex_buffer_data_size);

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

    free(vertex_buffer_data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load_index_buffer()
  {
    glGenBuffers(1, &index_buffer);

    int index_buffer_data_size;
    void * index_buffer_data = read_file("minecraft/configuration.idx", &index_buffer_data_size);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);

    free(index_buffer_data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void load_instance_cfg(int i)
  {
    int data_size;
    void * data = read_file(vertex_paths[i].cfg, &data_size);
    assert(data_size == (sizeof (struct instance_cfg)));

    memcpy(&instance_cfg[i], data, data_size);
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
    void * texture_data = read_file("minecraft/terrain.data", &texture_data_size);
    assert(texture_data != NULL);

    int width = 256;
    int height = 256;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    free(texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void load_texture_id_uniform_buffer()
  {
    texture_id_uniform_buffer = load_uniform_buffer("minecraft/block_id_to_texture_id.data");
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

    // per-instance buffer
    glGenBuffers(region_count, per_instance_vertex_buffers);
    for (int i = 0; i < region_count; i++) {
      load_per_instance_vertex_buffer(i);
      load_instance_cfg(i);
    }

    // index buffer
    load_index_buffer();

    //////////////////////////////////////////////////////////////////////
    // textures
    //////////////////////////////////////////////////////////////////////

    load_texture();

    //////////////////////////////////////////////////////////////////////
    // uniform buffers
    //////////////////////////////////////////////////////////////////////

    load_texture_id_uniform_buffer();
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

    glBindBufferBase(GL_UNIFORM_BUFFER, location.binding.texture_id, texture_id_uniform_buffer);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    glBindVertexArray(vertex_array_object);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    for (int region_index = 0; region_index < region_count; region_index++) {
      glBindVertexBuffer(1, per_instance_vertex_buffers[region_index], 0, per_instance_size);

      //////////////////////////////////////////////////////////////////////
      // cube blocks
      //////////////////////////////////////////////////////////////////////
      for (int configuration = 1; configuration < 64; configuration++) {
        int element_count = 6 * popcount(configuration);
        const void * indices = (void *)(2 * (ptrdiff_t)index_buffer_configuration_offsets[configuration]); // index into configuration.idx

        int instance_count = instance_cfg[region_index].cfg[configuration].instance_count;
        int base_instance = instance_cfg[region_index].cfg[configuration].offset / per_instance_size; // index into region.0.0.instance.vtx

        if (instance_count == 0)
          continue;

        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, indices, instance_count, base_instance);
      }

      //////////////////////////////////////////////////////////////////////
      // custom blocks
      //////////////////////////////////////////////////////////////////////
      for (int i = 0; i < custom_block_types; i++) {
        int element_count = index_buffer_custom_offsets[i].count;
        const void * indices = (void *)(2 * (ptrdiff_t)index_buffer_custom_offsets[i].offset);
        int instance_count = instance_cfg[region_index].cfg[64 + i].instance_count;
        int base_instance = instance_cfg[region_index].cfg[64 + i].offset / per_instance_size; // index into region.0.0.instance.vtx
        if (instance_count == 0)
          continue;
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, indices, instance_count, base_instance);
      }
    }
  }
}
