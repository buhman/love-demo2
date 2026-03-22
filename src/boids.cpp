#include <stdio.h>

#include "directxmath/directxmath.h"

#include "boids.h"

namespace boids {

  boid_forces forces;
  boid_configuration configuration;

  static inline void reset_cohesion()
  {
    forces.cohesion.center_of_mass = XMVectorZero();
    forces.cohesion.force = XMVectorZero();
  }

  static inline void reset_alignment()
  {
    forces.alignment.average_velocity = XMVectorZero();
    forces.alignment.force = XMVectorZero();
  }

  static inline void reset_separation()
  {
    forces.separation.force = XMVectorZero();
  }

  static inline bool vector_equal(XMVECTOR V1, XMVECTOR V2)
  {
    uint32_t CR;
    XMVectorEqualR(&CR, V1, V2);
    return XMComparisonAllTrue(CR);
  }

  static inline XMVECTOR cohesion_force(boid const & this_boid, float const reciprocal_neighbor_count)
  {
    XMVECTOR center_of_mass = forces.cohesion.center_of_mass * reciprocal_neighbor_count;
    XMVECTOR cohesion_vector = center_of_mass - this_boid.position;
    if (vector_equal(cohesion_vector, XMVectorZero()))
      return XMVectorZero();
    XMVECTOR cohesion_direction = XMVector3NormalizeEst(cohesion_vector);
    return cohesion_direction * configuration.cohesion.coefficient;
  }

  static inline XMVECTOR alignment_force(boid const & this_boid, float const reciprocal_neighbor_count)
  {
    XMVECTOR average_velocity = forces.alignment.average_velocity * reciprocal_neighbor_count;
    XMVECTOR alignment_vector = average_velocity - this_boid.velocity;
    if (vector_equal(alignment_vector, XMVectorZero()))
      return XMVectorZero();
    XMVECTOR alignment_direction = XMVector3NormalizeEst(alignment_vector);
    return alignment_direction * configuration.alignment.coefficient;
  }

  boid_forces const & evaluate(boid const * const boids, int length, int boid_index)
  {
    forces.vision_neighbor_count = 0;

    reset_cohesion();
    reset_alignment();
    reset_separation();

    boid const & this_boid = boids[boid_index];
    for (int i = 0; i < length; i++) {
      if (i == boid_index)
        continue;

      boid const & other_boid = boids[i];

      XMVECTOR position_vector = this_boid.position - other_boid.position;
      float position_length = XMVectorGetX(XMVector3LengthEst(position_vector));
      if (position_length < configuration.vision_length) {
        forces.vision_neighbor_count += 1;

        // cohesion
        forces.cohesion.center_of_mass += other_boid.position;

        // alignment
        forces.alignment.average_velocity += other_boid.velocity;
      }

      // separation
      if (vector_equal(position_vector, XMVectorZero()))
        continue;
      if (position_length < configuration.separation.minimum_length) {
        float reciprocal_position_length = 1.0f / position_length;
        //float reciprocal_position_length = 1.0f;
        XMVECTOR separation_direction = position_vector * reciprocal_position_length;
        forces.separation.force += separation_direction * reciprocal_position_length * configuration.separation.coefficient;
      }
    }

    if (forces.vision_neighbor_count != 0) {
      float reciprocal_vision_neighbor_count = 1.0f / forces.vision_neighbor_count;
      forces.cohesion.force = cohesion_force(this_boid, reciprocal_vision_neighbor_count);
      forces.alignment.force = alignment_force(this_boid, reciprocal_vision_neighbor_count);
    }

    return forces;
  }
}
