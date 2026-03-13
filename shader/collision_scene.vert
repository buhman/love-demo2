#version 330 core

// per-vertex
in vec2 Position;

flat out int InstanceID;

uniform mat4 Transform;
uniform bool UseGridTransform;

vec2 world_translation()
{
  if (gl_InstanceID == 0)
    return vec2(0, 0);
  int instance = gl_InstanceID + 1;
  float negative = ((instance % 2) == 0) ? -1.0 : 1.0;

  vec2 translation = (Position.x == 0) ? vec2(1, 0) : vec2(0, 1);

  return translation * negative * (instance >> 1);
}

vec2 grid_transform(vec2 position)
{
  return position * 4 + world_translation();
}

void main()
{
  InstanceID = gl_InstanceID;

  vec2 position;
  if (UseGridTransform)
    position = grid_transform(Position);
  else
    position = Position;

  gl_Position = Transform * vec4(position, 0, 1);
}
