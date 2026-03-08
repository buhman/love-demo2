#version 330 core

const vec2 vtx[4] = vec2[](vec2(-1.0,  1.0),  // tl
                           vec2( 1.0,  1.0),  // tr
                           vec2( 1.0, -1.0),  // br
                           vec2(-1.0, -1.0)); // bl

/*
tl tr
   br

0 1 2
tr tl br
1 0 2

tl
bl br

2 1 3
br tl bl
2 0 3

1 0 2 3
*/

uniform mat4 Transform;

out vec4 PixelTexture;

void main()
{
  vec2 vertex = vtx[gl_VertexID];

  PixelTexture = vec4(vertex * vec2(0.5, -0.5) + 0.5, 0, 0);

  vertex = vertex * vec2(0.5, 0.5) + vec2(0.5, -0.5);

  gl_Position = Transform * vec4(vertex, 0.0, 1.0);
}
