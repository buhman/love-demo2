#version 330 core

// per-vertex:
in vec3 Position;
in vec3 Normal;
in vec2 Texture;
// per-instance:
in vec3 BlockPosition;
in float BlockID;

out VS_OUT {
  vec3 Position;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
} vs_out;

uniform mat4 Transform;

void main()
{
  vec3 position = Position + BlockPosition; // world coordinates

  vs_out.Position = position;
  vs_out.Normal = Normal.xzy;
  vs_out.Texture = Texture;
  vs_out.BlockID = int(BlockID);

  gl_Position = Transform * vec4(position.xzy, 1.0);
}
