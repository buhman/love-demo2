#include "opengl.h"

#include "collada/effect.h"

namespace collada::effect {

  unsigned int program_static;
  unsigned int program_skinned;

  void load_effects()
  {
    program_static = compile_from_files("shader/collada/static.vert",
                                        nullptr,
                                        "shader/collada/generic.frag");
  }
}
