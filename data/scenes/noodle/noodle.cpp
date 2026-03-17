#include "collada/types.h"

#include "data/scenes/noodle.h"

namespace noodle {

using namespace collada::types;

camera const camera_camera001_camera = {
  .xfov = 45.0f,
  .yfov = 0.0f,
  .znear = 1.0f,
  .zfar = 1000.0f,
  .aspect_ratio = 0.0f,
};

light const light_environmentambientlight = {
  .type = light_type::AMBIENT,
  .color = {0.0f, 0.0f, 0.0f},
};

light const light_omni001_light = {
  .type = light_type::POINT,
  .color = {1.0f, 1.0f, 1.0f},
};

float const array_node_bone001_translation_x_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_translation_x_output_array[] = {
  0.0,
  0.0,
};

float const array_node_bone001_translation_x_intangent_array[] = {
  -0.3329306, 0.0,
  2.223333, 0.0,
};

float const array_node_bone001_translation_x_outtangent_array[] = {
  1.11, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_translation_x_sampler = {
  // node_bone001_translation_x_input
  .input = {
    .float_array = array_node_bone001_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_x_output
  .output = {
    .float_array = array_node_bone001_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_bone001_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone001_translation_y_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_translation_y_output_array[] = {
  0.0,
  0.0,
};

float const array_node_bone001_translation_y_intangent_array[] = {
  -0.3329306, 0.0,
  2.223333, 0.0,
};

float const array_node_bone001_translation_y_outtangent_array[] = {
  1.11, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_translation_y_sampler = {
  // node_bone001_translation_y_input
  .input = {
    .float_array = array_node_bone001_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_y_output
  .output = {
    .float_array = array_node_bone001_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_bone001_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone001_translation_z_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_translation_z_output_array[] = {
  0.0,
  0.0,
};

float const array_node_bone001_translation_z_intangent_array[] = {
  -0.3329306, 0.0,
  2.223333, 0.0,
};

float const array_node_bone001_translation_z_outtangent_array[] = {
  1.11, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_translation_z_sampler = {
  // node_bone001_translation_z_input
  .input = {
    .float_array = array_node_bone001_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_z_output
  .output = {
    .float_array = array_node_bone001_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_bone001_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone001_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone001_rotationz_angle_input_array[] = {
  0.0,
  1.666667,
  3.333333,
};

float const array_node_bone001_rotationz_angle_output_array[] = {
  0.0,
  0.0,
  0.0,
};

float const array_node_bone001_rotationz_angle_intangent_array[] = {
  -0.3329306, 0.0,
  1.111667, 0.0,
  2.778333, 0.0,
};

float const array_node_bone001_rotationz_angle_outtangent_array[] = {
  0.555, 0.0,
  2.221667, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_rotationz_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_rotationz_angle_sampler = {
  // node_bone001_rotationz_angle_input
  .input = {
    .float_array = array_node_bone001_rotationz_angle_input_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationz_angle_output
  .output = {
    .float_array = array_node_bone001_rotationz_angle_output_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone001_rotationz_angle_intangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_rotationz_angle_outtangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_rotationz_angle_interpolation_array,
    .count = 3,
    .stride = 1,
  },
};

float const array_node_bone001_rotationy_angle_input_array[] = {
  0.0,
  1.666667,
  3.333333,
};

float const array_node_bone001_rotationy_angle_output_array[] = {
  0.0,
  0.0,
  0.0,
};

float const array_node_bone001_rotationy_angle_intangent_array[] = {
  -0.3329306, 0.0,
  1.111667, 0.0,
  2.778333, 0.0,
};

float const array_node_bone001_rotationy_angle_outtangent_array[] = {
  0.555, 0.0,
  2.221667, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_rotationy_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_rotationy_angle_sampler = {
  // node_bone001_rotationy_angle_input
  .input = {
    .float_array = array_node_bone001_rotationy_angle_input_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationy_angle_output
  .output = {
    .float_array = array_node_bone001_rotationy_angle_output_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone001_rotationy_angle_intangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_rotationy_angle_outtangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_rotationy_angle_interpolation_array,
    .count = 3,
    .stride = 1,
  },
};

float const array_node_bone001_rotationx_angle_input_array[] = {
  0.0,
  1.666667,
  3.333333,
};

float const array_node_bone001_rotationx_angle_output_array[] = {
  0.0,
  55.0,
  0.0,
};

float const array_node_bone001_rotationx_angle_intangent_array[] = {
  -0.3329306, 0.0,
  1.111667, 55.0,
  2.778333, 0.0,
};

float const array_node_bone001_rotationx_angle_outtangent_array[] = {
  0.555, 0.0,
  2.221667, 55.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone001_rotationx_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_rotationx_angle_sampler = {
  // node_bone001_rotationx_angle_input
  .input = {
    .float_array = array_node_bone001_rotationx_angle_input_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationx_angle_output
  .output = {
    .float_array = array_node_bone001_rotationx_angle_output_array,
    .count = 3,
    .stride = 1,
  },
  // node_bone001_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone001_rotationx_angle_intangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_rotationx_angle_outtangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_bone001_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_rotationx_angle_interpolation_array,
    .count = 3,
    .stride = 1,
  },
};

float const array_node_bone001_scale_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_scale_output_array[] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
};

float const array_node_bone001_scale_intangent_array[] = {
  -0.3329306, 1.0, -0.3329306, 1.0, -0.3329306, 1.0,
  2.223333, 1.0, 2.223333, 1.0, 2.223333, 1.0,
};

float const array_node_bone001_scale_outtangent_array[] = {
  1.11, 1.0, 1.11, 1.0, 1.11, 1.0,
  3.666264, 1.0, 3.666264, 1.0, 3.666264, 1.0,
};

enum interpolation const array_node_bone001_scale_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone001_scale_sampler = {
  // node_bone001_scale_input
  .input = {
    .float_array = array_node_bone001_scale_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_scale_output
  .output = {
    .float_array = array_node_bone001_scale_output_array,
    .count = 2,
    .stride = 3,
  },
  // node_bone001_scale_intangent
  .in_tangent = {
    .float_array = array_node_bone001_scale_intangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone001_scale_outtangent
  .out_tangent = {
    .float_array = array_node_bone001_scale_outtangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone001_scale_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_scale_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone001_inversescaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_inversescaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, -2.41484e-06,
  0.0, 0.0, 0.0, -2.41484e-06,
};

enum interpolation const array_node_bone001_inversescaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone001_inversescaleaxisrotation_sampler = {
  // node_bone001_inversescaleaxisrotation_input
  .input = {
    .float_array = array_node_bone001_inversescaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_inversescaleaxisrotation_output
  .output = {
    .float_array = array_node_bone001_inversescaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone001_inversescaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_inversescaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone001_scaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone001_scaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, 2.41484e-06,
  0.0, 0.0, 0.0, 2.41484e-06,
};

enum interpolation const array_node_bone001_scaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone001_scaleaxisrotation_sampler = {
  // node_bone001_scaleaxisrotation_input
  .input = {
    .float_array = array_node_bone001_scaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone001_scaleaxisrotation_output
  .output = {
    .float_array = array_node_bone001_scaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone001_scaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone001_scaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_translation_x_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_translation_x_output_array[] = {
  7.378868,
  7.378868,
};

float const array_node_bone002_translation_x_intangent_array[] = {
  -0.3329306, 7.378868,
  2.223333, 7.378868,
};

float const array_node_bone002_translation_x_outtangent_array[] = {
  1.11, 7.378868,
  3.666264, 7.378868,
};

enum interpolation const array_node_bone002_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_translation_x_sampler = {
  // node_bone002_translation_x_input
  .input = {
    .float_array = array_node_bone002_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_x_output
  .output = {
    .float_array = array_node_bone002_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_bone002_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_translation_y_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_translation_y_output_array[] = {
  1.90735e-06,
  1.90735e-06,
};

float const array_node_bone002_translation_y_intangent_array[] = {
  -0.3329306, 1.90735e-06,
  2.223333, 1.90735e-06,
};

float const array_node_bone002_translation_y_outtangent_array[] = {
  1.11, 1.90735e-06,
  3.666264, 1.90735e-06,
};

enum interpolation const array_node_bone002_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_translation_y_sampler = {
  // node_bone002_translation_y_input
  .input = {
    .float_array = array_node_bone002_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_y_output
  .output = {
    .float_array = array_node_bone002_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_bone002_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_translation_z_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_translation_z_output_array[] = {
  -5.20561e-09,
  -5.20561e-09,
};

float const array_node_bone002_translation_z_intangent_array[] = {
  -0.3329306, -5.20561e-09,
  2.223333, -5.20561e-09,
};

float const array_node_bone002_translation_z_outtangent_array[] = {
  1.11, -5.20561e-09,
  3.666264, -5.20561e-09,
};

enum interpolation const array_node_bone002_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_translation_z_sampler = {
  // node_bone002_translation_z_input
  .input = {
    .float_array = array_node_bone002_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_z_output
  .output = {
    .float_array = array_node_bone002_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_bone002_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone002_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_rotationz_angle_input_array[] = {
  0.0,
  0.5,
  2.0,
  3.333333,
};

float const array_node_bone002_rotationz_angle_output_array[] = {
  0.0,
  -45.0,
  35.0,
  0.0,
};

float const array_node_bone002_rotationz_angle_intangent_array[] = {
  -0.3329306, 0.0,
  0.3335, -45.0,
  1.5005, 35.0,
  2.889333, 0.0,
};

float const array_node_bone002_rotationz_angle_outtangent_array[] = {
  0.1665, 0.0,
  0.9995, -45.0,
  2.444, 35.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone002_rotationz_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_rotationz_angle_sampler = {
  // node_bone002_rotationz_angle_input
  .input = {
    .float_array = array_node_bone002_rotationz_angle_input_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationz_angle_output
  .output = {
    .float_array = array_node_bone002_rotationz_angle_output_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone002_rotationz_angle_intangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_rotationz_angle_outtangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_rotationz_angle_interpolation_array,
    .count = 4,
    .stride = 1,
  },
};

float const array_node_bone002_rotationy_angle_input_array[] = {
  0.0,
  0.5,
  2.0,
  3.333333,
};

float const array_node_bone002_rotationy_angle_output_array[] = {
  0.0,
  0.0,
  0.0,
  0.0,
};

float const array_node_bone002_rotationy_angle_intangent_array[] = {
  -0.3329306, 0.0,
  0.3335, 0.0,
  1.5005, 0.0,
  2.889333, 0.0,
};

float const array_node_bone002_rotationy_angle_outtangent_array[] = {
  0.1665, 0.0,
  0.9995, 0.0,
  2.444, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone002_rotationy_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_rotationy_angle_sampler = {
  // node_bone002_rotationy_angle_input
  .input = {
    .float_array = array_node_bone002_rotationy_angle_input_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationy_angle_output
  .output = {
    .float_array = array_node_bone002_rotationy_angle_output_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone002_rotationy_angle_intangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_rotationy_angle_outtangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_rotationy_angle_interpolation_array,
    .count = 4,
    .stride = 1,
  },
};

float const array_node_bone002_rotationx_angle_input_array[] = {
  0.0,
  0.5,
  2.0,
  3.333333,
};

float const array_node_bone002_rotationx_angle_output_array[] = {
  0.0,
  0.0,
  0.0,
  0.0,
};

float const array_node_bone002_rotationx_angle_intangent_array[] = {
  -0.3329306, 0.0,
  0.3335, 0.0,
  1.5005, 0.0,
  2.889333, 0.0,
};

float const array_node_bone002_rotationx_angle_outtangent_array[] = {
  0.1665, 0.0,
  0.9995, 0.0,
  2.444, 0.0,
  3.666264, 0.0,
};

enum interpolation const array_node_bone002_rotationx_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_rotationx_angle_sampler = {
  // node_bone002_rotationx_angle_input
  .input = {
    .float_array = array_node_bone002_rotationx_angle_input_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationx_angle_output
  .output = {
    .float_array = array_node_bone002_rotationx_angle_output_array,
    .count = 4,
    .stride = 1,
  },
  // node_bone002_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone002_rotationx_angle_intangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_rotationx_angle_outtangent_array,
    .count = 4,
    .stride = 2,
  },
  // node_bone002_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_rotationx_angle_interpolation_array,
    .count = 4,
    .stride = 1,
  },
};

float const array_node_bone002_scale_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_scale_output_array[] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
};

float const array_node_bone002_scale_intangent_array[] = {
  -0.3329306, 1.0, -0.3329306, 1.0, -0.3329306, 1.0,
  2.223333, 1.0, 2.223333, 1.0, 2.223333, 1.0,
};

float const array_node_bone002_scale_outtangent_array[] = {
  1.11, 1.0, 1.11, 1.0, 1.11, 1.0,
  3.666264, 1.0, 3.666264, 1.0, 3.666264, 1.0,
};

enum interpolation const array_node_bone002_scale_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone002_scale_sampler = {
  // node_bone002_scale_input
  .input = {
    .float_array = array_node_bone002_scale_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_scale_output
  .output = {
    .float_array = array_node_bone002_scale_output_array,
    .count = 2,
    .stride = 3,
  },
  // node_bone002_scale_intangent
  .in_tangent = {
    .float_array = array_node_bone002_scale_intangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone002_scale_outtangent
  .out_tangent = {
    .float_array = array_node_bone002_scale_outtangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone002_scale_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_scale_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_inversescaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_inversescaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
};

enum interpolation const array_node_bone002_inversescaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone002_inversescaleaxisrotation_sampler = {
  // node_bone002_inversescaleaxisrotation_input
  .input = {
    .float_array = array_node_bone002_inversescaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_inversescaleaxisrotation_output
  .output = {
    .float_array = array_node_bone002_inversescaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone002_inversescaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_inversescaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone002_scaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone002_scaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
};

enum interpolation const array_node_bone002_scaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone002_scaleaxisrotation_sampler = {
  // node_bone002_scaleaxisrotation_input
  .input = {
    .float_array = array_node_bone002_scaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone002_scaleaxisrotation_output
  .output = {
    .float_array = array_node_bone002_scaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone002_scaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone002_scaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_translation_x_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_translation_x_output_array[] = {
  9.380154,
  9.380154,
};

float const array_node_bone003_translation_x_intangent_array[] = {
  -0.3329306, 9.380154,
  2.223333, 9.380154,
};

float const array_node_bone003_translation_x_outtangent_array[] = {
  1.11, 9.380154,
  3.666264, 9.380154,
};

enum interpolation const array_node_bone003_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_translation_x_sampler = {
  // node_bone003_translation_x_input
  .input = {
    .float_array = array_node_bone003_translation_x_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_x_output
  .output = {
    .float_array = array_node_bone003_translation_x_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_bone003_translation_x_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_translation_x_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_translation_x_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_translation_y_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_translation_y_output_array[] = {
  -6.48499e-05,
  -6.48499e-05,
};

float const array_node_bone003_translation_y_intangent_array[] = {
  -0.3329306, -6.48499e-05,
  2.223333, -6.48499e-05,
};

float const array_node_bone003_translation_y_outtangent_array[] = {
  1.11, -6.48499e-05,
  3.666264, -6.48499e-05,
};

enum interpolation const array_node_bone003_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_translation_y_sampler = {
  // node_bone003_translation_y_input
  .input = {
    .float_array = array_node_bone003_translation_y_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_y_output
  .output = {
    .float_array = array_node_bone003_translation_y_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_bone003_translation_y_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_translation_y_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_translation_y_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_translation_z_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_translation_z_output_array[] = {
  -8.38796e-07,
  -8.38796e-07,
};

float const array_node_bone003_translation_z_intangent_array[] = {
  -0.3329306, -8.38796e-07,
  2.223333, -8.38796e-07,
};

float const array_node_bone003_translation_z_outtangent_array[] = {
  1.11, -8.38796e-07,
  3.666264, -8.38796e-07,
};

enum interpolation const array_node_bone003_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_translation_z_sampler = {
  // node_bone003_translation_z_input
  .input = {
    .float_array = array_node_bone003_translation_z_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_z_output
  .output = {
    .float_array = array_node_bone003_translation_z_output_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_bone003_translation_z_intangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_translation_z_outtangent_array,
    .count = 2,
    .stride = 2,
  },
  // node_bone003_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_translation_z_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_rotationz_angle_input_array[] = {
  0.0,
  0.5,
  1.0,
  1.5,
  2.0,
  2.5,
  3.333333,
};

float const array_node_bone003_rotationz_angle_output_array[] = {
  0.0,
  45.0,
  45.0,
  45.0,
  35.49053,
  -49.19919,
  0.0,
};

float const array_node_bone003_rotationz_angle_intangent_array[] = {
  -0.3329306, 0.0,
  0.3335, 45.0,
  0.8335, 45.0,
  1.3335, 45.0,
  1.8335, 44.99049,
  2.3335, -49.19919,
  3.055833, 0.0,
};

float const array_node_bone003_rotationz_angle_outtangent_array[] = {
  0.1665, 0.0,
  0.6665, 45.0,
  1.1665, 45.0,
  1.6665, 45.0,
  2.1665, 25.99058,
  2.7775, -49.19919,
  3.666264, 0.0,
};

enum interpolation const array_node_bone003_rotationz_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_rotationz_angle_sampler = {
  // node_bone003_rotationz_angle_input
  .input = {
    .float_array = array_node_bone003_rotationz_angle_input_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationz_angle_output
  .output = {
    .float_array = array_node_bone003_rotationz_angle_output_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone003_rotationz_angle_intangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_rotationz_angle_outtangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_rotationz_angle_interpolation_array,
    .count = 7,
    .stride = 1,
  },
};

float const array_node_bone003_rotationy_angle_input_array[] = {
  0.0,
  0.5,
  1.0,
  1.5,
  2.0,
  2.5,
  3.333333,
};

float const array_node_bone003_rotationy_angle_output_array[] = {
  0.0,
  0.0,
  49.99999,
  -45.0,
  68.42802,
  40.75458,
  0.0,
};

float const array_node_bone003_rotationy_angle_intangent_array[] = {
  -0.3329306, 0.0,
  0.3335, 0.0,
  0.8335, 49.99999,
  1.3335, -45.0,
  1.8335, 68.42802,
  2.3335, 49.29953,
  3.055833, 0.0,
};

float const array_node_bone003_rotationy_angle_outtangent_array[] = {
  0.1665, 0.0,
  0.6665, 0.0,
  1.1665, 49.99999,
  1.6665, -45.0,
  2.1665, 68.42802,
  2.7775, 26.513,
  3.666264, 0.0,
};

enum interpolation const array_node_bone003_rotationy_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_rotationy_angle_sampler = {
  // node_bone003_rotationy_angle_input
  .input = {
    .float_array = array_node_bone003_rotationy_angle_input_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationy_angle_output
  .output = {
    .float_array = array_node_bone003_rotationy_angle_output_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationy_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone003_rotationy_angle_intangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationy_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_rotationy_angle_outtangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationy_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_rotationy_angle_interpolation_array,
    .count = 7,
    .stride = 1,
  },
};

float const array_node_bone003_rotationx_angle_input_array[] = {
  0.0,
  0.5,
  1.0,
  1.5,
  2.0,
  2.5,
  3.333333,
};

float const array_node_bone003_rotationx_angle_output_array[] = {
  1.36604e-05,
  1.36604e-05,
  1.36604e-05,
  1.36604e-05,
  -25.3435,
  -50.24762,
  1.36604e-05,
};

float const array_node_bone003_rotationx_angle_intangent_array[] = {
  -0.3329306, 1.36604e-05,
  0.3335, 1.36604e-05,
  0.8335, 1.36604e-05,
  1.3335, 1.36604e-05,
  1.8335, -16.97727,
  2.3335, -50.24762,
  3.055833, 1.36604e-05,
};

float const array_node_bone003_rotationx_angle_outtangent_array[] = {
  0.1665, 1.36604e-05,
  0.6665, 1.36604e-05,
  1.1665, 1.36604e-05,
  1.6665, 1.36604e-05,
  2.1665, -33.70973,
  2.7775, -50.24762,
  3.666264, 1.36604e-05,
};

enum interpolation const array_node_bone003_rotationx_angle_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_rotationx_angle_sampler = {
  // node_bone003_rotationx_angle_input
  .input = {
    .float_array = array_node_bone003_rotationx_angle_input_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationx_angle_output
  .output = {
    .float_array = array_node_bone003_rotationx_angle_output_array,
    .count = 7,
    .stride = 1,
  },
  // node_bone003_rotationx_angle_intangent
  .in_tangent = {
    .float_array = array_node_bone003_rotationx_angle_intangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationx_angle_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_rotationx_angle_outtangent_array,
    .count = 7,
    .stride = 2,
  },
  // node_bone003_rotationx_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_rotationx_angle_interpolation_array,
    .count = 7,
    .stride = 1,
  },
};

float const array_node_bone003_scale_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_scale_output_array[] = {
  0.9999999, 0.9999999, 1.0,
  0.9999999, 0.9999999, 1.0,
};

float const array_node_bone003_scale_intangent_array[] = {
  -0.3329306, 0.9999999, -0.3329306, 0.9999999, -0.3329306, 1.0,
  2.223333, 0.9999999, 2.223333, 0.9999999, 2.223333, 1.0,
};

float const array_node_bone003_scale_outtangent_array[] = {
  1.11, 0.9999999, 1.11, 0.9999999, 1.11, 1.0,
  3.666264, 0.9999999, 3.666264, 0.9999999, 3.666264, 1.0,
};

enum interpolation const array_node_bone003_scale_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_bone003_scale_sampler = {
  // node_bone003_scale_input
  .input = {
    .float_array = array_node_bone003_scale_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_scale_output
  .output = {
    .float_array = array_node_bone003_scale_output_array,
    .count = 2,
    .stride = 3,
  },
  // node_bone003_scale_intangent
  .in_tangent = {
    .float_array = array_node_bone003_scale_intangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone003_scale_outtangent
  .out_tangent = {
    .float_array = array_node_bone003_scale_outtangent_array,
    .count = 2,
    .stride = 6,
  },
  // node_bone003_scale_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_scale_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_inversescaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_inversescaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, -1.0526e-05,
  0.0, 0.0, 0.0, -1.0526e-05,
};

enum interpolation const array_node_bone003_inversescaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone003_inversescaleaxisrotation_sampler = {
  // node_bone003_inversescaleaxisrotation_input
  .input = {
    .float_array = array_node_bone003_inversescaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_inversescaleaxisrotation_output
  .output = {
    .float_array = array_node_bone003_inversescaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone003_inversescaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_inversescaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

float const array_node_bone003_scaleaxisrotation_input_array[] = {
  0.0,
  3.333333,
};

float const array_node_bone003_scaleaxisrotation_output_array[] = {
  0.0, 0.0, 0.0, 1.0526e-05,
  0.0, 0.0, 0.0, 1.0526e-05,
};

enum interpolation const array_node_bone003_scaleaxisrotation_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_bone003_scaleaxisrotation_sampler = {
  // node_bone003_scaleaxisrotation_input
  .input = {
    .float_array = array_node_bone003_scaleaxisrotation_input_array,
    .count = 2,
    .stride = 1,
  },
  // node_bone003_scaleaxisrotation_output
  .output = {
    .float_array = array_node_bone003_scaleaxisrotation_output_array,
    .count = 2,
    .stride = 4,
  },
  // node_bone003_scaleaxisrotation_interpolation
  .interpolation = {
    .interpolation_array = array_node_bone003_scaleaxisrotation_interpolation_array,
    .count = 2,
    .stride = 1,
  },
};

channel const node_channel_node_bone001_translation_x = {
  .source_sampler = &sampler_node_bone001_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_bone001_translation_y = {
  .source_sampler = &sampler_node_bone001_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_bone001_translation_z = {
  .source_sampler = &sampler_node_bone001_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_bone001_rotationz_angle = {
  .source_sampler = &sampler_node_bone001_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone001_rotationy_angle = {
  .source_sampler = &sampler_node_bone001_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone001_rotationx_angle = {
  .source_sampler = &sampler_node_bone001_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone001_scale = {
  .source_sampler = &sampler_node_bone001_scale_sampler,
  .target_transform_index = 5,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone001_inversescaleaxisrotation = {
  .source_sampler = &sampler_node_bone001_inversescaleaxisrotation_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone001_scaleaxisrotation = {
  .source_sampler = &sampler_node_bone001_scaleaxisrotation_sampler,
  .target_transform_index = 6,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone002_translation_x = {
  .source_sampler = &sampler_node_bone002_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_bone002_translation_y = {
  .source_sampler = &sampler_node_bone002_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_bone002_translation_z = {
  .source_sampler = &sampler_node_bone002_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_bone002_rotationz_angle = {
  .source_sampler = &sampler_node_bone002_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone002_rotationy_angle = {
  .source_sampler = &sampler_node_bone002_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone002_rotationx_angle = {
  .source_sampler = &sampler_node_bone002_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone002_scale = {
  .source_sampler = &sampler_node_bone002_scale_sampler,
  .target_transform_index = 5,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone002_inversescaleaxisrotation = {
  .source_sampler = &sampler_node_bone002_inversescaleaxisrotation_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone002_scaleaxisrotation = {
  .source_sampler = &sampler_node_bone002_scaleaxisrotation_sampler,
  .target_transform_index = 6,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone003_translation_x = {
  .source_sampler = &sampler_node_bone003_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_bone003_translation_y = {
  .source_sampler = &sampler_node_bone003_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_bone003_translation_z = {
  .source_sampler = &sampler_node_bone003_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_bone003_rotationz_angle = {
  .source_sampler = &sampler_node_bone003_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone003_rotationy_angle = {
  .source_sampler = &sampler_node_bone003_rotationy_angle_sampler,
  .target_transform_index = 2,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone003_rotationx_angle = {
  .source_sampler = &sampler_node_bone003_rotationx_angle_sampler,
  .target_transform_index = 3,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_bone003_scale = {
  .source_sampler = &sampler_node_bone003_scale_sampler,
  .target_transform_index = 5,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone003_inversescaleaxisrotation = {
  .source_sampler = &sampler_node_bone003_inversescaleaxisrotation_sampler,
  .target_transform_index = 4,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_bone003_scaleaxisrotation = {
  .source_sampler = &sampler_node_bone003_scaleaxisrotation_sampler,
  .target_transform_index = 6,
  .target_attribute = target_attribute::ALL,
};

image const * const images[] = {
};

effect const effect_coloreffectr5g54b179 = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 0.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.01960784f, 0.2117647f, 0.7019608f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.01960784f, 0.2117647f, 0.7019608f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .shininess = 10.0f,
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

effect const effect_coloreffectr6g134b58 = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 0.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.02352941f, 0.5254902f, 0.227451f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.02352941f, 0.5254902f, 0.227451f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .shininess = 10.0f,
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

material const material_coloreffectr5g54b179_material = {
  .effect = &effect_coloreffectr5g54b179,
};

material const material_coloreffectr6g134b58_material = {
  .effect = &effect_coloreffectr6g134b58,
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

triangles const triangles_geom_box001[] = {
  {
    .count = 60, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_box001 = {
  .mesh = {
    .triangles = triangles_geom_box001,
    .triangles_count = 1,

    .vertex_buffer_offset = 0,
    .vertex_buffer_size = 2592,

    .index_buffer_offset = 0,
    .index_buffer_size = 720,
  }
};

geometry const * const geometries[] = {
  &geometry_geom_box001,
};

matrix const inverse_bind_matrices_geom_box001_skin1[] = {
  {
    4.37114e-08f, -8.74228e-08f, -1.0f, 0.0f,
    8.74228e-08f, 1.0f, -8.74228e-08f, 0.0f,
    1.0f, -8.74228e-08f, 4.37114e-08f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  },
  {
    3.45463e-08f, 1.03685e-06f, -1.0f, 0.0f,
    -4.60877e-14f, 1.0f, 1.03685e-06f, 0.0f,
    1.0f, 1.57076e-14f, 3.45463e-08f, 0.0f,
    -16.75902f, 6.06573e-05f, 1.77593e-07f, 1.0f,
  },
  {
    -4.37114e-08f, 4.76837e-07f, -1.0f, 0.0f,
    1.74846e-07f, 1.0f, 4.76837e-07f, 0.0f,
    1.0f, -1.74846e-07f, -4.37115e-08f, 0.0f,
    -7.378868f, -1.26227e-06f, 6.50286e-07f, 1.0f,
  },
};

controller const controller_geom_box001_skin1 = {
  .skin = {
    .geometry = &geometry_geom_box001,

    .inverse_bind_matrices = inverse_bind_matrices_geom_box001_skin1,

    .vertex_buffer_offset = 0,
    .vertex_buffer_size = 2304,
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

transform const transforms_node_cameratargethelper[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-19.90239f, -27.72767f, 54.6898f},
  },
};

instance_geometry const instance_geometries_node_cameratargethelper[] = {
};

instance_controller const instance_controllers_node_cameratargethelper[] = {
};

instance_light const instance_lights_node_cameratargethelper[] = {
};

channel const * const node_channels_node_cameratargethelper[] = {
};

node const node_node_cameratargethelper = {
  .name = "CameraTargetHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_cameratargethelper,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_cameratargethelper,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_cameratargethelper,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_cameratargethelper,
  .instance_lights_count = 0,

  .channels = node_channels_node_cameratargethelper,
  .channels_count = 0,
};

transform const transforms_node_camera_target[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-12.69313f, 5.226418f, -13.172f},
  },
};

instance_geometry const instance_geometries_node_camera_target[] = {
};

instance_controller const instance_controllers_node_camera_target[] = {
};

instance_light const instance_lights_node_camera_target[] = {
};

channel const * const node_channels_node_camera_target[] = {
};

node const node_node_camera_target = {
  .name = "Camera.Target",

  .parent_index = 1,

  .type = node_type::NODE,

  .transforms = transforms_node_camera_target,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camera_target,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera_target,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera_target,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera_target,
  .channels_count = 0,
};

transform const transforms_node_omni001[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-2.48297e-06f, -56.80384f, 58.23672f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {-0.5773502f, 0.5773503f, 0.5773503f, -120.0f},
  },
};

instance_geometry const instance_geometries_node_omni001[] = {
};

instance_controller const instance_controllers_node_omni001[] = {
};

instance_light const instance_lights_node_omni001[] = {
  {
    .light = &light_omni001_light,
  }
};

channel const * const node_channels_node_omni001[] = {
};

node const node_node_omni001 = {
  .name = "Omni001",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_omni001,
  .transforms_count = 2,

  .instance_geometries = instance_geometries_node_omni001,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_omni001,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_omni001,
  .instance_lights_count = 1,

  .channels = node_channels_node_omni001,
  .channels_count = 0,
};

transform const transforms_node_box001[] = {
};

instance_geometry const instance_geometries_node_box001[] = {
};

int const joint_node_indices_node_box001_geom_box001_skin1[] = {
  6, // joint0 node_bone001
  8, // joint1 node_bone003
  7, // joint2 node_bone002
};

instance_material const instance_controller_instance_materials_node_box001_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material = &material_coloreffectr6g134b58_material,

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_controller const instance_controllers_node_box001[] = {
  {
    .controller = &controller_geom_box001_skin1,

    .joint_node_indices = joint_node_indices_node_box001_geom_box001_skin1,
    .joint_count = (sizeof (joint_node_indices_node_box001_geom_box001_skin1)) / (sizeof (int)),

    .instance_materials = instance_controller_instance_materials_node_box001_0,
    .instance_materials_count = 1,
  },
};

instance_light const instance_lights_node_box001[] = {
};

channel const * const node_channels_node_box001[] = {
};

node const node_node_box001 = {
  .name = "Box001",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_box001,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_box001,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_box001,
  .instance_controllers_count = 1,

  .instance_lights = instance_lights_node_box001,
  .instance_lights_count = 0,

  .channels = node_channels_node_box001,
  .channels_count = 0,
};

transform const transforms_node_bonehelper[] = {
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, -90.00001f},
  },
};

instance_geometry const instance_geometries_node_bonehelper[] = {
};

instance_controller const instance_controllers_node_bonehelper[] = {
};

instance_light const instance_lights_node_bonehelper[] = {
};

channel const * const node_channels_node_bonehelper[] = {
};

node const node_node_bonehelper = {
  .name = "BoneHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_bonehelper,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_bonehelper,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bonehelper,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bonehelper,
  .instance_lights_count = 0,

  .channels = node_channels_node_bonehelper,
  .channels_count = 0,
};

transform const transforms_node_bone001[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_bone001[] = {
};

instance_controller const instance_controllers_node_bone001[] = {
};

instance_light const instance_lights_node_bone001[] = {
};

channel const * const node_channels_node_bone001[] = {
  &node_channel_node_bone001_rotationy_angle,
  &node_channel_node_bone001_rotationz_angle,
  &node_channel_node_bone001_translation_y,
  &node_channel_node_bone001_translation_z,
  &node_channel_node_bone001_rotationx_angle,
  &node_channel_node_bone001_inversescaleaxisrotation,
  &node_channel_node_bone001_scale,
  &node_channel_node_bone001_scaleaxisrotation,
  &node_channel_node_bone001_translation_x,
};

node const node_node_bone001 = {
  .name = "Bone001",

  .parent_index = 5,

  .type = node_type::JOINT,

  .transforms = transforms_node_bone001,
  .transforms_count = 7,

  .instance_geometries = instance_geometries_node_bone001,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bone001,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bone001,
  .instance_lights_count = 0,

  .channels = node_channels_node_bone001,
  .channels_count = 9,
};

transform const transforms_node_bone002[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {7.378868f, 1.90735e-06f, -5.20561e-09f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {1.0f, 1.0f, 1.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_bone002[] = {
};

instance_controller const instance_controllers_node_bone002[] = {
};

instance_light const instance_lights_node_bone002[] = {
};

channel const * const node_channels_node_bone002[] = {
  &node_channel_node_bone002_translation_y,
  &node_channel_node_bone002_scale,
  &node_channel_node_bone002_inversescaleaxisrotation,
  &node_channel_node_bone002_scaleaxisrotation,
  &node_channel_node_bone002_translation_x,
  &node_channel_node_bone002_rotationy_angle,
  &node_channel_node_bone002_rotationz_angle,
  &node_channel_node_bone002_rotationx_angle,
  &node_channel_node_bone002_translation_z,
};

node const node_node_bone002 = {
  .name = "Bone002",

  .parent_index = 6,

  .type = node_type::JOINT,

  .transforms = transforms_node_bone002,
  .transforms_count = 7,

  .instance_geometries = instance_geometries_node_bone002,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bone002,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bone002,
  .instance_lights_count = 0,

  .channels = node_channels_node_bone002,
  .channels_count = 9,
};

transform const transforms_node_bone003[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {9.380154f, -6.48499e-05f, -8.38796e-07f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 1.36604e-05f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
  {
    .type = transform_type::SCALE,
    .scale = {0.9999999f, 0.9999999f, 1.0f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 0.0f, 0.0f},
  },
};

instance_geometry const instance_geometries_node_bone003[] = {
};

instance_controller const instance_controllers_node_bone003[] = {
};

instance_light const instance_lights_node_bone003[] = {
};

channel const * const node_channels_node_bone003[] = {
  &node_channel_node_bone003_scale,
  &node_channel_node_bone003_rotationz_angle,
  &node_channel_node_bone003_rotationy_angle,
  &node_channel_node_bone003_rotationx_angle,
  &node_channel_node_bone003_scaleaxisrotation,
  &node_channel_node_bone003_translation_y,
  &node_channel_node_bone003_inversescaleaxisrotation,
  &node_channel_node_bone003_translation_z,
  &node_channel_node_bone003_translation_x,
};

node const node_node_bone003 = {
  .name = "Bone003",

  .parent_index = 7,

  .type = node_type::JOINT,

  .transforms = transforms_node_bone003,
  .transforms_count = 7,

  .instance_geometries = instance_geometries_node_bone003,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_bone003,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_bone003,
  .instance_lights_count = 0,

  .channels = node_channels_node_bone003,
  .channels_count = 9,
};

transform const transforms_node_camerahelper_1[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-54.43401f, -35.53392f, 57.3912f},
  },
};

instance_geometry const instance_geometries_node_camerahelper_1[] = {
};

instance_controller const instance_controllers_node_camerahelper_1[] = {
};

instance_light const instance_lights_node_camerahelper_1[] = {
};

channel const * const node_channels_node_camerahelper_1[] = {
};

node const node_node_camerahelper_1 = {
  .name = "CameraHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_camerahelper_1,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camerahelper_1,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camerahelper_1,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camerahelper_1,
  .instance_lights_count = 0,

  .channels = node_channels_node_camerahelper_1,
  .channels_count = 0,
};

transform const transforms_node_camera001[] = {
  {
    .type = transform_type::MATRIX,
    .matrix = {0.546629f, -0.8373749f, -8.9407e-08f, 0.0f, 0.4692288f, 0.3063076f, 0.8282512f, 0.0f, -0.6935565f, -0.4527462f, 0.5603571f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_camera001[] = {
};

instance_controller const instance_controllers_node_camera001[] = {
};

instance_light const instance_lights_node_camera001[] = {
};

channel const * const node_channels_node_camera001[] = {
};

node const node_node_camera001 = {
  .name = "Camera001",

  .parent_index = 9,

  .type = node_type::NODE,

  .transforms = transforms_node_camera001,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camera001,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera001,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera001,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera001,
  .channels_count = 0,
};

transform const transforms_node_cameratargethelper_1[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {0.0f, 0.0f, 13.41141f},
  },
};

instance_geometry const instance_geometries_node_cameratargethelper_1[] = {
};

instance_controller const instance_controllers_node_cameratargethelper_1[] = {
};

instance_light const instance_lights_node_cameratargethelper_1[] = {
};

channel const * const node_channels_node_cameratargethelper_1[] = {
};

node const node_node_cameratargethelper_1 = {
  .name = "CameraTargetHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_cameratargethelper_1,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_cameratargethelper_1,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_cameratargethelper_1,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_cameratargethelper_1,
  .instance_lights_count = 0,

  .channels = node_channels_node_cameratargethelper_1,
  .channels_count = 0,
};

transform const transforms_node_camera001_target[] = {
  {
    .type = transform_type::ROTATE,
    .rotate = {-0.6495421f, 0.3687832f, 0.6649015f, -80.98797f},
  },
};

instance_geometry const instance_geometries_node_camera001_target[] = {
};

instance_controller const instance_controllers_node_camera001_target[] = {
};

instance_light const instance_lights_node_camera001_target[] = {
};

channel const * const node_channels_node_camera001_target[] = {
};

node const node_node_camera001_target = {
  .name = "Camera001.Target",

  .parent_index = 11,

  .type = node_type::NODE,

  .transforms = transforms_node_camera001_target,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camera001_target,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera001_target,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera001_target,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera001_target,
  .channels_count = 0,
};

node const * const nodes[] = {
  &node_node_environmentambientlight, // 0
  &node_node_cameratargethelper, // 1
  &node_node_camera_target, // 2
  &node_node_omni001, // 3
  &node_node_box001, // 4
  &node_node_bonehelper, // 5
  &node_node_bone001, // 6
  &node_node_bone002, // 7
  &node_node_bone003, // 8
  &node_node_camerahelper_1, // 9
  &node_node_camera001, // 10
  &node_node_cameratargethelper_1, // 11
  &node_node_camera001_target, // 12
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

  .position_normal_texture_buffer = "data/scenes/noodle/noodle.vtx",
  .joint_weight_buffer = "data/scenes/noodle/noodle.vjw",
  .index_buffer = "data/scenes/noodle/noodle.idx",
};

}
