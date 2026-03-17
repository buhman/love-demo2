#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Texture;

layout (location = 0) uniform mat4 Transform;

out vec3 PixelNormal;
out vec2 PixelTexture;

void main()
{
  PixelNormal = Normal;
  PixelTexture = vec2(Texture.x, 1.0 - Texture.y);

  gl_Position = Transform * vec4(Position, 1);
}
