#version 430 core

in vec4 PixelTexture;

layout (location = 0, binding = 0) uniform sampler2D FlameSampler;
layout (location = 1) uniform int Frame;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec4 Normal;
layout (location = 2) out vec3 Color;
layout (location = 3) out vec4 Block;

const float frames = 1.0 / 4.0;

void main()
{
  vec2 coord = vec2(PixelTexture.x, 1.0 - PixelTexture.y) * vec2(1, frames) + vec2(0, frames * Frame);
  vec4 texture_color = texture(FlameSampler, coord);
  if (texture_color.w == 0) {
    discard;
    return;
  }

  Position = vec3(0, 0, 0);
  Normal = vec4(0, 0, 0, 0);
  Color = vec3(texture_color.xyz);
  Block = vec4(-1, -1, -1, -1);
}
