#version 330 core

in GS_OUT {
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
} gs_out;

out vec4 FragColor;

uniform sampler2D TerrainSampler;

int Textures[256] = int[256](
  185,   1,   0,   2,  16,   4,  15,  17, 205, 205, 237, 237,  18,  19,  32,  33,
   34,  20,  52,  48,  49, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,   0,
  185, 185, 185,  64, 185,  13,  12,  29,  28,  39,  38,   5,   5,   7,   8,  35,
   36,  37,  80,  31,  65,   4,  27,  84,  50,  40,  43,  88,  87,  44,  61, 185,
   81,  83, 128,  16, 185,  96,   6,  82,   6,  51,  51, 115,  99, 185,  66,  67,
   66,  70,  72,  73,  74,   4, 102, 103, 104, 105,  14, 102, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185,
  185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185
);

void main()
{
  vec3 light_direction = normalize(vec3(-1, -0.5, 0.5));
  float diffuse_intensity = max(dot(normalize(gs_out.Normal), light_direction), 0.0);

  int terrain_ix = int(Textures[int(gs_out.BlockID)]);
  int terrain_x = terrain_ix % 16;
  int terrain_y = terrain_ix / 16;
  ivec2 coord = ivec2(terrain_x, terrain_y) * 16;
  coord += ivec2(gs_out.Texture.xy * 16.0);

  vec4 texture_color = texelFetch(TerrainSampler, coord, 0);
  if (texture_color.w != 1.0) {
    discard;
    return;
  }

  if (int(gs_out.BlockID) == 18) // leaves
    texture_color.xyz *= vec3(0.125, 0.494, 0.027);

  FragColor = vec4(texture_color.xyz * vec3(diffuse_intensity), 1.0);
}
