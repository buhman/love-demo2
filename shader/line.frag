#version 330 core

in VS_OUT {
  vec3 Position; // world coordinates
  vec3 Normal;
  vec2 Texture;
} fs_in;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec3 Color;

void main()
{
  Position = fs_in.Position.xzy;
  Normal = normalize(fs_in.Normal.xzy);
  Color = vec3(0.5, 0, 1);
}
