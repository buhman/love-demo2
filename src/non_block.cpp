#include <stdlib.h>
#include <stdio.h>

#include "glad/gl.h"
#include "directxmath/directxmath.h"

#include "opengl.h"
#include "file.h"
#include "view.h"
#include "non_block.h"

namespace non_block {
  unsigned int vertex_array_object;
  unsigned int index_buffer;
  unsigned int per_vertex_buffer;
  const int per_vertex_size = (3 + 3 + 2) * 2;

  struct location {
    struct {
      unsigned int position;
      unsigned int normal;
      unsigned int texture;
    } attrib;
    struct {
      unsigned int transform;
      unsigned int world_transform;
    } uniform;
  };
  location location;
  unsigned int program;

  void load_index_buffer()
  {
    glGenBuffers(1, &index_buffer);

    int index_buffer_data_size;
    void * index_buffer_data = read_file("minecraft/non_block.idx", &index_buffer_data_size);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);

    free(index_buffer_data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void load_per_vertex_buffer()
  {
    glGenBuffers(1, &per_vertex_buffer);

    int vertex_buffer_data_size;
    void * vertex_buffer_data = read_file("minecraft/non_block.vtx", &vertex_buffer_data_size);

    glBindBuffer(GL_ARRAY_BUFFER, per_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

    free(vertex_buffer_data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void load_vertex_attributes()
  {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glVertexBindingDivisor(0, 0);

    glEnableVertexAttribArray(location.attrib.position);
    glVertexAttribFormat(location.attrib.position, 3, GL_HALF_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(location.attrib.position, 0);

    glEnableVertexAttribArray(location.attrib.normal);
    glVertexAttribFormat(location.attrib.normal, 3, GL_HALF_FLOAT, GL_FALSE, 6);
    glVertexAttribBinding(location.attrib.normal, 0);

    glEnableVertexAttribArray(location.attrib.texture);
    glVertexAttribFormat(location.attrib.texture, 2, GL_HALF_FLOAT, GL_FALSE, 12);
    glVertexAttribBinding(location.attrib.texture, 0);

    glBindVertexArray(0);
  }

  void load_program()
  {
    program = compile_from_files("shader/non_block.vert",
                                 NULL,
                                 "shader/non_block.frag");

    location.attrib.position = glGetAttribLocation(program, "Position");
    location.attrib.normal = glGetAttribLocation(program, "Normal");
    location.attrib.texture = glGetAttribLocation(program, "Texture");

    printf("non_block program:\n");
    printf(" attributes:\n  position %u\n  normal %u\n  texture %u\n",
           location.attrib.position,
           location.attrib.normal,
           location.attrib.texture);

    location.uniform.world_transform = glGetUniformLocation(program, "WorldTransform");
    location.uniform.transform = glGetUniformLocation(program, "Transform");
    printf(" uniforms:\n  world_transform %u\n  transform %u\n",
           location.uniform.world_transform,
           location.uniform.transform);
  }

  void draw()
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    XMVECTOR offset = view::state.at;
    XMMATRIX world_transform = XMMatrixTranslationFromVector(offset);
    XMMATRIX transform = world_transform * view::state.transform;
    XMFLOAT4X4 float_world_transform;
    XMStoreFloat4x4(&float_world_transform, world_transform);
    XMFLOAT4X4 float_transform;
    XMStoreFloat4x4(&float_transform, transform);
    glUniformMatrix4fv(location.uniform.transform, 1, false, (float *)&float_transform);
    glUniformMatrix4fv(location.uniform.world_transform, 1, false, (float *)&float_world_transform);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBindVertexBuffer(0, per_vertex_buffer, 0, per_vertex_size);

    void const * indices = (void *)(0);
    int element_count = 300;
    glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, indices);
  }
}
