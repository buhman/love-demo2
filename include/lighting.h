#pragma once

namespace lighting {

  struct light_parameters {
    float quadratic;
    float linear;
  };

  extern light_parameters global;

  void load_program();
  void load_light_uniform_buffer();
  void draw();
}
