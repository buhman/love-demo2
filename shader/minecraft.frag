#version 330 core

in VS_OUT {
  vec3 Position; // world coordinates
  vec3 BlockPosition;
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
  flat int Data;
} fs_in;

layout (location = 0) out vec3 Position;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec3 Color;

uniform sampler2D TerrainSampler;
uniform vec3 MousePosition;
uniform vec3 MousePosition2;

layout (std140) uniform TextureID
{
  ivec4 block_id_to_texture_id[256 / 4];
};

int wool[16] = int[16]( 64, //  0  64
                       210, // 32 208
                       194, // 32 192
                       178, // 32 176
                       162, // 32 160
                       146, // 32 144
                       130, // 32 128
                       114, // 32 112
                       225, // 16 224
                       209, // 16 208
                       193, // 16 192
                       177, // 16 176
                       161, // 16 160
                       145, // 16 144
                       129, // 16 128
                       113  // 16 112
                       );

void main()
{
  int terrain_ix;
  if (fs_in.BlockID == 35) // cloth
    terrain_ix = wool[fs_in.Data];
  else
    terrain_ix = block_id_to_texture_id[fs_in.BlockID / 4][fs_in.BlockID % 4];

  int terrain_x = terrain_ix % 16;
  int terrain_y = terrain_ix / 16;
  ivec2 coord = ivec2(terrain_x, terrain_y) * 16;
  coord += ivec2(vec2(fs_in.Texture.x, 1.0 - fs_in.Texture.y) * 16.0);

  vec4 texture_color = texelFetch(TerrainSampler, coord, 0);
  if (texture_color.w != 1.0) {
    discard;
    return;
  }

  if (fs_in.BlockID == 18 || fs_in.BlockID == 31) // leaves
    texture_color.xyz *= vec3(0.125, 0.494, 0.027);

  Position = fs_in.Position.xzy;
  Normal = normalize(fs_in.Normal.xzy);

  if (length(fs_in.BlockPosition - floor(MousePosition.xzy)) < 1)
    Color = vec3(0, 1, 0);
  else if (length(fs_in.BlockPosition - floor(MousePosition.xzy)) <= 1)
    Color = vec3(0, 0.5, 0);
  else
    Color = texture_color.xyz;
}
