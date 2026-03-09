#version 330 core

const vec2 vtx[4] = vec2[](vec2(-1.0,  1.0),  // tl
                           vec2( 1.0,  1.0),  // tr
                           vec2( 1.0, -1.0),  // br
                           vec2(-1.0, -1.0)); // bl

out vec4 PixelTexture;

void main()
{
  vec2 vertex = vtx[gl_VertexID];

  PixelTexture = vec4(vertex * 0.5 + 0.5, 0, 0);

  gl_Position = vec4(vertex, 0.0, 1.0);
}
