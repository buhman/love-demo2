#pragma once

namespace view {
  struct view_state {
    // positions
    XMVECTOR eye;
    XMVECTOR at;

    // vectors
    XMVECTOR up;
    XMVECTOR forward;
    XMVECTOR normal; // cross(forward, up)
    XMVECTOR direction; // rotationaxis(forward, pitch)

    // angles
    float fov;
    float pitch;

    // transforms
    XMMATRIX projection_transform;
    XMMATRIX view_transform;
    XMMATRIX transform;

    // transform views
    XMFLOAT4X4 float_transform;
  };

  extern view_state state;

  namespace first_person {
    void apply_transform(float forward, float strafe, float elevation,
                         float delta_yaw, float delta_pitch);
  }

  namespace third_person {
    void apply_transform(float forward, float strafe, float elevation,
                         float delta_yaw, float delta_pitch);
  }

  void apply_fov(float delta);
  void update_transforms();
  void load();
}
