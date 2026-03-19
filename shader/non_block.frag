#version 330 core

in VS_OUT {
  vec3 Position; // world coordinates
  vec3 Normal;
  vec2 Texture;
} fs_in;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec4 Normal;
layout (location = 2) out vec3 Color;

void main()
{
  Position = fs_in.Position;
  Normal = vec4(normalize(fs_in.Normal), 0.0);
  Color = vec3(0, 1, 1);
}
