#version 330 core

in VS_OUT {
  vec3 Position; // world coordinates
  vec3 BlockPosition;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
  flat int Data;
  flat int TextureID;
} fs_in;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec3 Color;
layout (location = 3) out vec3 Block;

uniform sampler2D TerrainSampler;
uniform vec3 MousePosition;
uniform vec3 MousePosition2;

void main()
{
  int texture_id = fs_in.TextureID;
  if (fs_in.BlockID == 2) // grass
    texture_id = 0;
  if (fs_in.BlockID == 50 && fs_in.Data == 0) // ?
    texture_id = 61;
  if (fs_in.BlockID == 18)
    texture_id = 11;
  if (fs_in.BlockID == 21)
    texture_id = 17;
  if (fs_in.BlockID == 22)
    texture_id = 16;

  int terrain_x = texture_id % 8;
  int terrain_y = texture_id / 8;
  ivec2 coord = ivec2(terrain_x, terrain_y) * 16;
  coord += ivec2(vec2(fs_in.Texture.x, 1.0 - fs_in.Texture.y) * 16.0);

  vec4 texture_color = texelFetch(TerrainSampler, coord, 0);
  if (texture_color.w != 1.0) {
    //discard;
    //return;
  }

  Position = fs_in.BlockPosition.xzy;
  Normal = normalize(fs_in.Normal.xzy);
  Color = texture_color.xyz;
  Block = vec3(fs_in.BlockID, fs_in.Data, fs_in.TextureID);
}
