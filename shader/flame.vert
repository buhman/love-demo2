#version 430 core

layout (location = 2) uniform mat4 Transform;
layout (location = 3) uniform vec3 Eye;

const vec2 vtx[4] = vec2[](vec2(-1.0,  1.0),  // tl
                           vec2( 1.0,  1.0),  // tr
                           vec2( 1.0, -1.0),  // br
                           vec2(-1.0, -1.0)); // bl

out vec4 PixelTexture;

const vec3 up = vec3(0, 0, 1);

layout (std140, binding = 0) uniform Lights
{
  vec4 light[256];
};

void main()
{
  vec2 vertex = vtx[gl_VertexID];

  PixelTexture = vec4(vertex * 0.5 + 0.5, 0, 0);

  vec4 light_instance = light[gl_InstanceID];
  bool is_candle = light_instance.w == 5;
  float z_offset = is_candle ? 0.17 : 0.5;
  float y_offset = float(light_instance.w == 4) - float(light_instance.w == 3);
  float x_offset = float(light_instance.w == 2) - float(light_instance.w == 1);

  float size = is_candle ? 0.1 : 0.25;

  vec3 global_position = light_instance.xzy + vec3(x_offset * 0.2, y_offset * 0.2, z_offset);
  vec3 direction = global_position - Eye;
  vec3 normal = normalize(vec3(direction.x, direction.y, 0));
  vec3 right = normalize(cross(normal, up));

  vec3 position = global_position + (vertex.x * right + vertex.y * up) * size;

  gl_Position = Transform * vec4(position, 1);
}
