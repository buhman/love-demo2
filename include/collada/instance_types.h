#pragma once

#include "directxmath/directxmath.h"

#include "collada/types.h"

namespace collada::instance_types {

  struct __attribute__((aligned(16))) lookat {
    XMVECTOR eye;
    XMVECTOR at;
    XMVECTOR up;
  };

  struct __attribute__((aligned(16))) transform {
    union {
      instance_types::lookat lookat;
      XMMATRIX matrix;
      XMVECTOR vector;
    };
    types::transform_type type;
  };

  struct node_instance {
    transform * transforms = NULL;
    XMMATRIX world;
  };
}
