#pragma once

#include <float.h>
#include <stdio.h>

#include "directxmath/directxmath.h"

namespace collision {

  struct AABB {
    XMVECTOR min;
    XMVECTOR max;
  };

  struct Sphere {
    XMVECTOR center;
    float radius;
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

  static inline bool test_sphere_aabb(Sphere const & sphere, AABB const & aabb, XMVECTOR & point)
  {
    point = closest_point_point_aabb(sphere.center, aabb);

    XMVECTOR v = point - sphere.center;
    return XMVectorGetX(XMVector3Dot(v, v)) <= sphere.radius * sphere.radius;
  }

  static inline void vector_swap_control(XMVECTOR & a, XMVECTOR & b, XMVECTOR const & control)
  {
    XMVECTOR tmp = XMVectorSelect(a, b, control);
    b = XMVectorSelect(b, a, control);
    a = tmp;
  }

  static inline bool intersect_ray_aabb(XMVECTOR const & point, XMVECTOR const & direction, AABB const & aabb, float & t_result, XMVECTOR & v_result)
  {
    // check parallel
    XMVECTOR parallel = XMVectorLess(XMVectorAbs(direction), XMVectorSplatEpsilon());
    XMVECTOR point_lt_aabb = XMVectorLess(point, aabb.min);
    XMVECTOR point_gt_aabb = XMVectorGreater(point, aabb.max);
    if (XMVectorGetX(parallel) != 0) // if (x < epsilon)
      if (XMVectorGetX(point_lt_aabb) != 0 || XMVectorGetX(point_gt_aabb) != 0)
        return false; // direction x is parallel and point x outside aabb
    if (XMVectorGetY(parallel) != 0) // if (y < epsilon)
      if (XMVectorGetY(point_lt_aabb) != 0 || XMVectorGetY(point_gt_aabb) != 0)
        return false; // direction y is parallel and point y outside aabb
    if (XMVectorGetZ(parallel) != 0) // if (z < epsilon)
      if (XMVectorGetZ(point_lt_aabb) != 0 || XMVectorGetZ(point_gt_aabb) != 0)
        return false; // direction z is parallel and point z outside aabb

    XMVECTOR direction_reciprocal = XMVectorReciprocalEst(direction);
    XMVECTOR t1 = (aabb.min - point) * direction_reciprocal;
    XMVECTOR t2 = (aabb.max - point) * direction_reciprocal;
    vector_swap_control(t2, t1, XMVectorGreater(t1, t2));

    float tmin = XMVectorGetX(t1);
    if (XMVectorGetY(t1) > tmin) tmin = XMVectorGetY(t1);
    if (XMVectorGetZ(t1) > tmin) tmin = XMVectorGetZ(t1);
    float tmax = XMVectorGetX(t2);
    if (XMVectorGetY(t2) < tmax) tmax = XMVectorGetY(t2);
    if (XMVectorGetZ(t2) < tmax) tmax = XMVectorGetZ(t2);
    if (tmin > tmax) return false; // no intersection

    t_result = tmin;
    v_result = point + direction * tmin;

    return true;
  }
}
