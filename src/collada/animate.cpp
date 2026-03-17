#include <stdio.h>

#include "directxmath/directxmath.h"

#include "collada/types.h"
#include "collada/instance_types.h"

namespace collada::animate {

  static inline int find_frame_ix(types::source const& source, float t)
  {
    for (int i = 0; i < source.count - 1; i++) {
      if (source.float_array[i] <= t && source.float_array[i+1] > t) {
        return i;
      }
    }
    return -1;
  }

  static inline float linear_interpolate_iv(types::source const& source, int frame_ix, float t)
  {
    float prev = source.float_array[(frame_ix+0) * source.stride];
    float next = source.float_array[(frame_ix+1) * source.stride];
    return (t - prev) / (next - prev);
  }

  static inline float linear_interpolate_value(types::source const& source, int frame_ix, int parameter_ix, float iv)
  {
    float prev = source.float_array[(frame_ix+0) * source.stride + parameter_ix];
    float next = source.float_array[(frame_ix+1) * source.stride + parameter_ix];
    return prev + iv * (next - prev);
  }

  static inline float pow3(float f)
  {
    return f * f * f;
  }

  static inline float pow2(float f)
  {
    return f * f;
  }

  static inline XMVECTOR bezier(XMVECTOR p0, XMVECTOR c0, XMVECTOR c1, XMVECTOR p1, float s)
  {
    return
        p0 * pow3(1 - s)
      + 3 * c0 * s * pow2(1 - s)
      + 3 * c1 * pow2(s) * (1 - s)
      + p1 * pow3(s);
  }

  static inline float bezier_binary_search(XMVECTOR p0, XMVECTOR c0, XMVECTOR c1, XMVECTOR p1, float want)
  {
    float low = 0.0f;
    float high = 1.0f;

    int iterations = 0;
    while (iterations < 20) {
      iterations += 1;

      float s = (high + low) * 0.5f;
      XMVECTOR bs = bezier(p0, c0, c1, p1, s);
      float t = XMVectorGetX(bs);

      const float epsilon = 0.001f;
      if (fabsf(t - want) < epsilon) {
        return XMVectorGetY(bs);
      }

      if (t > want) {
        high = s;
      } else {
        low = s;
      }
    }

    fprintf(stderr, "%f %f\n", XMVectorGetX(p0), XMVectorGetY(p0));
    fprintf(stderr, "%f %f\n", XMVectorGetX(c0), XMVectorGetY(c0));
    fprintf(stderr, "%f %f\n", XMVectorGetX(c1), XMVectorGetY(c1));
    fprintf(stderr, "%f %f\n", XMVectorGetX(p1), XMVectorGetY(p1));
    assert(false);
  }

  static inline XMFLOAT2 const * tangent_index(types::source const& source, int frame_ix, int parameter_ix)
  {
    int ix = frame_ix * source.stride + parameter_ix * 2;
    return (XMFLOAT2 const *)&source.float_array[ix];
  }

  static float bezier_sampler(types::sampler const * const sampler, int frame_ix, int parameter_ix, float t)
  {
    /*
      P0 is (INPUT[i] , OUTPUT[i])
      C0 (or T0) is (OUT_TANGENT[i][0] , OUT_TANGENT[i][1])
      C1 (or T1) is (IN_TANGENT[i+1][0], IN_TANGENT[i+1][1])
      P1 is (INPUT[i+1], OUTPUT[i+1])
    */

    float frame0_input = sampler->input.float_array[frame_ix+0];
    float frame1_input = sampler->input.float_array[frame_ix+1];

    float frame0_output = sampler->output.float_array[(frame_ix+0) * sampler->output.stride + parameter_ix];
    float frame1_output = sampler->output.float_array[(frame_ix+1) * sampler->output.stride + parameter_ix];

    XMVECTOR p0 = XMVectorSet(frame0_input, frame0_output, 0, 0);
    XMVECTOR c0 = XMLoadFloat2(tangent_index(sampler->out_tangent, frame_ix + 0, parameter_ix));
    XMVECTOR c1 = XMLoadFloat2(tangent_index(sampler->in_tangent, frame_ix + 1, parameter_ix));
    XMVECTOR p1 = XMVectorSet(frame1_input, frame1_output, 0, 0);

    return bezier_binary_search(p0, c0, c1, p1, t);
  }

