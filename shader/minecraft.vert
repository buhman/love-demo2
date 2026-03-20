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
in int Special;

out VS_OUT {
  vec3 Position;
  vec3 BlockPosition;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
  flat int Data;
  flat int TextureID;
  flat int Special;
} vs_out;

uniform mat4 Transform;

vec3 orientation(vec3 position)
{
  if (Special == 1) { // oriented torch
    if (Data == 1) // "facing east"
      return vec3(position.z, position.y, -position.x);
    else if (Data == 2) // "facing west"
      return vec3(-position.z, position.y, position.x);
    else if (Data == 4) // "facing north"
      return vec3(position.x, position.y, -position.z);
    else // "facing south"
      return position;
  } else {
    return position;
  }
}

void main()
{
  vec3 position = orientation(Position) + BlockPosition; // world coordinates

  vs_out.Position = position;
  vs_out.BlockPosition = BlockPosition;
  vs_out.Normal = orientation(Normal);
  vs_out.Texture = Texture;
  vs_out.BlockID = BlockID;
  vs_out.Data = Data;
  vs_out.TextureID = TextureID;
  vs_out.Special = Special;

  gl_Position = Transform * vec4(position.xzy, 1.0);
}
