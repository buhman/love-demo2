#version 430 core

layout (location = 1) uniform vec2 TextureSize;
layout (location = 2) uniform vec4 WidthHeightXY;

layout (location = 3, binding = 0) uniform sampler2D TextureSampler;

out vec4 g_color;

in vec4 PixelTexture;

void main()
{
  vec2 coord = (PixelTexture.xy * WidthHeightXY.xy + WidthHeightXY.zw) * TextureSize;
  vec4 color = texture(TextureSampler, coord);
  g_color = vec4(color.x);
}
