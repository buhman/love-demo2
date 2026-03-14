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

  struct Capsule {
    XMVECTOR a;
    XMVECTOR b;
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

  static inline float clamp(float f, float min, float max)
  {
    if (f < min) return min;
    if (f > max) return max;
    return f;
  }

  static inline void closest_point_segment_segment(XMVECTOR const & a1, XMVECTOR const & b1, // segment 1
                                                   XMVECTOR const & a2, XMVECTOR const & b2, // segment 2
                                                   float & t1, // (s)
                                                   float & t2, // (t)
                                                   XMVECTOR & c1, // closest point to segment 1
                                                   XMVECTOR & c2) // closest point to segment 2
  {
    const float epsilon = 1.192092896e-7f;

    XMVECTOR d1 = b1 - a1;
    XMVECTOR d2 = b2 - a2;
    XMVECTOR r = a1 - a2;
    float l1 = XMVectorGetX(XMVector3Dot(d1, d1)); // squared length of segment 1 (a)
    float l2 = XMVectorGetX(XMVector3Dot(d2, d2)); // squared length of segment 2 (e)
    float d1r = XMVectorGetX(XMVector3Dot(d1, r)); // (c)
    float d2r = XMVectorGetX(XMVector3Dot(d2, r)); // (f)

    if (l1 <= epsilon && l2 <= epsilon) {
      // both segments are points
      t1 = 0.0f;
      t2 = 0.0f;
      c1 = a1;
      c2 = a2;
      return;
    }
    if (l1 <= epsilon) {
      // segment 1 is a point
      t1 = 0.0f;
      t2 = clamp(d2r / l2, 0.0f, 1.0f);
    } else if (l2 <= epsilon) {
      // segment 2 is a point
      t1 = clamp(-d1r / l1, 0.0, 1.0f);
      t2 = 0.0f;
    } else {
      float b = XMVectorGetX(XMVector3Dot(d1, d2));
      float denom = l1 * l2 - b * b;
      if (denom != 0.0f) {
        // segments are not parallel
        t1 = clamp((b * d2r - d1r * l2) / denom, 0.0f, 1.0f);
      } else {
        t1 = 0.0f;
      }
      t2 = (b * t1 + d2r) / l2;
      if (t2 < 0.0f) {
        t2 = 0.0f;
        t1 = clamp(-d1r / l1, 0.0f, 1.0f);
      } else if (t2 > 1.0f) {
        t2 = 1.0f;
        t1 = clamp((b - d1r) / l1, 0.0f, 1.0f);
      }
    }

    c1 = a1 + d1 * t1;
    c2 = a2 + d2 * t2;
  }

  static inline bool intersect_capsule_capsule(Capsule const & capsule1, Capsule const & capsule2,
                                               XMVECTOR & p1, XMVECTOR & p2)
  {
    float t1;
    float t2;
    XMVECTOR c1; // closest point in capsule1
    XMVECTOR c2; // closest point in capsule2
    closest_point_segment_segment(capsule1.a, capsule1.b,
                                  capsule2.a, capsule2.b,
                                  t1, t2,
                                  c1, c2);
    float distance2 = XMVectorGetX(XMVector3Dot(c1 - c2, c1 - c2));
    float radius = capsule1.radius + capsule2.radius;
    if (distance2 >= radius * radius)
      return false;

    float length = XMVectorGetX(XMVector3Length(c1 - c2));
    XMVECTOR normal = XMVector3NormalizeEst(c2 - c1);
    printf("length2 %f\n", capsule1.radius - length);
    p1 = c1 + normal * capsule1.radius;
    p2 = c2 + normal;

    return true;
  }

  static inline bool intersect_moving_sphere_aabb(Sphere const & sphere, XMVECTOR const & direction, AABB const & aabb, float & t)
  {
    AABB expand(expand.min - XMVectorReplicate(sphere.radius),
                expand.max + XMVectorReplicate(sphere.radius));

    // intersect ray against expand
    XMVECTOR point;
    bool intersection = intersect_ray_aabb(sphere.center, direction, expand, t, point);
    if (!intersection || t > 1.0f)
      return false;

    XMVECTOR lt = XMVectorLess(point, aabb.min);
    int u = 0;
    if (XMVectorGetX(lt) != 0) u |= 1;
    if (XMVectorGetY(lt) != 0) u |= 2;
    if (XMVectorGetZ(lt) != 0) u |= 4;
    XMVECTOR gt = XMVectorGreater(point, aabb.max);
    int v = 0;
    if (XMVectorGetX(gt) != 0) v |= 1;
    if (XMVectorGetY(gt) != 0) v |= 2;
    if (XMVectorGetZ(gt) != 0) v |= 4;

    int mask = u + v;
  }
}
