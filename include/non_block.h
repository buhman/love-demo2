#pragma once

namespace non_block {
  extern unsigned int index_buffer;
  extern unsigned int per_vertex_buffer;
  extern unsigned int vertex_array_object;

  void load_index_buffer();
  void load_per_vertex_buffer();
  void load_vertex_attributes();
  void load_program();
  void draw();
}
