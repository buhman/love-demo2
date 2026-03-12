#pragma once

namespace view {
  struct view_state {
    XMVECTOR up;
    XMVECTOR eye;
    XMVECTOR forward;
    XMVECTOR direction;
    XMVECTOR at;
    XMVECTOR normal;
    float fov;
    float pitch;

    XMMATRIX projection_transform;
    XMMATRIX view_transform;
    XMMATRIX transform;
    XMFLOAT4X4 float_transform;
  };


  extern view_state state;

  void apply_translation(float forward, float strafe, float elevation);
  void apply_yaw_pitch(float delta_yaw, float delta_pitch);
  void apply_fov(float delta);
  void update_transforms();
  void load();
}
