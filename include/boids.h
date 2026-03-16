namespace boids {

  struct boid_configuration {
    float vision_length;

    struct {
      float coefficient;
    } cohesion;

    struct {
      float coefficient;
    } alignment;

    struct {
      float minimum_length;
      float coefficient;
    } separation;

    struct {
      float coefficient;
    } bounds;
  };

  struct boid_forces {
    float vision_neighbor_count;

    struct {
      // intermediate state
      XMVECTOR center_of_mass;
      XMVECTOR force;
    } cohesion;

    struct {
      // intermediate state
      XMVECTOR average_velocity;
      XMVECTOR force;
    } alignment;

    struct {
      // intermediate state
      XMVECTOR force;
    } separation;
  };

  struct boid {
    XMVECTOR position;
    XMVECTOR velocity;
  };

  extern boid_configuration configuration;

  boid_forces const & evaluate(boid const * const boids, int length, int boid_index);
}
