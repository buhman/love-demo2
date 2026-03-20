#pragma once

namespace flame {
  void load_program();
  void load_texture();
  void draw(unsigned int light_uniform_buffer, int light_count);
}
