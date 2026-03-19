#version 430 core

out vec4 Color;

layout (location = 1) uniform vec3 BaseColor;

void main()
{
  Color = vec4(BaseColor, 1);
}
