#version 330 core

// per-vertex:
in vec3 Position;
in vec3 Normal;
in vec2 Texture;
// per-instance:
in vec3 BlockPosition;
in int BlockID;
in int Data;
in int TextureID;

out VS_OUT {
  vec3 Position;
  vec3 BlockPosition;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
  flat int Data;
  flat int TextureID;
} vs_out;

uniform mat4 Transform;

void main()
{
  vec3 position = Position + BlockPosition; // world coordinates

  vs_out.Position = position;
  vs_out.BlockPosition = BlockPosition;
  vs_out.Normal = Normal;
  vs_out.Texture = Texture;
  vs_out.BlockID = BlockID;
  vs_out.Data = Data;
  vs_out.TextureID = TextureID;

  gl_Position = Transform * vec4(position.xzy, 1.0);
}
