#include <stdio.h>

#include "glad/gl.h"
#include "directxmath/directxmath.h"

#include "opengl.h"
#include "window.h"
#include "view.h"
#include "lighting.h"
#include "geometry_buffer.h"

extern unsigned int empty_vertex_array_object;
extern unsigned int quad_index_buffer;
extern geometry_buffer<3> geometry_buffer_pnc;

namespace lighting {

  light_parameters global = {
    .quadratic = 1.0,
    .linear = 1.0
  };

  struct location {
    struct {
      unsigned int position_sampler;
      unsigned int normal_sampler;
      unsigned int color_sampler;
      unsigned int quadratic;
      unsigned int linear;
      unsigned int eye;
      unsigned int light_count;

      unsigned int lights;
    } uniform;
    struct {
      unsigned int lights;
    } binding;
  };
  static unsigned int program;
  static location location;

  static void load_program()
  {
    program = compile_from_files("shader/quad.vert",
                                 NULL,
                                 "shader/lighting.frag");

    location.uniform.position_sampler = glGetUniformLocation(program, "PositionSampler");
    location.uniform.normal_sampler = glGetUniformLocation(program, "NormalSampler");
    location.uniform.color_sampler = glGetUniformLocation(program, "ColorSampler");
    location.uniform.quadratic = glGetUniformLocation(program, "Quadratic");
    location.uniform.linear = glGetUniformLocation(program, "Linear");
    location.uniform.eye = glGetUniformLocation(program, "Eye");
    location.uniform.light_count = glGetUniformLocation(program, "LightCount");
    location.uniform.lights = glGetUniformBlockIndex(program, "Lights");

    fprintf(stderr, "lighting program:\n");
    fprintf(stderr, " uniforms:\n  position_sampler %u  normal_sampler %u  color_sampler %u  quadratic %u\n  linear %u\n  eye %u\n  light_count %u\n  lights %u\n",
            location.uniform.position_sampler,
            location.uniform.normal_sampler,
            location.uniform.color_sampler,
            location.uniform.quadratic,
            location.uniform.linear,
            location.uniform.eye,
            location.uniform.light_count,
            location.uniform.lights);

    location.binding.lights = 0;
    glUniformBlockBinding(program, location.uniform.lights, location.binding.lights);
  }

  void load()
  {
    load_program();
  }

  static inline bool near_zero(float a)
  {
    return (fabsf(a) < 0.00001f);
  }

  void draw(unsigned int light_uniform_buffer, int light_count)
  {
    glUseProgram(program);
    glDepthFunc(GL_ALWAYS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, geometry_buffer_pnc.target[2]);

    glUniform1i(location.uniform.position_sampler, 0);
    glUniform1i(location.uniform.normal_sampler, 1);
    glUniform1i(location.uniform.color_sampler, 2);

    float quadratic = near_zero(global.quadratic) ? 0.0 : 1.0f / global.quadratic;
    float linear = near_zero(global.linear) ? 0.0 : 1.0f / global.linear;
    glUniform1f(location.uniform.quadratic, quadratic);
    glUniform1f(location.uniform.linear, linear);

    XMFLOAT3 eye;
    XMStoreFloat3(&eye, view::state.eye);
    glUniform3fv(location.uniform.eye, 1, (float*)&eye);

    glUniform1i(location.uniform.light_count, light_count);
    glBindBufferBase(GL_UNIFORM_BUFFER, location.binding.lights, light_uniform_buffer);

    glBindVertexArray(empty_vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void *)0);
  }

}
