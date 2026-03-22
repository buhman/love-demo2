#pragma once

#include "directxmath/directxmath.h"

#include "collada/types.h"

namespace collada::instance_types {

  struct XM_ALIGNED_DATA(16) lookat {
    XMVECTOR eye;
    XMVECTOR at;
    XMVECTOR up;
  };

  struct XM_ALIGNED_DATA(16) transform {
    union {
      instance_types::lookat lookat;
      XMMATRIX matrix;
      XMVECTOR vector;
    };
    types::transform_type type;
  };

  struct node {
    // immutable state
    types::node const * node;

    // mutable state
    transform * transforms;
    XMMATRIX world;
  };
}
