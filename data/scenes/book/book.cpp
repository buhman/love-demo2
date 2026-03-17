#include "collada/types.h"

#include "data/scenes/book.h"

namespace book {

using namespace collada::types;

camera const camera_camera_camera = {
  .xfov = 39.59775f,
  .yfov = 0.0f,
  .znear = 3.937008f,
  .zfar = 3937.008f,
  .aspect_ratio = 0.0f,
};

light const light_environmentambientlight = {
  .type = light_type::AMBIENT,
  .color = {0.0f, 0.0f, 0.0f},
};

float const array_camera_camera_xfov_input_array[] = {
  0.0,
  0.03333333,
  0.06666667,
  0.1,
  0.1333333,
  0.1666667,
  0.2,
  0.2333333,
  0.2666667,
  0.3,
  0.3333333,
  0.3666667,
  0.4,
  0.4333333,
  0.4666667,
  0.5,
  0.5333333,
  0.5666667,
  0.6,
  0.6333333,
  0.6666667,
  0.7,
  0.7333334,
  0.7666667,
  0.8,
  0.8333334,
  0.8666667,
  0.9,
  0.9333334,
  0.9666667,
  1.0,
  1.033333,
  1.066667,
  1.1,
  1.133333,
  1.166667,
  1.2,
  1.233333,
  1.266667,
  1.3,
  1.333333,
  1.366667,
  1.4,
  1.433333,
  1.466667,
  1.5,
  1.533333,
  1.566667,
  1.6,
  1.633333,
  1.666667,
  1.7,
  1.733333,
  1.766667,
};

float const array_camera_camera_xfov_output_array[] = {
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
  39.59775,
};

float const array_camera_camera_xfov_intangent_array[] = {
  -0.3332639, 39.59775,
  0.02222222, 39.59775,
  0.05555556, 39.59775,
  0.08888889, 39.59775,
  0.1222222, 39.59775,
  0.1555556, 39.59775,
  0.1888889, 39.59775,
  0.2222222, 39.59775,
  0.2555556, 39.59775,
  0.2888889, 39.59775,
  0.3222222, 39.59775,
  0.3555556, 39.59775,
  0.3888889, 39.59775,
  0.4222222, 39.59775,
  0.4555556, 39.59775,
  0.4888889, 39.59775,
  0.5222222, 39.59775,
  0.5555556, 39.59775,
  0.5888889, 39.59775,
  0.6222222, 39.59775,
  0.6555555, 39.59775,
  0.6888889, 39.59775,
  0.7222223, 39.59775,
  0.7555556, 39.59775,
  0.7888889, 39.59775,
  0.8222222, 39.59775,
  0.8555556, 39.59775,
  0.8888889, 39.59775,
  0.9222223, 39.59775,
  0.9555556, 39.59775,
  0.9888889, 39.59775,
  1.022222, 39.59775,
  1.055556, 39.59775,
  1.088889, 39.59775,
  1.122222, 39.59775,
  1.155556, 39.59775,
  1.188889, 39.59775,
  1.222222, 39.59775,
  1.255556, 39.59775,
  1.288889, 39.59775,
  1.322222, 39.59775,
  1.355556, 39.59775,
  1.388889, 39.59775,
  1.422222, 39.59775,
  1.455556, 39.59775,
  1.488889, 39.59775,
  1.522222, 39.59775,
  1.555556, 39.59775,
  1.588889, 39.59775,
  1.622222, 39.59775,
  1.655556, 39.59775,
  1.688889, 39.59775,
  1.722222, 39.59775,
  1.755556, 39.59775,
};

float const array_camera_camera_xfov_outtangent_array[] = {
  0.01111111, 39.59775,
  0.04444445, 39.59775,
  0.07777778, 39.59775,
  0.1111111, 39.59775,
  0.1444445, 39.59775,
  0.1777778, 39.59775,
  0.2111111, 39.59775,
  0.2444444, 39.59775,
  0.2777778, 39.59775,
  0.3111111, 39.59775,
  0.3444445, 39.59775,
  0.3777778, 39.59775,
  0.4111111, 39.59775,
  0.4444444, 39.59775,
  0.4777778, 39.59775,
  0.5111111, 39.59775,
  0.5444444, 39.59775,
  0.5777778, 39.59775,
  0.6111111, 39.59775,
  0.6444445, 39.59775,
  0.6777778, 39.59775,
  0.7111111, 39.59775,
  0.7444445, 39.59775,
  0.7777778, 39.59775,
  0.8111112, 39.59775,
  0.8444445, 39.59775,
  0.8777778, 39.59775,
  0.9111111, 39.59775,
  0.9444445, 39.59775,
  0.9777778, 39.59775,
  1.011111, 39.59775,
  1.044444, 39.59775,
  1.077778, 39.59775,
  1.111111, 39.59775,
  1.144444, 39.59775,
  1.177778, 39.59775,
  1.211111, 39.59775,
  1.244444, 39.59775,
  1.277778, 39.59775,
  1.311111, 39.59775,
  1.344445, 39.59775,
  1.377778, 39.59775,
  1.411111, 39.59775,
  1.444445, 39.59775,
  1.477778, 39.59775,
  1.511111, 39.59775,
  1.544444, 39.59775,
  1.577778, 39.59775,
  1.611111, 39.59775,
  1.644444, 39.59775,
  1.677778, 39.59775,
  1.711111, 39.59775,
  1.744444, 39.59775,
  2.099931, 39.59775,
};

enum interpolation const array_camera_camera_xfov_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_camera_camera_xfov_sampler = {
  // camera_camera_xfov_input
  .input = {
    .float_array = array_camera_camera_xfov_input_array,
    .count = 54,
    .stride = 1,
  },
  // camera_camera_xfov_output
  .output = {
    .float_array = array_camera_camera_xfov_output_array,
    .count = 54,
    .stride = 1,
  },
  // camera_camera_xfov_intangent
  .in_tangent = {
    .float_array = array_camera_camera_xfov_intangent_array,
    .count = 54,
    .stride = 2,
  },
  // camera_camera_xfov_outtangent
  .out_tangent = {
    .float_array = array_camera_camera_xfov_outtangent_array,
    .count = 54,
    .stride = 2,
  },
  // camera_camera_xfov_interpolation
  .interpolation = {
    .interpolation_array = array_camera_camera_xfov_interpolation_array,
    .count = 54,
    .stride = 1,
  },
};

float const array_node_root_bone_translation_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_translation_x_output_array[] = {
  -0.04051036,
  -0.04051036,
};

float const array_node_root_bone_translation_x_intangent_array[] = {
  -0.3332639, -0.04051036,
  1.194444, -0.04051036,
};

float const array_node_root_bone_translation_x_outtangent_array[] = {
  0.5972222, -0.04051036,
  2.124931, -0.04051036,
};

enum interpolation const array_node_root_bone_translation_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_translation_x_sampler = {
  // node_root_bone_translation_x_input
  .input = {
    .float_array = array_node_root_bone_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_x_output
  .output = {
    .float_array = array_node_root_bone_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_translation_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_translation_y_output_array[] = {
  -0.2942449,
  -0.2942449,
};

float const array_node_root_bone_translation_y_intangent_array[] = {
  -0.3332639, -0.2942449,
  1.194444, -0.2942449,
};

float const array_node_root_bone_translation_y_outtangent_array[] = {
  0.5972222, -0.2942449,
  2.124931, -0.2942449,
};

enum interpolation const array_node_root_bone_translation_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_translation_y_sampler = {
  // node_root_bone_translation_y_input
  .input = {
    .float_array = array_node_root_bone_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_y_output
  .output = {
    .float_array = array_node_root_bone_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_translation_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_translation_z_output_array[] = {
  -0.1360549,
  -0.1360549,
};

float const array_node_root_bone_translation_z_intangent_array[] = {
  -0.3332639, -0.1360549,
  1.194444, -0.1360549,
};

float const array_node_root_bone_translation_z_outtangent_array[] = {
  0.5972222, -0.1360549,
  2.124931, -0.1360549,
};

enum interpolation const array_node_root_bone_translation_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_translation_z_sampler = {
  // node_root_bone_translation_z_input
  .input = {
    .float_array = array_node_root_bone_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_z_output
  .output = {
    .float_array = array_node_root_bone_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_rotationz_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_rotationz_angle_output_array[] = {
  -1.21888e-12,
  -1.21888e-12,
};

float const array_node_root_bone_rotationz_angle_intangent_array[] = {
  -0.3332639, -1.21888e-12,
  1.194444, -1.21888e-12,
};

float const array_node_root_bone_rotationz_angle_outtangent_array[] = {
  0.5972222, -1.21888e-12,
  2.124931, -1.21888e-12,
};

enum interpolation const array_node_root_bone_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_rotationz_angle_sampler = {
  // node_root_bone_rotationz_angle_input
  .input = {
    .float_array = array_node_root_bone_rotationz_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationz_angle_output
  .output = {
    .float_array = array_node_root_bone_rotationz_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_rotationz_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_rotationz_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_rotationz_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_rotationy_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_rotationy_angle_output_array[] = {
  -1.36604e-05,
  -1.36604e-05,
};

float const array_node_root_bone_rotationy_angle_intangent_array[] = {
  -0.3332639, -1.36604e-05,
  1.194444, -1.36604e-05,
};

float const array_node_root_bone_rotationy_angle_outtangent_array[] = {
  0.5972222, -1.36604e-05,
  2.124931, -1.36604e-05,
};

enum interpolation const array_node_root_bone_rotationy_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_rotationy_angle_sampler = {
  // node_root_bone_rotationy_angle_input
  .input = {
    .float_array = array_node_root_bone_rotationy_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationy_angle_output
  .output = {
    .float_array = array_node_root_bone_rotationy_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_rotationy_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_rotationy_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_rotationy_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_rotationx_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_rotationx_angle_output_array[] = {
  5.11235e-06,
  5.11235e-06,
};

float const array_node_root_bone_rotationx_angle_intangent_array[] = {
  -0.3332639, 5.11235e-06,
  1.194444, 5.11235e-06,
};

float const array_node_root_bone_rotationx_angle_outtangent_array[] = {
  0.5972222, 5.11235e-06,
  2.124931, 5.11235e-06,
};

enum interpolation const array_node_root_bone_rotationx_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_rotationx_angle_sampler = {
  // node_root_bone_rotationx_angle_input
  .input = {
    .float_array = array_node_root_bone_rotationx_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationx_angle_output
  .output = {
    .float_array = array_node_root_bone_rotationx_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_rotationx_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_rotationx_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_rotationx_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_scale_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_scale_x_output_array[] = {
  1.0,
  1.0,
};

float const array_node_root_bone_scale_x_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_root_bone_scale_x_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_root_bone_scale_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_scale_x_sampler = {
  // node_root_bone_scale_x_input
  .input = {
    .float_array = array_node_root_bone_scale_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_x_output
  .output = {
    .float_array = array_node_root_bone_scale_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_x_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_scale_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_x_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_scale_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_scale_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_scale_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_scale_y_output_array[] = {
  1.0,
  1.0,
};

float const array_node_root_bone_scale_y_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_root_bone_scale_y_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_root_bone_scale_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_scale_y_sampler = {
  // node_root_bone_scale_y_input
  .input = {
    .float_array = array_node_root_bone_scale_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_y_output
  .output = {
    .float_array = array_node_root_bone_scale_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_y_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_scale_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_y_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_scale_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_scale_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_root_bone_scale_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_root_bone_scale_z_output_array[] = {
  1.0,
  1.0,
};

float const array_node_root_bone_scale_z_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_root_bone_scale_z_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_root_bone_scale_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_root_bone_scale_z_sampler = {
  // node_root_bone_scale_z_input
  .input = {
    .float_array = array_node_root_bone_scale_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_z_output
  .output = {
    .float_array = array_node_root_bone_scale_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_root_bone_scale_z_intangent
  .in_tangent = {
    .float_array = array_node_root_bone_scale_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_z_outtangent
  .out_tangent = {
    .float_array = array_node_root_bone_scale_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_root_bone_scale_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_root_bone_scale_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_translation_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_translation_x_output_array[] = {
  -0.04051036,
  -0.04051036,
};

float const array_node_bottom_cover_translation_x_intangent_array[] = {
  -0.3332639, -0.04051036,
  1.194444, -0.04051036,
};

float const array_node_bottom_cover_translation_x_outtangent_array[] = {
  0.5972222, -0.04051036,
  2.124931, -0.04051036,
};

enum interpolation const array_node_bottom_cover_translation_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_translation_x_sampler = {
  // node_bottom_cover_translation_x_input
  .input = {
    .float_array = array_node_bottom_cover_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_x_output
  .output = {
    .float_array = array_node_bottom_cover_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_translation_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_translation_y_output_array[] = {
  -0.2942449,
  -0.2942449,
};

float const array_node_bottom_cover_translation_y_intangent_array[] = {
  -0.3332639, -0.2942449,
  1.194444, -0.2942449,
};

float const array_node_bottom_cover_translation_y_outtangent_array[] = {
  0.5972222, -0.2942449,
  2.124931, -0.2942449,
};

enum interpolation const array_node_bottom_cover_translation_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_translation_y_sampler = {
  // node_bottom_cover_translation_y_input
  .input = {
    .float_array = array_node_bottom_cover_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_y_output
  .output = {
    .float_array = array_node_bottom_cover_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_translation_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_translation_z_output_array[] = {
  -0.1360549,
  -0.1360549,
};

float const array_node_bottom_cover_translation_z_intangent_array[] = {
  -0.3332639, -0.1360549,
  1.194444, -0.1360549,
};

float const array_node_bottom_cover_translation_z_outtangent_array[] = {
  0.5972222, -0.1360549,
  2.124931, -0.1360549,
};

enum interpolation const array_node_bottom_cover_translation_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_translation_z_sampler = {
  // node_bottom_cover_translation_z_input
  .input = {
    .float_array = array_node_bottom_cover_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_z_output
  .output = {
    .float_array = array_node_bottom_cover_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_rotationz_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_rotationz_angle_output_array[] = {
  -1.08297e-12,
  -1.08297e-12,
};

float const array_node_bottom_cover_rotationz_angle_intangent_array[] = {
  -0.3332639, -1.08297e-12,
  1.194444, -1.08297e-12,
};

float const array_node_bottom_cover_rotationz_angle_outtangent_array[] = {
  0.5972222, -1.08297e-12,
  2.124931, -1.08297e-12,
};

enum interpolation const array_node_bottom_cover_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_rotationz_angle_sampler = {
  // node_bottom_cover_rotationz_angle_input
  .input = {
    .float_array = array_node_bottom_cover_rotationz_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_rotationz_angle_output
  .output = {
    .float_array = array_node_bottom_cover_rotationz_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_rotationz_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_rotationz_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_rotationz_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_rotationy_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_rotationy_angle_output_array[] = {
  -1.36604e-05,
  -1.36604e-05,
};

float const array_node_bottom_cover_rotationy_angle_intangent_array[] = {
  -0.3332639, -1.36604e-05,
  1.194444, -1.36604e-05,
};

float const array_node_bottom_cover_rotationy_angle_outtangent_array[] = {
  0.5972222, -1.36604e-05,
  2.124931, -1.36604e-05,
};

enum interpolation const array_node_bottom_cover_rotationy_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_rotationy_angle_sampler = {
  // node_bottom_cover_rotationy_angle_input
  .input = {
    .float_array = array_node_bottom_cover_rotationy_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_rotationy_angle_output
  .output = {
    .float_array = array_node_bottom_cover_rotationy_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_rotationy_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_rotationy_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_rotationy_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_rotationx_angle_input_array[] = {
  0.0,
  0.04166667,
  0.08333334,
  0.125,
  0.1666667,
  0.2083333,
  0.25,
  0.2916667,
  0.3333333,
  0.375,
  0.4166667,
  0.4583333,
  0.5,
  0.5416667,
  0.5833333,
  0.625,
  0.6666667,
  0.7083334,
  0.75,
  0.7916667,
  0.8333334,
  0.875,
  0.9166667,
  0.9583334,
  1.0,
  1.041667,
  1.083333,
  1.125,
  1.166667,
  1.208333,
  1.25,
  1.291667,
  1.333333,
  1.375,
  1.416667,
  1.458333,
  1.5,
  1.541667,
  1.583333,
  1.625,
  1.666667,
  1.708333,
  1.75,
  1.791667,
};

float const array_node_bottom_cover_rotationx_angle_output_array[] = {
  -4.999998,
  -8.600579,
  -17.8863,
  -30.58308,
  -44.4169,
  -57.11371,
  -66.39939,
  -70.00001,
  -67.20704,
  -59.84375,
  -49.4336,
  -37.49999,
  -25.5664,
  -15.15625,
  -7.792974,
  -4.999998,
  -8.600579,
  -17.8863,
  -30.58309,
  -44.41691,
  -57.11371,
  -66.39941,
  -70.00001,
  -67.20704,
  -59.84375,
  -49.4336,
  -37.49999,
  -25.5664,
  -15.15625,
  -7.792974,
  -4.999998,
  -8.600582,
  -17.8863,
  -30.58309,
  -44.4169,
  -57.11371,
  -66.39939,
  -70.00001,
  -65.18519,
  -53.14815,
  -37.49999,
  -21.85185,
  -9.814806,
  -4.999998,
};

float const array_node_bottom_cover_rotationx_angle_intangent_array[] = {
  -0.3332639, -4.999998,
  0.02777778, -7.400385,
  0.06944445, -14.79106,
  0.1111111, -26.35082,
  0.1527778, -39.80563,
  0.1944444, -52.88144,
  0.2361111, -63.30416,
  0.2777778, -68.7998,
  0.3194444, -68.13802,
  0.3611111, -62.29818,
  0.4027778, -52.90365,
  0.4444444, -41.47786,
  0.4861111, -29.54427,
  0.5277778, -18.6263,
  0.5694445, -10.2474,
  0.6111111, -5.93099,
  0.6527778, -7.400385,
  0.6944445, -14.79106,
  0.7361111, -26.35082,
  0.7777778, -39.80564,
  0.8194445, -52.88144,
  0.8611111, -63.30417,
  0.9027778, -68.79981,
  0.9444445, -68.13802,
  0.9861112, -62.29818,
  1.027778, -52.90365,
  1.069444, -41.47786,
  1.111111, -29.54427,
  1.152778, -18.6263,
  1.194444, -10.2474,
  1.236111, -5.93099,
  1.277778, -7.400387,
  1.319444, -14.79106,
  1.361111, -26.35082,
  1.402778, -39.80563,
  1.444445, -52.88144,
  1.486111, -63.30416,
  1.527778, -68.7998,
  1.569445, -66.79013,
  1.611111, -57.1605,
  1.652778, -42.71605,
  1.694445, -27.0679,
  1.736111, -13.82715,
  1.777778, -6.604934,
};

float const array_node_bottom_cover_rotationx_angle_outtangent_array[] = {
  0.01388889, -6.200191,
  0.05555556, -11.69582,
  0.09722222, -22.11856,
  0.1388889, -35.19436,
  0.1805556, -48.64917,
  0.2222222, -60.20893,
  0.2638889, -67.5996,
  0.3055556, -69.06902,
  0.3472222, -64.75261,
  0.3888889, -56.3737,
  0.4305556, -45.45573,
  0.4722222, -33.52213,
  0.5138889, -22.09635,
  0.5555556, -12.70182,
  0.5972222, -6.861981,
  0.6388889, -6.200191,
  0.6805556, -11.69582,
  0.7222223, -22.11856,
  0.7638889, -35.19436,
  0.8055556, -48.64918,
  0.8472223, -60.20894,
  0.8888889, -67.59961,
  0.9305556, -69.06902,
  0.9722223, -64.75261,
  1.013889, -56.3737,
  1.055556, -45.45573,
  1.097222, -33.52213,
  1.138889, -22.09635,
  1.180556, -12.70182,
  1.222222, -6.861981,
  1.263889, -6.200192,
  1.305556, -11.69582,
  1.347222, -22.11856,
  1.388889, -35.19436,
  1.430556, -48.64917,
  1.472222, -60.20893,
  1.513889, -67.5996,
  1.555556, -68.39507,
  1.597222, -61.17284,
  1.638889, -47.93209,
  1.680556, -32.28395,
  1.722222, -17.8395,
  1.763889, -8.209869,
  2.124931, -4.999998,
};

enum interpolation const array_node_bottom_cover_rotationx_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_rotationx_angle_sampler = {
  // node_bottom_cover_rotationx_angle_input
  .input = {
    .float_array = array_node_bottom_cover_rotationx_angle_input_array,
    .count = 44,
    .stride = 1,
  },
  // node_bottom_cover_rotationx_angle_output
  .output = {
    .float_array = array_node_bottom_cover_rotationx_angle_output_array,
    .count = 44,
    .stride = 1,
  },
  // node_bottom_cover_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_rotationx_angle_intangent_array,
    .count = 44,
    .stride = 2,
  },
  // node_bottom_cover_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_rotationx_angle_outtangent_array,
    .count = 44,
    .stride = 2,
  },
  // node_bottom_cover_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_rotationx_angle_interpolation_array,
    .count = 44,
    .stride = 1,
  },
};

float const array_node_bottom_cover_scale_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_scale_x_output_array[] = {
  1.0,
  1.0,
};

float const array_node_bottom_cover_scale_x_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_bottom_cover_scale_x_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_bottom_cover_scale_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_scale_x_sampler = {
  // node_bottom_cover_scale_x_input
  .input = {
    .float_array = array_node_bottom_cover_scale_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_x_output
  .output = {
    .float_array = array_node_bottom_cover_scale_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_x_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_scale_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_x_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_scale_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_scale_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_scale_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_scale_y_output_array[] = {
  1.0,
  1.0,
};

float const array_node_bottom_cover_scale_y_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_bottom_cover_scale_y_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_bottom_cover_scale_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_scale_y_sampler = {
  // node_bottom_cover_scale_y_input
  .input = {
    .float_array = array_node_bottom_cover_scale_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_y_output
  .output = {
    .float_array = array_node_bottom_cover_scale_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_y_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_scale_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_y_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_scale_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_scale_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bottom_cover_scale_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_bottom_cover_scale_z_output_array[] = {
  1.0,
  1.0,
};

float const array_node_bottom_cover_scale_z_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_bottom_cover_scale_z_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_bottom_cover_scale_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bottom_cover_scale_z_sampler = {
  // node_bottom_cover_scale_z_input
  .input = {
    .float_array = array_node_bottom_cover_scale_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_z_output
  .output = {
    .float_array = array_node_bottom_cover_scale_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bottom_cover_scale_z_intangent
  .in_tangent = {
    .float_array = array_node_bottom_cover_scale_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_z_outtangent
  .out_tangent = {
    .float_array = array_node_bottom_cover_scale_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bottom_cover_scale_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_bottom_cover_scale_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_translation_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_translation_x_output_array[] = {
  0.1620414,
  0.1620414,
};

float const array_node_control_bone_translation_x_intangent_array[] = {
  -0.3332639, 0.1620414,
  1.194444, 0.1620414,
};

float const array_node_control_bone_translation_x_outtangent_array[] = {
  0.5972222, 0.1620414,
  2.124931, 0.1620414,
};

enum interpolation const array_node_control_bone_translation_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_translation_x_sampler = {
  // node_control_bone_translation_x_input
  .input = {
    .float_array = array_node_control_bone_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_x_output
  .output = {
    .float_array = array_node_control_bone_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_translation_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_translation_y_output_array[] = {
  -0.2942449,
  -0.2942449,
};

float const array_node_control_bone_translation_y_intangent_array[] = {
  -0.3332639, -0.2942449,
  1.194444, -0.2942449,
};

float const array_node_control_bone_translation_y_outtangent_array[] = {
  0.5972222, -0.2942449,
  2.124931, -0.2942449,
};

enum interpolation const array_node_control_bone_translation_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_translation_y_sampler = {
  // node_control_bone_translation_y_input
  .input = {
    .float_array = array_node_control_bone_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_y_output
  .output = {
    .float_array = array_node_control_bone_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_translation_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_translation_z_output_array[] = {
  -0.1360549,
  -0.1360549,
};

float const array_node_control_bone_translation_z_intangent_array[] = {
  -0.3332639, -0.1360549,
  1.194444, -0.1360549,
};

float const array_node_control_bone_translation_z_outtangent_array[] = {
  0.5972222, -0.1360549,
  2.124931, -0.1360549,
};

enum interpolation const array_node_control_bone_translation_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_translation_z_sampler = {
  // node_control_bone_translation_z_input
  .input = {
    .float_array = array_node_control_bone_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_z_output
  .output = {
    .float_array = array_node_control_bone_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_rotationz_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_rotationz_angle_output_array[] = {
  -1.21915e-12,
  -1.21915e-12,
};

float const array_node_control_bone_rotationz_angle_intangent_array[] = {
  -0.3332639, -1.21915e-12,
  1.194444, -1.21915e-12,
};

float const array_node_control_bone_rotationz_angle_outtangent_array[] = {
  0.5972222, -1.21915e-12,
  2.124931, -1.21915e-12,
};

enum interpolation const array_node_control_bone_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_rotationz_angle_sampler = {
  // node_control_bone_rotationz_angle_input
  .input = {
    .float_array = array_node_control_bone_rotationz_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationz_angle_output
  .output = {
    .float_array = array_node_control_bone_rotationz_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_rotationz_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_rotationz_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_rotationz_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_rotationy_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_rotationy_angle_output_array[] = {
  -1.36604e-05,
  -1.36604e-05,
};

float const array_node_control_bone_rotationy_angle_intangent_array[] = {
  -0.3332639, -1.36604e-05,
  1.194444, -1.36604e-05,
};

float const array_node_control_bone_rotationy_angle_outtangent_array[] = {
  0.5972222, -1.36604e-05,
  2.124931, -1.36604e-05,
};

enum interpolation const array_node_control_bone_rotationy_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_rotationy_angle_sampler = {
  // node_control_bone_rotationy_angle_input
  .input = {
    .float_array = array_node_control_bone_rotationy_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationy_angle_output
  .output = {
    .float_array = array_node_control_bone_rotationy_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_rotationy_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_rotationy_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_rotationy_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_rotationx_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_rotationx_angle_output_array[] = {
  5.1135e-06,
  5.1135e-06,
};

float const array_node_control_bone_rotationx_angle_intangent_array[] = {
  -0.3332639, 5.1135e-06,
  1.194444, 5.1135e-06,
};

float const array_node_control_bone_rotationx_angle_outtangent_array[] = {
  0.5972222, 5.1135e-06,
  2.124931, 5.1135e-06,
};

enum interpolation const array_node_control_bone_rotationx_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_rotationx_angle_sampler = {
  // node_control_bone_rotationx_angle_input
  .input = {
    .float_array = array_node_control_bone_rotationx_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationx_angle_output
  .output = {
    .float_array = array_node_control_bone_rotationx_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_rotationx_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_rotationx_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_rotationx_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_scale_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_scale_x_output_array[] = {
  1.0,
  1.0,
};

float const array_node_control_bone_scale_x_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_control_bone_scale_x_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_control_bone_scale_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_scale_x_sampler = {
  // node_control_bone_scale_x_input
  .input = {
    .float_array = array_node_control_bone_scale_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_x_output
  .output = {
    .float_array = array_node_control_bone_scale_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_x_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_scale_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_x_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_scale_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_scale_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_scale_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_scale_y_output_array[] = {
  1.0,
  1.0,
};

float const array_node_control_bone_scale_y_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_control_bone_scale_y_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_control_bone_scale_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_scale_y_sampler = {
  // node_control_bone_scale_y_input
  .input = {
    .float_array = array_node_control_bone_scale_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_y_output
  .output = {
    .float_array = array_node_control_bone_scale_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_y_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_scale_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_y_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_scale_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_scale_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_control_bone_scale_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_control_bone_scale_z_output_array[] = {
  1.0,
  1.0,
};

float const array_node_control_bone_scale_z_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_control_bone_scale_z_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_control_bone_scale_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_control_bone_scale_z_sampler = {
  // node_control_bone_scale_z_input
  .input = {
    .float_array = array_node_control_bone_scale_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_z_output
  .output = {
    .float_array = array_node_control_bone_scale_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_control_bone_scale_z_intangent
  .in_tangent = {
    .float_array = array_node_control_bone_scale_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_z_outtangent
  .out_tangent = {
    .float_array = array_node_control_bone_scale_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_control_bone_scale_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_control_bone_scale_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_translation_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_translation_x_output_array[] = {
  -0.04051036,
  -0.04051036,
};

float const array_node_side_cover_translation_x_intangent_array[] = {
  -0.3332639, -0.04051036,
  1.194444, -0.04051036,
};

float const array_node_side_cover_translation_x_outtangent_array[] = {
  0.5972222, -0.04051036,
  2.124931, -0.04051036,
};

enum interpolation const array_node_side_cover_translation_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_translation_x_sampler = {
  // node_side_cover_translation_x_input
  .input = {
    .float_array = array_node_side_cover_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_x_output
  .output = {
    .float_array = array_node_side_cover_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_translation_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_translation_y_output_array[] = {
  -0.2942449,
  -0.2942449,
};

float const array_node_side_cover_translation_y_intangent_array[] = {
  -0.3332639, -0.2942449,
  1.194444, -0.2942449,
};

float const array_node_side_cover_translation_y_outtangent_array[] = {
  0.5972222, -0.2942449,
  2.124931, -0.2942449,
};

enum interpolation const array_node_side_cover_translation_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_translation_y_sampler = {
  // node_side_cover_translation_y_input
  .input = {
    .float_array = array_node_side_cover_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_y_output
  .output = {
    .float_array = array_node_side_cover_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_translation_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_translation_z_output_array[] = {
  -0.1360549,
  -0.1360549,
};

float const array_node_side_cover_translation_z_intangent_array[] = {
  -0.3332639, -0.1360549,
  1.194444, -0.1360549,
};

float const array_node_side_cover_translation_z_outtangent_array[] = {
  0.5972222, -0.1360549,
  2.124931, -0.1360549,
};

enum interpolation const array_node_side_cover_translation_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_translation_z_sampler = {
  // node_side_cover_translation_z_input
  .input = {
    .float_array = array_node_side_cover_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_z_output
  .output = {
    .float_array = array_node_side_cover_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_rotationz_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_rotationz_angle_output_array[] = {
  180.0,
  180.0,
};

float const array_node_side_cover_rotationz_angle_intangent_array[] = {
  -0.3332639, 180.0,
  1.194444, 180.0,
};

float const array_node_side_cover_rotationz_angle_outtangent_array[] = {
  0.5972222, 180.0,
  2.124931, 180.0,
};

enum interpolation const array_node_side_cover_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_rotationz_angle_sampler = {
  // node_side_cover_rotationz_angle_input
  .input = {
    .float_array = array_node_side_cover_rotationz_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationz_angle_output
  .output = {
    .float_array = array_node_side_cover_rotationz_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_rotationz_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_rotationz_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_rotationz_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_rotationy_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_rotationy_angle_output_array[] = {
  0.0,
  0.0,
};

float const array_node_side_cover_rotationy_angle_intangent_array[] = {
  -0.3332639, 0.0,
  1.194444, 0.0,
};

float const array_node_side_cover_rotationy_angle_outtangent_array[] = {
  0.5972222, 0.0,
  2.124931, 0.0,
};

enum interpolation const array_node_side_cover_rotationy_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_rotationy_angle_sampler = {
  // node_side_cover_rotationy_angle_input
  .input = {
    .float_array = array_node_side_cover_rotationy_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationy_angle_output
  .output = {
    .float_array = array_node_side_cover_rotationy_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_rotationy_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_rotationy_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_rotationy_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_rotationx_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_rotationx_angle_output_array[] = {
  90.00001,
  90.00001,
};

float const array_node_side_cover_rotationx_angle_intangent_array[] = {
  -0.3332639, 90.00001,
  1.194444, 90.00001,
};

float const array_node_side_cover_rotationx_angle_outtangent_array[] = {
  0.5972222, 90.00001,
  2.124931, 90.00001,
};

enum interpolation const array_node_side_cover_rotationx_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_rotationx_angle_sampler = {
  // node_side_cover_rotationx_angle_input
  .input = {
    .float_array = array_node_side_cover_rotationx_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationx_angle_output
  .output = {
    .float_array = array_node_side_cover_rotationx_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_rotationx_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_rotationx_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_rotationx_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_scale_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_scale_x_output_array[] = {
  1.0,
  1.0,
};

float const array_node_side_cover_scale_x_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_side_cover_scale_x_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_side_cover_scale_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_scale_x_sampler = {
  // node_side_cover_scale_x_input
  .input = {
    .float_array = array_node_side_cover_scale_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_x_output
  .output = {
    .float_array = array_node_side_cover_scale_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_x_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_scale_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_x_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_scale_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_scale_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_scale_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_scale_y_output_array[] = {
  1.0,
  1.0,
};

float const array_node_side_cover_scale_y_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_side_cover_scale_y_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_side_cover_scale_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_scale_y_sampler = {
  // node_side_cover_scale_y_input
  .input = {
    .float_array = array_node_side_cover_scale_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_y_output
  .output = {
    .float_array = array_node_side_cover_scale_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_y_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_scale_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_y_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_scale_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_scale_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_side_cover_scale_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_side_cover_scale_z_output_array[] = {
  1.0,
  1.0,
};

float const array_node_side_cover_scale_z_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_side_cover_scale_z_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_side_cover_scale_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_side_cover_scale_z_sampler = {
  // node_side_cover_scale_z_input
  .input = {
    .float_array = array_node_side_cover_scale_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_z_output
  .output = {
    .float_array = array_node_side_cover_scale_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_side_cover_scale_z_intangent
  .in_tangent = {
    .float_array = array_node_side_cover_scale_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_z_outtangent
  .out_tangent = {
    .float_array = array_node_side_cover_scale_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_side_cover_scale_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_side_cover_scale_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_translation_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_translation_x_output_array[] = {
  -0.04051036,
  -0.04051036,
};

float const array_node_top_cover_translation_x_intangent_array[] = {
  -0.3332639, -0.04051036,
  1.194444, -0.04051036,
};

float const array_node_top_cover_translation_x_outtangent_array[] = {
  0.5972222, -0.04051036,
  2.124931, -0.04051036,
};

enum interpolation const array_node_top_cover_translation_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_translation_x_sampler = {
  // node_top_cover_translation_x_input
  .input = {
    .float_array = array_node_top_cover_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_x_output
  .output = {
    .float_array = array_node_top_cover_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_translation_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_translation_y_output_array[] = {
  -0.2942449,
  -0.2942449,
};

float const array_node_top_cover_translation_y_intangent_array[] = {
  -0.3332639, -0.2942449,
  1.194444, -0.2942449,
};

float const array_node_top_cover_translation_y_outtangent_array[] = {
  0.5972222, -0.2942449,
  2.124931, -0.2942449,
};

enum interpolation const array_node_top_cover_translation_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_translation_y_sampler = {
  // node_top_cover_translation_y_input
  .input = {
    .float_array = array_node_top_cover_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_y_output
  .output = {
    .float_array = array_node_top_cover_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_translation_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_translation_z_output_array[] = {
  0.3174614,
  0.3174614,
};

float const array_node_top_cover_translation_z_intangent_array[] = {
  -0.3332639, 0.3174614,
  1.194444, 0.3174614,
};

float const array_node_top_cover_translation_z_outtangent_array[] = {
  0.5972222, 0.3174614,
  2.124931, 0.3174614,
};

enum interpolation const array_node_top_cover_translation_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_translation_z_sampler = {
  // node_top_cover_translation_z_input
  .input = {
    .float_array = array_node_top_cover_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_z_output
  .output = {
    .float_array = array_node_top_cover_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_rotationz_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_rotationz_angle_output_array[] = {
  -5.9515e-15,
  -5.9515e-15,
};

float const array_node_top_cover_rotationz_angle_intangent_array[] = {
  -0.3332639, -5.9515e-15,
  1.194444, -5.9515e-15,
};

float const array_node_top_cover_rotationz_angle_outtangent_array[] = {
  0.5972222, -5.9515e-15,
  2.124931, -5.9515e-15,
};

enum interpolation const array_node_top_cover_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_rotationz_angle_sampler = {
  // node_top_cover_rotationz_angle_input
  .input = {
    .float_array = array_node_top_cover_rotationz_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_rotationz_angle_output
  .output = {
    .float_array = array_node_top_cover_rotationz_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_rotationz_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_rotationz_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_rotationz_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_rotationy_angle_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_rotationy_angle_output_array[] = {
  180.0,
  180.0,
};

float const array_node_top_cover_rotationy_angle_intangent_array[] = {
  -0.3332639, 180.0,
  1.194444, 180.0,
};

float const array_node_top_cover_rotationy_angle_outtangent_array[] = {
  0.5972222, 180.0,
  2.124931, 180.0,
};

enum interpolation const array_node_top_cover_rotationy_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_rotationy_angle_sampler = {
  // node_top_cover_rotationy_angle_input
  .input = {
    .float_array = array_node_top_cover_rotationy_angle_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_rotationy_angle_output
  .output = {
    .float_array = array_node_top_cover_rotationy_angle_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_rotationy_angle_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_rotationy_angle_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_rotationy_angle_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_rotationx_angle_input_array[] = {
  0.0,
  0.04166667,
  0.08333334,
  0.125,
  0.1666667,
  0.2083333,
  0.25,
  0.2916667,
  0.3333333,
  0.375,
  0.4166667,
  0.4583333,
  0.5,
  0.5416667,
  0.5833333,
  0.625,
  0.6666667,
  0.7083334,
  0.75,
  0.7916667,
  0.8333334,
  0.875,
  0.9166667,
  0.9583334,
  1.0,
  1.041667,
  1.083333,
  1.125,
  1.166667,
  1.208333,
  1.25,
  1.291667,
  1.333333,
  1.375,
  1.416667,
  1.458333,
  1.5,
  1.541667,
  1.583333,
  1.625,
  1.666667,
  1.708333,
  1.75,
  1.791667,
};

float const array_node_top_cover_rotationx_angle_output_array[] = {
  -4.999999,
  -8.600581,
  -17.88629,
  -30.58308,
  -44.41691,
  -57.1137,
  -66.39941,
  -70.0,
  -67.20704,
  -59.84376,
  -49.43359,
  -37.5,
  -25.5664,
  -15.15625,
  -7.792964,
  -4.999999,
  -8.60058,
  -17.88629,
  -30.58309,
  -44.41691,
  -57.1137,
  -66.39942,
  -70.0,
  -67.20703,
  -59.84375,
  -49.43359,
  -37.5,
  -25.5664,
  -15.15625,
  -7.792964,
  -4.999999,
  -8.600583,
  -17.8863,
  -30.58309,
  -44.41691,
  -57.1137,
  -66.39941,
  -70.0,
  -65.18517,
  -53.14815,
  -37.5,
  -21.85185,
  -9.814812,
  -4.999999,
};

float const array_node_top_cover_rotationx_angle_intangent_array[] = {
  -0.3332639, -4.999999,
  0.02777778, -7.400387,
  0.06944445, -14.79106,
  0.1111111, -26.35082,
  0.1527778, -39.80564,
  0.1944444, -52.88144,
  0.2361111, -63.30417,
  0.2777778, -68.7998,
  0.3194444, -68.13802,
  0.3611111, -62.29819,
  0.4027778, -52.90365,
  0.4444444, -41.47787,
  0.4861111, -29.54427,
  0.5277778, -18.6263,
  0.5694445, -10.24739,
  0.6111111, -5.930987,
  0.6527778, -7.400387,
  0.6944445, -14.79106,
  0.7361111, -26.35082,
  0.7777778, -39.80564,
  0.8194445, -52.88144,
  0.8611111, -63.30418,
  0.9027778, -68.79981,
  0.9444445, -68.13802,
  0.9861112, -62.29818,
  1.027778, -52.90365,
  1.069444, -41.47787,
  1.111111, -29.54427,
  1.152778, -18.6263,
  1.194444, -10.24739,
  1.236111, -5.930987,
  1.277778, -7.400388,
  1.319444, -14.79106,
  1.361111, -26.35082,
  1.402778, -39.80564,
  1.444445, -52.88144,
  1.486111, -63.30417,
  1.527778, -68.7998,
  1.569445, -66.79012,
  1.611111, -57.16049,
  1.652778, -42.71605,
  1.694445, -27.0679,
  1.736111, -13.82716,
  1.777778, -6.604937,
};

float const array_node_top_cover_rotationx_angle_outtangent_array[] = {
  0.01388889, -6.200193,
  0.05555556, -11.69582,
  0.09722222, -22.11856,
  0.1388889, -35.19436,
  0.1805556, -48.64917,
  0.2222222, -60.20893,
  0.2638889, -67.59961,
  0.3055556, -69.06902,
  0.3472222, -64.75261,
  0.3888889, -56.3737,
  0.4305556, -45.45573,
  0.4722222, -33.52214,
  0.5138889, -22.09635,
  0.5555556, -12.70182,
  0.5972222, -6.861975,
  0.6388889, -6.200192,
  0.6805556, -11.69582,
  0.7222223, -22.11856,
  0.7638889, -35.19436,
  0.8055556, -48.64917,
  0.8472223, -60.20894,
  0.8888889, -67.59962,
  0.9305556, -69.06902,
  0.9722223, -64.7526,
  1.013889, -56.3737,
  1.055556, -45.45573,
  1.097222, -33.52214,
  1.138889, -22.09635,
  1.180556, -12.70182,
  1.222222, -6.861975,
  1.263889, -6.200193,
  1.305556, -11.69582,
  1.347222, -22.11856,
  1.388889, -35.19436,
  1.430556, -48.64917,
  1.472222, -60.20893,
  1.513889, -67.59961,
  1.555556, -68.39506,
  1.597222, -61.17283,
  1.638889, -47.9321,
  1.680556, -32.28395,
  1.722222, -17.8395,
  1.763889, -8.209874,
  2.124931, -4.999999,
};

enum interpolation const array_node_top_cover_rotationx_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_rotationx_angle_sampler = {
  // node_top_cover_rotationx_angle_input
  .input = {
    .float_array = array_node_top_cover_rotationx_angle_input_array,
    .count = 44,
    .stride = 1,
  },
  // node_top_cover_rotationx_angle_output
  .output = {
    .float_array = array_node_top_cover_rotationx_angle_output_array,
    .count = 44,
    .stride = 1,
  },
  // node_top_cover_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_rotationx_angle_intangent_array,
    .count = 44,
    .stride = 2,
  },
  // node_top_cover_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_rotationx_angle_outtangent_array,
    .count = 44,
    .stride = 2,
  },
  // node_top_cover_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_rotationx_angle_interpolation_array,
    .count = 44,
    .stride = 1,
  },
};

float const array_node_top_cover_scale_x_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_scale_x_output_array[] = {
  1.0,
  1.0,
};

float const array_node_top_cover_scale_x_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_top_cover_scale_x_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_top_cover_scale_x_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_scale_x_sampler = {
  // node_top_cover_scale_x_input
  .input = {
    .float_array = array_node_top_cover_scale_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_x_output
  .output = {
    .float_array = array_node_top_cover_scale_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_x_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_scale_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_x_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_scale_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_scale_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_scale_y_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_scale_y_output_array[] = {
  1.0,
  1.0,
};

float const array_node_top_cover_scale_y_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_top_cover_scale_y_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_top_cover_scale_y_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_scale_y_sampler = {
  // node_top_cover_scale_y_input
  .input = {
    .float_array = array_node_top_cover_scale_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_y_output
  .output = {
    .float_array = array_node_top_cover_scale_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_y_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_scale_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_y_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_scale_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_scale_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_top_cover_scale_z_input_array[] = {
  0.0,
  1.791667,
};

float const array_node_top_cover_scale_z_output_array[] = {
  1.0,
  1.0,
};

float const array_node_top_cover_scale_z_intangent_array[] = {
  -0.3332639, 1.0,
  1.194444, 1.0,
};

float const array_node_top_cover_scale_z_outtangent_array[] = {
  0.5972222, 1.0,
  2.124931, 1.0,
};

enum interpolation const array_node_top_cover_scale_z_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_top_cover_scale_z_sampler = {
  // node_top_cover_scale_z_input
  .input = {
    .float_array = array_node_top_cover_scale_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_z_output
  .output = {
    .float_array = array_node_top_cover_scale_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_top_cover_scale_z_intangent
  .in_tangent = {
    .float_array = array_node_top_cover_scale_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_z_outtangent
  .out_tangent = {
    .float_array = array_node_top_cover_scale_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_top_cover_scale_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_top_cover_scale_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

channel const node_channel_node_root_bone_translation_x = {
  .source_sampler = &sampler_node_root_bone_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_root_bone_translation_y = {
  .source_sampler = &sampler_node_root_bone_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_root_bone_translation_z = {
  .source_sampler = &sampler_node_root_bone_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_root_bone_rotationz_angle = {
  .source_sampler = &sampler_node_root_bone_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_root_bone_rotationy_angle = {
  .source_sampler = &sampler_node_root_bone_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_root_bone_rotationx_angle = {
  .source_sampler = &sampler_node_root_bone_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_root_bone_scale_x = {
  .source_sampler = &sampler_node_root_bone_scale_x_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_root_bone_scale_y = {
  .source_sampler = &sampler_node_root_bone_scale_y_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_root_bone_scale_z = {
  .source_sampler = &sampler_node_root_bone_scale_z_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_bottom_cover_translation_x = {
  .source_sampler = &sampler_node_bottom_cover_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_bottom_cover_translation_y = {
  .source_sampler = &sampler_node_bottom_cover_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_bottom_cover_translation_z = {
  .source_sampler = &sampler_node_bottom_cover_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_bottom_cover_rotationz_angle = {
  .source_sampler = &sampler_node_bottom_cover_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bottom_cover_rotationy_angle = {
  .source_sampler = &sampler_node_bottom_cover_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bottom_cover_rotationx_angle = {
  .source_sampler = &sampler_node_bottom_cover_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bottom_cover_scale_x = {
  .source_sampler = &sampler_node_bottom_cover_scale_x_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_bottom_cover_scale_y = {
  .source_sampler = &sampler_node_bottom_cover_scale_y_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_bottom_cover_scale_z = {
  .source_sampler = &sampler_node_bottom_cover_scale_z_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_control_bone_translation_x = {
  .source_sampler = &sampler_node_control_bone_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_control_bone_translation_y = {
  .source_sampler = &sampler_node_control_bone_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_control_bone_translation_z = {
  .source_sampler = &sampler_node_control_bone_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_control_bone_rotationz_angle = {
  .source_sampler = &sampler_node_control_bone_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_control_bone_rotationy_angle = {
  .source_sampler = &sampler_node_control_bone_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_control_bone_rotationx_angle = {
  .source_sampler = &sampler_node_control_bone_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_control_bone_scale_x = {
  .source_sampler = &sampler_node_control_bone_scale_x_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_control_bone_scale_y = {
  .source_sampler = &sampler_node_control_bone_scale_y_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_control_bone_scale_z = {
  .source_sampler = &sampler_node_control_bone_scale_z_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_side_cover_translation_x = {
  .source_sampler = &sampler_node_side_cover_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_side_cover_translation_y = {
  .source_sampler = &sampler_node_side_cover_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_side_cover_translation_z = {
  .source_sampler = &sampler_node_side_cover_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_side_cover_rotationz_angle = {
  .source_sampler = &sampler_node_side_cover_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_side_cover_rotationy_angle = {
  .source_sampler = &sampler_node_side_cover_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_side_cover_rotationx_angle = {
  .source_sampler = &sampler_node_side_cover_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_side_cover_scale_x = {
  .source_sampler = &sampler_node_side_cover_scale_x_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_side_cover_scale_y = {
  .source_sampler = &sampler_node_side_cover_scale_y_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_side_cover_scale_z = {
  .source_sampler = &sampler_node_side_cover_scale_z_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_top_cover_translation_x = {
  .source_sampler = &sampler_node_top_cover_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_top_cover_translation_y = {
  .source_sampler = &sampler_node_top_cover_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_top_cover_translation_z = {
  .source_sampler = &sampler_node_top_cover_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_top_cover_rotationz_angle = {
  .source_sampler = &sampler_node_top_cover_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_top_cover_rotationy_angle = {
  .source_sampler = &sampler_node_top_cover_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_top_cover_rotationx_angle = {
  .source_sampler = &sampler_node_top_cover_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_top_cover_scale_x = {
  .source_sampler = &sampler_node_top_cover_scale_x_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_top_cover_scale_y = {
  .source_sampler = &sampler_node_top_cover_scale_y_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_top_cover_scale_z = {
  .source_sampler = &sampler_node_top_cover_scale_z_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::Z,
};

image const * const images[] = {
};

effect const effect_material_003 = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.03878482f, 0.04486225f, 0.8000157f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.009696205f, 0.01121556f, 0.2000039f, 1.0f},
    },
    .shininess = 46.43856f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_material = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.8f, 0.8f, 0.8f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.2f, 0.2f, 0.2f, 1.0f},
    },
    .shininess = 46.43856f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

material const material_material_003_material = {
  .effect = &effect_material_003,
};

material const material_material_material = {
  .effect = &effect_material,
};

input_element const input_elements_position_0_3_normal_0_3_texcoord_0_3[] = {
  {
    .semantic = "POSITION",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
  {
    .semantic = "NORMAL",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
  {
    .semantic = "TEXCOORD",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
};

triangles const triangles_geom_book[] = {
  {
    .count = 76, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
  {
    .count = 864, // triangles
    .index_offset = 228, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_book = {
  .mesh = {
    .triangles = triangles_geom_book,
    .triangles_count = 2,

    .vertex_buffer_offset = 0,
    .vertex_buffer_size = 21816,

    .index_buffer_offset = 0,
    .index_buffer_size = 11280,
  }
};

geometry const * const geometries[] = {
  &geometry_geom_book,
};

matrix const inverse_bind_matrices_geom_book_skin1[] = {
  {
    0.0254f, -1.11027e-09f, -6.05583e-09f, 0.0f,
    6.05583e-09f, 4.18402e-09f, 0.0254f, 0.0f,
    -1.11027e-09f, -0.0254f, 4.18402e-09f, 0.0f,
    0.0405104f, 0.2942449f, 0.2216883f, 1.0f,
  },
  {
    0.0254f, -1.11027e-09f, -6.05583e-09f, 0.0f,
    6.05583e-09f, 4.05173e-09f, 0.0254f, 0.0f,
    -1.11027e-09f, -0.0254f, 4.05173e-09f, 0.0f,
    0.0405104f, 0.2942449f, 0.2216883f, 1.0f,
  },
  {
    0.0254f, -1.11027e-09f, -6.05583e-09f, 0.0f,
    6.05583e-09f, 4.18453e-09f, 0.0254f, 0.0f,
    -1.11027e-09f, -0.0254f, 4.18453e-09f, 0.0f,
    -0.1620414f, 0.2942449f, 0.2216883f, 1.0f,
  },
  {
    -0.0254f, 3.394e-16f, 2.72502e-09f, 0.0f,
    5.45133e-16f, 0.0254f, 1.91765e-09f, 0.0f,
    -2.72502e-09f, 1.91765e-09f, -0.0254f, 0.0f,
    -0.04051031f, 0.2216883f, 0.2942449f, 1.0f,
  },
  {
    -0.0254f, -1.11027e-09f, 3.83529e-09f, 0.0f,
    -3.83529e-09f, 1.91765e-09f, -0.0254f, 0.0f,
    1.11027e-09f, -0.0254f, -1.91765e-09f, 0.0f,
    -0.04051032f, 0.2942449f, 0.231828f, 1.0f,
  },
};

controller const controller_geom_book_skin1 = {
  .skin = {
    .geometry = &geometry_geom_book,

    .bind_shape_matrix = {
      -4.64649e-06f, 0.0f, -106.2992f, 0.0f,
      -106.2992f, -1.73183e-05f, 4.64649e-06f, 0.0f,
      -1.73183e-05f, 106.2992f, 7.57009e-13f, 0.0f,
      -1.736628f, 0.2053121f, -6.005055f, 1.0f,
    },
    .inverse_bind_matrices = inverse_bind_matrices_geom_book_skin1,

    .vertex_buffer_offset = 0,
    .vertex_buffer_size = 19392,
  }
};

transform const transforms_node_environmentambientlight[] = {
};

instance_geometry const instance_geometries_node_environmentambientlight[] = {
};

instance_controller const instance_controllers_node_environmentambientlight[] = {
};

instance_light const instance_lights_node_environmentambientlight[] = {
  {
    .light = &light_environmentambientlight,
  }
};

channel const * const node_channels_node_environmentambientlight[] = {
};

node const node_node_environmentambientlight = {
  .name = "EnvironmentAmbientLight",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_environmentambientlight,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_environmentambientlight,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_environmentambientlight,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_environmentambientlight,
  .instance_lights_count = 1,

  .channels = node_channels_node_environmentambientlight,
  .channels_count = 0,
};

transform const transforms_node_armature[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, -3.371394f, -4.44089e-16f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 2.22045e-16f, 0.0f, -89.99998f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {39.37008f, 39.37008f, 39.37008f},
  },
};

instance_geometry const instance_geometries_node_armature[] = {
};

instance_controller const instance_controllers_node_armature[] = {
};

instance_light const instance_lights_node_armature[] = {
};

channel const * const node_channels_node_armature[] = {
};

node const node_node_armature = {
  .name = "Armature",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_armature,
  .transforms_count = 3,

  .instance_geometries = instance_geometries_node_armature,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_armature,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_armature,
  .instance_lights_count = 0,

  .channels = node_channels_node_armature,
  .channels_count = 0,
};

transform const transforms_node_root_bone[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-0.04051036f, -0.2942448f, -0.1360549f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, -1.21888e-12f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, -1.36604e-05f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 5.11235e-06f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_root_bone[] = {
};

instance_controller const instance_controllers_node_root_bone[] = {
};

instance_light const instance_lights_node_root_bone[] = {
};

channel const * const node_channels_node_root_bone[] = {
  &node_channel_node_root_bone_scale_x,
  &node_channel_node_root_bone_scale_y,
  &node_channel_node_root_bone_translation_y,
  &node_channel_node_root_bone_rotationy_angle,
  &node_channel_node_root_bone_scale_z,
  &node_channel_node_root_bone_translation_z,
  &node_channel_node_root_bone_rotationx_angle,
  &node_channel_node_root_bone_rotationz_angle,
  &node_channel_node_root_bone_translation_x,
};

node const node_node_root_bone = {
  .name = "root_bone",

  .parent_index = 1,

  .type = node_type::JOINT,

  .transforms = transforms_node_root_bone,
  .transforms_count = 5,

  .instance_geometries = instance_geometries_node_root_bone,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_root_bone,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_root_bone,
  .instance_lights_count = 0,

  .channels = node_channels_node_root_bone,
  .channels_count = 9,
};

transform const transforms_node_root_bone_end[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.6680081f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_root_bone_end[] = {
};

instance_controller const instance_controllers_node_root_bone_end[] = {
};

instance_light const instance_lights_node_root_bone_end[] = {
};

channel const * const node_channels_node_root_bone_end[] = {
};

node const node_node_root_bone_end = {
  .name = "root_bone_end",

  .parent_index = 2,

  .type = node_type::NODE,

  .transforms = transforms_node_root_bone_end,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_root_bone_end,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_root_bone_end,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_root_bone_end,
  .instance_lights_count = 0,

  .channels = node_channels_node_root_bone_end,
  .channels_count = 0,
};

transform const transforms_node_bottom_cover[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-0.04051036f, -0.2942448f, -0.1360549f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, -1.06867e-12f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, -1.36604e-05f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, -4.999998f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_bottom_cover[] = {
};

instance_controller const instance_controllers_node_bottom_cover[] = {
};

instance_light const instance_lights_node_bottom_cover[] = {
};

channel const * const node_channels_node_bottom_cover[] = {
  &node_channel_node_bottom_cover_scale_y,
  &node_channel_node_bottom_cover_rotationz_angle,
  &node_channel_node_bottom_cover_rotationx_angle,
  &node_channel_node_bottom_cover_scale_x,
  &node_channel_node_bottom_cover_translation_y,
  &node_channel_node_bottom_cover_rotationy_angle,
  &node_channel_node_bottom_cover_translation_x,
  &node_channel_node_bottom_cover_translation_z,
  &node_channel_node_bottom_cover_scale_z,
};

node const node_node_bottom_cover = {
  .name = "bottom_cover",

  .parent_index = 1,

  .type = node_type::JOINT,

  .transforms = transforms_node_bottom_cover,
  .transforms_count = 5,

  .instance_geometries = instance_geometries_node_bottom_cover,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bottom_cover,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bottom_cover,
  .instance_lights_count = 0,

  .channels = node_channels_node_bottom_cover,
  .channels_count = 9,
};

transform const transforms_node_bottom_cover_end[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.8867731f, -2.98023e-08f},
  },
};

instance_geometry const instance_geometries_node_bottom_cover_end[] = {
};

instance_controller const instance_controllers_node_bottom_cover_end[] = {
};

instance_light const instance_lights_node_bottom_cover_end[] = {
};

channel const * const node_channels_node_bottom_cover_end[] = {
};

node const node_node_bottom_cover_end = {
  .name = "bottom_cover_end",

  .parent_index = 4,

  .type = node_type::NODE,

  .transforms = transforms_node_bottom_cover_end,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_bottom_cover_end,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bottom_cover_end,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bottom_cover_end,
  .instance_lights_count = 0,

  .channels = node_channels_node_bottom_cover_end,
  .channels_count = 0,
};

transform const transforms_node_control_bone[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.1620414f, -0.2942448f, -0.1360549f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, -1.21915e-12f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, -1.36604e-05f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 5.1135e-06f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_control_bone[] = {
};

instance_controller const instance_controllers_node_control_bone[] = {
};

instance_light const instance_lights_node_control_bone[] = {
};

channel const * const node_channels_node_control_bone[] = {
  &node_channel_node_control_bone_translation_z,
  &node_channel_node_control_bone_translation_y,
  &node_channel_node_control_bone_scale_y,
  &node_channel_node_control_bone_rotationz_angle,
  &node_channel_node_control_bone_scale_z,
  &node_channel_node_control_bone_rotationx_angle,
  &node_channel_node_control_bone_scale_x,
  &node_channel_node_control_bone_rotationy_angle,
  &node_channel_node_control_bone_translation_x,
};

node const node_node_control_bone = {
  .name = "control_bone",

  .parent_index = 1,

  .type = node_type::JOINT,

  .transforms = transforms_node_control_bone,
  .transforms_count = 5,

  .instance_geometries = instance_geometries_node_control_bone,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_control_bone,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_control_bone,
  .instance_lights_count = 0,

  .channels = node_channels_node_control_bone,
  .channels_count = 9,
};

transform const transforms_node_control_bone_end[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.500894f, -1.49012e-08f},
  },
};

instance_geometry const instance_geometries_node_control_bone_end[] = {
};

instance_controller const instance_controllers_node_control_bone_end[] = {
};

instance_light const instance_lights_node_control_bone_end[] = {
};

channel const * const node_channels_node_control_bone_end[] = {
};

node const node_node_control_bone_end = {
  .name = "control_bone_end",

  .parent_index = 6,

  .type = node_type::NODE,

  .transforms = transforms_node_control_bone_end,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_control_bone_end,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_control_bone_end,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_control_bone_end,
  .instance_lights_count = 0,

  .channels = node_channels_node_control_bone_end,
  .channels_count = 0,
};

transform const transforms_node_side_cover[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-0.04051036f, -0.2942448f, -0.1360549f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, 180.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, -8.14222e-13f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 90.00001f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_side_cover[] = {
};

instance_controller const instance_controllers_node_side_cover[] = {
};

instance_light const instance_lights_node_side_cover[] = {
};

channel const * const node_channels_node_side_cover[] = {
  &node_channel_node_side_cover_rotationy_angle,
  &node_channel_node_side_cover_scale_x,
  &node_channel_node_side_cover_translation_y,
  &node_channel_node_side_cover_rotationz_angle,
  &node_channel_node_side_cover_translation_x,
  &node_channel_node_side_cover_rotationx_angle,
  &node_channel_node_side_cover_scale_z,
  &node_channel_node_side_cover_translation_z,
  &node_channel_node_side_cover_scale_y,
};

node const node_node_side_cover = {
  .name = "side_cover",

  .parent_index = 1,

  .type = node_type::JOINT,

  .transforms = transforms_node_side_cover,
  .transforms_count = 5,

  .instance_geometries = instance_geometries_node_side_cover,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_side_cover,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_side_cover,
  .instance_lights_count = 0,

  .channels = node_channels_node_side_cover,
  .channels_count = 9,
};

transform const transforms_node_side_cover_end[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.4535162f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_side_cover_end[] = {
};

instance_controller const instance_controllers_node_side_cover_end[] = {
};

instance_light const instance_lights_node_side_cover_end[] = {
};

channel const * const node_channels_node_side_cover_end[] = {
};

node const node_node_side_cover_end = {
  .name = "side_cover_end",

  .parent_index = 8,

  .type = node_type::NODE,

  .transforms = transforms_node_side_cover_end,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_side_cover_end,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_side_cover_end,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_side_cover_end,
  .instance_lights_count = 0,

  .channels = node_channels_node_side_cover_end,
  .channels_count = 0,
};

transform const transforms_node_top_cover[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-0.04051036f, -0.2942449f, 0.3174614f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, 180.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, 2.23118e-05f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 175.0f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_top_cover[] = {
};

instance_controller const instance_controllers_node_top_cover[] = {
};

instance_light const instance_lights_node_top_cover[] = {
};

channel const * const node_channels_node_top_cover[] = {
  &node_channel_node_top_cover_translation_x,
  &node_channel_node_top_cover_scale_z,
  &node_channel_node_top_cover_scale_y,
  &node_channel_node_top_cover_translation_z,
  &node_channel_node_top_cover_rotationz_angle,
  &node_channel_node_top_cover_scale_x,
  &node_channel_node_top_cover_rotationx_angle,
  &node_channel_node_top_cover_rotationy_angle,
  &node_channel_node_top_cover_translation_y,
};

node const node_node_top_cover = {
  .name = "top_cover",

  .parent_index = 1,

  .type = node_type::JOINT,

  .transforms = transforms_node_top_cover,
  .transforms_count = 5,

  .instance_geometries = instance_geometries_node_top_cover,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_top_cover,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_top_cover,
  .instance_lights_count = 0,

  .channels = node_channels_node_top_cover,
  .channels_count = 9,
};

transform const transforms_node_top_cover_end[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.8867732f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_top_cover_end[] = {
};

instance_controller const instance_controllers_node_top_cover_end[] = {
};

instance_light const instance_lights_node_top_cover_end[] = {
};

channel const * const node_channels_node_top_cover_end[] = {
};

node const node_node_top_cover_end = {
  .name = "top_cover_end",

  .parent_index = 10,

  .type = node_type::NODE,

  .transforms = transforms_node_top_cover_end,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_top_cover_end,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_top_cover_end,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_top_cover_end,
  .instance_lights_count = 0,

  .channels = node_channels_node_top_cover_end,
  .channels_count = 0,
};

transform const transforms_node_book[] = {
};

instance_geometry const instance_geometries_node_book[] = {
};

int const joint_node_indices_node_book_geom_book_skin1[] = {
  2, // joint0 node_root_bone
  4, // joint1 node_bottom_cover
  6, // joint2 node_control_bone
  8, // joint3 node_side_cover
  10, // joint4 node_top_cover
};

instance_material const instance_controller_instance_materials_node_book_0[] = {
  {
    .element_index = 1, // an index into mesh.triangles
    .material = &material_material_material,

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
  {
    .element_index = 0, // an index into mesh.triangles
    .material = &material_material_003_material,

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_controller const instance_controllers_node_book[] = {
  {
    .controller = &controller_geom_book_skin1,

    .joint_node_indices = joint_node_indices_node_book_geom_book_skin1,
    .joint_count = (sizeof (joint_node_indices_node_book_geom_book_skin1)) / (sizeof (int)),

    .instance_materials = instance_controller_instance_materials_node_book_0,
    .instance_materials_count = 2,
  },
};

instance_light const instance_lights_node_book[] = {
};

channel const * const node_channels_node_book[] = {
};

node const node_node_book = {
  .name = "Book",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_book,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_book,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_book,
  .instance_controllers_count = 1,

  .instance_lights = instance_lights_node_book,
  .instance_lights_count = 0,

  .channels = node_channels_node_book,
  .channels_count = 0,
};

transform const transforms_node_camera[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {256.181f, -87.99197f, 70.63641f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {-0.6239836f, -0.4714231f, -0.6232213f, -100.9618f},
  },
};

instance_geometry const instance_geometries_node_camera[] = {
};

instance_controller const instance_controllers_node_camera[] = {
};

instance_light const instance_lights_node_camera[] = {
};

channel const * const node_channels_node_camera[] = {
};

node const node_node_camera = {
  .name = "Camera",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_camera,
  .transforms_count = 2,

  .instance_geometries = instance_geometries_node_camera,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera,
  .channels_count = 0,
};

node const * const nodes[] = {
  &node_node_environmentambientlight, // 0
  &node_node_armature, // 1
  &node_node_root_bone, // 2
  &node_node_root_bone_end, // 3
  &node_node_bottom_cover, // 4
  &node_node_bottom_cover_end, // 5
  &node_node_control_bone, // 6
  &node_node_control_bone_end, // 7
  &node_node_side_cover, // 8
  &node_node_side_cover_end, // 9
  &node_node_top_cover, // 10
  &node_node_top_cover_end, // 11
  &node_node_book, // 12
  &node_node_camera, // 13
};

inputs const inputs_list[] = {
  {
    .elements = input_elements_position_0_3_normal_0_3_texcoord_0_3,
    .elements_count = 3,
  },
};

extern collada::types::descriptor const descriptor;

collada::types::descriptor const descriptor = {
  .nodes = nodes,
  .nodes_count = (sizeof (nodes)) / (sizeof (nodes[0])),

  .inputs_list = inputs_list,
  .inputs_list_count = (sizeof (inputs_list)) / (sizeof (inputs_list[0])),

  .images = images,
  .images_count = (sizeof (images)) / (sizeof (images[0])),

  .position_normal_texture_buffer = "data/scenes/book/book.vtx",
  .joint_weight_buffer = "data/scenes/book/book.vjw",
  .index_buffer = "data/scenes/book/book.idx",
};

}
