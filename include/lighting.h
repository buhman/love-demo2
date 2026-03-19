#pragma once

namespace lighting {

  struct light_parameters {
    float quadratic;
    float linear;
  };

  extern light_parameters global;

  void load();
  void draw(unsigned int light_uniform_buffer, int light_count);
}
