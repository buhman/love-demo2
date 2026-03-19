#version 330 core

in VS_OUT {
  vec3 Position; // world coordinates
  vec3 BlockPosition;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
  flat int Data;
  flat int TextureID;
  flat int Special;
} fs_in;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec4 Normal;
layout (location = 2) out vec3 Color;
layout (location = 3) out vec4 Block;

uniform sampler2D TerrainSampler;
uniform vec3 MousePosition;
uniform vec3 MousePosition2;

void main()
{
  int texture_id = fs_in.TextureID;

  int terrain_x = texture_id % 8;
  int terrain_y = texture_id / 8;
  ivec2 coord = ivec2(terrain_x, terrain_y) * 16;
  coord += ivec2(vec2(fs_in.Texture.x, 1.0 - fs_in.Texture.y) * 16.0);

  vec4 texture_color = texelFetch(TerrainSampler, coord, 0);
  if (texture_color.w != 1.0) {
    discard;
    return;
  }

  float two_sided = float(fs_in.Special == -1); // special

  Position = fs_in.BlockPosition.xzy;
  Normal = vec4(normalize(fs_in.Normal.xzy), two_sided);
  Color = texture_color.xyz;
  Block = vec4(fs_in.BlockID, fs_in.Data, fs_in.TextureID, fs_in.Special);
}
