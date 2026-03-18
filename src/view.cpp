#include "directxmath/directxmath.h"

#include "window.h"
#include "view.h"

constexpr bool third_person = false;

namespace view {
  view_state state = {};

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
    XMMATRIX view = XMMatrixLookAtRH(state.eye, state.at, state.up);
    return view;
  }

  static inline float clamp_pitch(float delta_pitch)
  {
    float pitch = state.pitch + delta_pitch;
    if (pitch > 1.57f) pitch = 1.57f;
    if (pitch < -1.57f) pitch = -1.57f;
    return pitch;
  }

  static inline XMVECTOR get_normal()
  {
    return XMVector3NormalizeEst(XMVector3Cross(state.forward, state.up));
  }

  static inline XMVECTOR get_direction()
  {
    XMMATRIX mrn = XMMatrixRotationAxis(state.normal, state.pitch);
    return XMVector3Transform(state.forward, mrn);
  }

  namespace first_person {
    void apply_transform(float forward, float strafe, float elevation,
                         float delta_yaw, float delta_pitch)
    {
      state.pitch = clamp_pitch(delta_pitch);

      state.forward = XMVector3Transform(state.forward, XMMatrixRotationZ(delta_yaw));
      state.normal = get_normal(); // on forward change
      state.direction = get_direction(); // on forward/normal/pitch change

      state.eye += state.forward * forward + state.normal * strafe + state.up * elevation;
      state.at = state.eye + state.direction * at_distance;
    }
  }

  namespace third_person {
    XMVECTOR apply_transform(float forward, float strafe, float elevation,
                             float delta_yaw, float delta_pitch)
    {
      state.pitch = clamp_pitch(delta_pitch);

      state.forward = XMVector3Transform(state.forward, XMMatrixRotationZ(delta_yaw));
      state.normal = get_normal(); // on forward change
      state.direction = get_direction(); // on forward/normal/pitch change

      /*
      state.at += state.forward * forward + state.normal * strafe + state.up * elevation;
      state.eye = state.at - state.direction * at_distance;
      */
      return state.forward * forward + state.normal * strafe + state.up * elevation;
    }
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

    state.fov = 1.5;
    state.pitch = -0.7;

    state.forward = XMVector3Normalize(XMVectorSet(-0.64, 0.77, 0, 0));
    state.normal = get_normal(); // on forward change
    state.direction = get_direction(); // on forward/normal/pitch change

    // position
    state.eye = XMVectorSet(-45.5f, 43.25f, 63.0f, 1);
    state.at = state.eye + state.direction * at_distance;
    //state.at = XMVectorSet(0, 0, 0, 1);
    //state.eye = XMVectorSet(0, -100, 0, 1);
  }
}
