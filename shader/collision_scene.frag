#version 330 core

out vec4 Color;

flat in int InstanceID;

uniform vec3 BaseColor;

void main()
{
  float intensity = (InstanceID == 0) ? 0.7 : 0.3;

  Color = vec4(BaseColor * intensity, 1);
}
