#include "directxmath/directxmath.h"

#include "window.h"
#include "view.h"

constexpr bool third_person = false;

namespace view {
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
    state.at = XMVectorAdd(state.eye, state.direction);

    XMMATRIX view = XMMatrixLookAtRH(state.eye, state.at, state.up);
    return view;
  }

  void apply_translation(float forward, float strafe, float elevation)
  {
    state.eye += state.forward * forward + state.normal * strafe + state.up * elevation;
  }

  void apply_yaw_pitch(float delta_yaw, float delta_pitch)
  {
    XMMATRIX mrz = XMMatrixRotationZ(delta_yaw);
    state.forward = XMVector3Transform(state.forward, mrz);
    state.normal = XMVector3NormalizeEst(XMVector3Cross(state.forward, state.up));

    state.pitch += delta_pitch;
    if (state.pitch > 1.57f) state.pitch = 1.57f;
    if (state.pitch < -1.57f) state.pitch = -1.57f;

    XMMATRIX mrn = XMMatrixRotationAxis(state.normal, state.pitch);
    state.direction = XMVector3Transform(state.forward, mrn);
  }

  void apply_fov(float delta)
  {
    float new_fov = state.fov + delta;
    if (new_fov > 0.00001f) {
      state.fov = new_fov;
    }
  }

  void update_transforms()
  {
    state.projection_transform = current_projection();
    state.view_transform = current_view();
    state.transform = state.view_transform * state.projection_transform;
    XMStoreFloat4x4(&state.float_transform, state.transform);
  }

  void load()
  {
    state.up = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    state.eye = XMVectorSet(-55.5f, 48.25f, 50.0f, 1);
    state.forward = XMVector3Normalize(XMVectorSet(-0.63, 0.78, 0, 0));
    state.direction = state.forward;
    state.normal = XMVector3Normalize(XMVector3Cross(state.forward, state.up));

    state.fov = 1.5;

    state.pitch = 0;
  }
}
