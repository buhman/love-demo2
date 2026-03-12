#version 330 core

// per-vertex:
in vec3 Position;
in vec3 Normal;
in vec2 Texture;

out VS_OUT {
  vec3 Position;
  vec3 Normal;
  vec2 Texture;
} vs_out;

uniform mat4 WorldTransform;
uniform mat4 Transform;

void main()
{
  vs_out.Position = (WorldTransform * vec4(Position.xzy, 1.0)).xyz;
  vs_out.Normal = (WorldTransform * vec4(Normal.xzy, 0.0)).xyz;
  vs_out.Texture = Texture;

  gl_Position = Transform * vec4(Position.xzy, 1.0);
}
