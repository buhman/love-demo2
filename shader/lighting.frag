#version 330 core

uniform sampler2D PositionSampler;
uniform sampler2D NormalSampler;
uniform sampler2D ColorSampler;

uniform float Linear;
uniform float Quadratic;
uniform vec3 Eye;
uniform vec3 MousePosition;
uniform vec3 MousePosition2;

layout (location = 0) out vec4 Color;

in vec4 PixelTexture;

layout (std140) uniform Lights
{
  vec4 light[256];
};

void main()
{
  vec4 position = texture(PositionSampler, PixelTexture.xy);
  vec4 normal = texture(NormalSampler, PixelTexture.xy);
  vec4 color = texture(ColorSampler, PixelTexture.xy);

  vec3 out_color = color.xyz * 0.1;
  for (int i = 0; i < 82; i++) {
    vec3 light_position = light[i].xzy;
    float light_distance = length(light_position - position.xyz);
    vec3 light_direction = normalize(light_position - position.xyz);
    float diffuse = max(dot(normal.xyz, light_direction), 0.0);
    //float attenuation = 1.0 / (1.0 + Linear * light_distance + Quadratic * light_distance * light_distance);

    float attenuation = 1.0 / (1.0 + Quadratic * light_distance * light_distance);
    //out_color += color.xyz * attenuation * diffuse;
    //out_color = vec3(diffuse);
  }
  vec3 light_direction = normalize(Eye.xyz - position.xyz);
  float diffuse = max(dot(normal.xyz, light_direction), 0.0);
  //if (floor(MousePosition + 0.5) == floor(position.xyz + 0.5))
  //diffuse = 1.5;

  //if (round(MousePosition2) == round(position.xyz))
  //color.xyz = vec3(0.75, 1.25, 0.75);

  out_color = color.xyz * diffuse;
  Color = vec4(out_color, 1.0);
}
