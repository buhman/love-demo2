#include <assert.h>
#include <stdlib.h>

#include "glad/gl.h"

#include "file.h"
#include "opengl.h"

#include "flame.h"
#include "view.h"

extern unsigned int quad_index_buffer;
extern unsigned int empty_vertex_array_object;

namespace flame {
  static unsigned int program;
  static unsigned int flame_texture;
  static unsigned int vertex_array_object;

  const int per_instance_size = 4 * (sizeof (float));

  struct layout {
    struct {
      unsigned int flame_sampler;
      unsigned int frame;
      unsigned int transform;
      unsigned int eye;
    } uniform;
    struct {
      unsigned int lights;
    } binding;
  };

  layout layout = {
    .uniform = {
      .flame_sampler = 0,
      .frame = 1,
      .transform = 2,
      .eye = 3,
    },
    .binding = {
      .lights = 0,
    },
  };

  void load_program()
  {
    program = compile_from_files("shader/flame.vert",
                                 nullptr,
                                 "shader/flame.frag");
  }

  void load_texture()
  {
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int texture_data_size;
    void * texture_data = read_file("minecraft/flame.data", &texture_data_size);
    assert(texture_data != nullptr);

    int width = 16;
    int height = 80;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    free(texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    flame_texture = texture;
  }

  static int frame = 0;

  void draw(unsigned int light_uniform_buffer, int light_count)
  {
    glUseProgram(program);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, flame_texture);
    glUniform1i(layout.uniform.frame, (frame / 20) % 4);
    frame++;

    glUniformMatrix4fv(layout.uniform.transform, 1, false, (float *)&view::state.float_transform);
    XMFLOAT3 eye;
    XMStoreFloat3(&eye, view::state.eye);
    glUniform3fv(layout.uniform.eye, 1, (float *)&eye);

    glBindBufferBase(GL_UNIFORM_BUFFER, layout.binding.lights, light_uniform_buffer);

    glBindVertexArray(empty_vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0, light_count);
  }
}