  static void apply_transform_target(instance_types::transform& transform,
                                     enum types::target_attribute channel_target_attribute,
                                     float value)
  {
    switch (transform.type) {
    case types::transform_type::TRANSLATE: __attribute__((fallthrough));
    case types::transform_type::SCALE:
      switch (channel_target_attribute) {
      case types::target_attribute::X: transform.vector = XMVectorSetX(transform.vector, value); return;
      case types::target_attribute::Y: transform.vector = XMVectorSetY(transform.vector, value); return;
      case types::target_attribute::Z: transform.vector = XMVectorSetZ(transform.vector, value); return;
      default: assert(false);
      }
    case types::transform_type::ROTATE:
      switch (channel_target_attribute) {
      case types::target_attribute::X: transform.vector = XMVectorSetX(transform.vector, value); return;
      case types::target_attribute::Y: transform.vector = XMVectorSetY(transform.vector, value); return;
      case types::target_attribute::Z: transform.vector = XMVectorSetZ(transform.vector, value); return;
      case types::target_attribute::ANGLE: transform.vector = XMVectorSetW(transform.vector, value); return;
      default: assert(false);
      }
    default:
      assert(false);
      break;
    }
  }

  static enum types::target_attribute const rotate_target_attributes[] = {
    types::target_attribute::X,
    types::target_attribute::Y,
    types::target_attribute::Z,
    types::target_attribute::ANGLE,
  };

  static enum types::target_attribute const translate_scale_target_attributes[] = {
    types::target_attribute::X,
    types::target_attribute::Y,
    types::target_attribute::Z,
  };

  static void animate_channel_segment(types::channel const& channel,
                                      instance_types::transform& transform,
                                      int frame_ix, float t)
  {
    enum types::target_attribute const * target_attributes = &channel.target_attribute;
    int target_attributes_count = 1;
    if (channel.target_attribute == types::target_attribute::ALL) {
      switch (transform.type) {
      case types::transform_type::TRANSLATE: __attribute__((fallthrough));
      case types::transform_type::SCALE:
        target_attributes = translate_scale_target_attributes;
        target_attributes_count = 3;
        break;
      case types::transform_type::ROTATE:
        target_attributes = rotate_target_attributes;
        target_attributes_count = 4;
        break;
      default:
        assert(false);
        break;
      }
    }

    for (int parameter_ix = 0; parameter_ix < target_attributes_count; parameter_ix++) {

      enum types::interpolation interpolation = channel.source_sampler->interpolation.interpolation_array[frame_ix];

      float value;
      if (interpolation == types::interpolation::BEZIER) {
        value = bezier_sampler(channel.source_sampler, frame_ix, parameter_ix, t);
      } else {
        float iv = linear_interpolate_iv(channel.source_sampler->input, frame_ix, t);
        value = linear_interpolate_value(channel.source_sampler->output, frame_ix, parameter_ix, iv);
      }

      apply_transform_target(transform, target_attributes[parameter_ix], value);
    }
  }

  void animate_node(instance_types::node& node_instance, float t)
  {
    for (int i = 0; i < node_instance.node->channels_count; i++) {
      types::channel const& channel = *node_instance.node->channels[i];
      instance_types::transform& transform = node_instance.transforms[channel.target_transform_index];

      int frame_ix = find_frame_ix(channel.source_sampler->input, t);
      assert(frame_ix >= 0); // animation is missing a key frame

      animate_channel_segment(channel, transform, frame_ix, t);
    }
  }
}
