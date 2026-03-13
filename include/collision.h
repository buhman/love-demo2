#pragma once

#include "directxmath/directxmath.h"

namespace collision {

  struct AABB {
    XMVECTOR min;
    XMVECTOR max;
  };

  static inline AABB cube_aabb(XMVECTOR const & center, float half)
  {
    half = fabsf(half);
    XMVECTOR min = center + XMVectorReplicate(-half);
    XMVECTOR max = center + XMVectorReplicate( half);
    return AABB(min, max);
  }

  static inline XMVECTOR closest_point_point_aabb(XMVECTOR const & p, AABB const & aabb)
  {
    return XMVectorClamp(p, aabb.min, aabb.max);
  }

}
