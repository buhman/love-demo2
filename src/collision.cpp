#include "directxmath/directxmath.h"

struct AABB {
  XMVECTOR min;
  XMVECTOR max;
};

XMVECTOR closest_point_point_aabb(XMVECTOR const &p, AABB const& aabb)
{
  return XMVectorClamp(p, aabb.min, aabb.max);
}
