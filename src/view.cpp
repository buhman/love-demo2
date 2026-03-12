#include "directxmath/directxmath.h"

#include "window.h"

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

  view_state state;

  static inline XMMATRIX current_projection()
  {
    float fov_angle_y = XMConvertToRadians(45 * state.fov);
    float aspect_ratio = window::width / window::height;
    float near_z = 1.0;
    float far_z = 0.1;
    XMMATRIX projection = XMMatrixPerspectiveFovRH(fov_angle_y, aspect_ratio, near_z, far_z);
    return projection;
  }

  static inline XMMATRIX current_view()
  {
    XMVECTOR at = XMVectorAdd(state.eye, state.direction);
    XMMATRIX view = XMMatrixLookAtRH(state.eye, at, state.up);
    return view;
  }

  void update_transforms()
  {
    state.projection_transform = current_projection();
    state.view_transform = current_view();
    state.transform = state.view_transform * state.projection_transform;
    XMStoreFloat4x4(&state.float_transform, state.transform);
  }
}
