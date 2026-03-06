#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in float BlockID;
layout (location = 2) in float Configuration;

out VS_OUT {
  int BlockID;
  int Configuration;
} vs_out;

uniform mat4 Transform;

void main()
{
  vs_out.BlockID = int(BlockID);
  vs_out.Configuration = int(Configuration);

  gl_Position = vec4(Position.xyz, 1.0);
}
