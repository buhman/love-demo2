#pragma once

namespace view {
  struct view_state {
    XMVECTOR up;
    XMVECTOR eye;
    XMVECTOR forward;
    XMVECTOR direction;
    float fov;
    float pitch;

    XMMATRIX projection_transform;
    XMMATRIX view_transform;
    XMMATRIX transform;
    XMFLOAT4X4 float_transform;
  };

  extern view_state state;

  void update_transforms();
}
