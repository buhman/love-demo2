#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Texture;

out vec3 PixelNormal;
out vec2 PixelTexture;
out float PixelBlock;

uniform mat4 Transform;

void main()
{
  //gl_Position = vec4(position, 1.0);
  //ourColor = color;

  PixelNormal = Normal.xzy;
  PixelTexture = Texture.xy;
  PixelBlock = Texture.z;

  gl_Position = Transform * vec4(Position.xzy, 1.0);
}
