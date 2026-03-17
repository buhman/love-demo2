#version 430 core

in vec3 PixelNormal;
in vec2 PixelTexture;
/*

in vec4 PixelViewPosition;
in vec4 PixelWorldPosition;
in vec4 PixelLightPosition;
*/

layout (location = 10) uniform vec4 EmissionColor;
layout (location = 11) uniform vec4 AmbientColor;
layout (location = 12) uniform vec4 DiffuseColor;
layout (location = 13) uniform vec4 SpecularColor;

layout (location = 14) uniform float shininess;

layout (location = 15) uniform sampler2D EmissionSampler;
layout (location = 16) uniform sampler2D AmbientSampler;
layout (location = 17) uniform sampler2D DiffuseSampler;
layout (location = 18) uniform sampler2D SpecularSampler;

layout (location = 19) uniform ivec4 TextureChannel;

layout (location = 0) out vec4 g_color;
//layout (location = 1) out vec4 g_position;
//layout (location = 2) out vec4 g_normal;

void main()
{
  vec4 emission;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  if (TextureChannel.x >= 0) { // emission
    emission = texture(EmissionSampler, PixelTexture.xy);
  } else {
    emission = EmissionColor;
  }
  if (TextureChannel.y >= 0) { // ambient
    ambient = texture(AmbientSampler, PixelTexture.xy);
  } else {
    ambient = AmbientColor;
  }
  if (TextureChannel.z >= 0) { // diffuse
    diffuse = texture(DiffuseSampler, PixelTexture.xy);
  } else {
    diffuse = DiffuseColor;
  }
  if (TextureChannel.w >= 0) { // specular
    specular = texture(SpecularSampler, PixelTexture.xy);
  } else {
    specular = SpecularColor;
  }

  vec3 color = emission.xyz * 0;
  color += ambient.xyz * 0.05;
  color += diffuse.xyz * 1;
  color += specular.xyz * 0 * 0.3;

  g_color = vec4(color, 1.0);
  //g_color = vec4(PixelNormal.xyz, 1.0);
  //g_color = vec4(PixelTexture.xy, 0, 1);
}
