#version 330 core

// per-vertex:
in vec3 Position;
in vec3 Normal;
in vec2 Texture;
// per-instance:
in vec3 BlockPosition;

out VS_OUT {
  vec3 Position;
  vec3 Normal;
  vec2 Texture;
} vs_out;

uniform mat4 Transform;

void main()
{
  vec3 position = Position + BlockPosition; // world coordinates

  vs_out.Position = position;
  vs_out.Normal = Normal;
  vs_out.Texture = Texture;

  gl_Position = Transform * vec4(position.xzy, 1.0);
}
