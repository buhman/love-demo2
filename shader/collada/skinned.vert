#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Texture;
layout (location = 3) in ivec4 BlendIndices;
layout (location = 4) in vec4 BlendWeight;

layout (location = 0) uniform mat4 Transform;

layout (std140, binding = 0) uniform JointsLayout
{
  mat4 Joints[64];
};

out vec3 PixelNormal;
out vec2 PixelTexture;

void main()
{
  PixelNormal = Normal;
  PixelTexture = vec2(Texture.x, 1.0 - Texture.y);

  mat4 skin
    = BlendWeight.x * Joints[BlendIndices.x]
    + BlendWeight.y * Joints[BlendIndices.y]
    + BlendWeight.z * Joints[BlendIndices.z]
    + BlendWeight.w * Joints[BlendIndices.w]
    ;

  vec4 position = skin * vec4(Position, 1);

  gl_Position = Transform * position;
}
