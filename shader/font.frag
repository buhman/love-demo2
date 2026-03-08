#version 330 core

uniform sampler2D TextureSampler;

uniform vec2 Cell;
uniform vec2 Glyph;

out vec4 g_color;

in vec4 PixelTexture;

void main()
{
  vec4 sample = texture(TextureSampler, PixelTexture.xy * Cell + Cell * Glyph);
  float px = sample.x == 0.0 ? 0.0 : 1.0;

  g_color = vec4(vec3(px), 1.0);
}
