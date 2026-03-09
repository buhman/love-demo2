#version 330 core

uniform sampler2D TextureSampler;

layout (location = 0) out vec4 Color;

in vec4 PixelTexture;

void main()
{
  vec4 sample = texture(TextureSampler, PixelTexture.xy);
  Color = vec4(sample.xyz, 1.0);
}
