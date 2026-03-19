#version 430 core

layout (location = 0) in vec2 Position;

layout (location = 0) uniform mat4 Transform;

void main()
{
  gl_Position = Transform * vec4(Position, 0, 1);
}
