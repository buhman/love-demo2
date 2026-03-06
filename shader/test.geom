#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in VS_OUT {
  int BlockID;
  int Configuration;
} gs_in[1];

out GS_OUT {
  vec3 Normal;
  vec2 Texture;
  flat int BlockID;
} gs_out;

struct PT {
  vec3 Position;
  vec2 Texture;
};

uniform mat4 Transform;

PT vertices[] = PT[24](
    PT(vec3(-1.0, 1.0, -1.0), vec2(1.0, 0.0)),
    PT(vec3(1.0, 1.0, 1.0), vec2(0.0, 1.0)),
    PT(vec3(1.0, 1.0, -1.0), vec2(0.0, 0.0)),
    PT(vec3(1.0, 1.0, 1.0), vec2(1.0, 1.0)),
    PT(vec3(-1.0, -1.0, 1.0), vec2(0.0, 0.0)),
    PT(vec3(1.0, -1.0, 1.0), vec2(1.0, 0.0)),
    PT(vec3(-1.0, 1.0, 1.0), vec2(1.0, 1.0)),
    PT(vec3(-1.0, -1.0, -1.0), vec2(0.0, 0.0)),
    PT(vec3(-1.0, -1.0, 1.0), vec2(1.0, 0.0)),
    PT(vec3(1.0, -1.0, -1.0), vec2(1.0, 0.0)),
    PT(vec3(-1.0, -1.0, 1.0), vec2(0.0, 1.0)),
    PT(vec3(-1.0, -1.0, -1.0), vec2(0.0, 0.0)),
    PT(vec3(1.0, 1.0, -1.0), vec2(1.0, 1.0)),
    PT(vec3(1.0, -1.0, 1.0), vec2(0.0, 0.0)),
    PT(vec3(1.0, -1.0, -1.0), vec2(1.0, 0.0)),
    PT(vec3(-1.0, 1.0, -1.0), vec2(1.0, 1.0)),
    PT(vec3(1.0, -1.0, -1.0), vec2(0.0, 0.0)),
    PT(vec3(-1.0, -1.0, -1.0), vec2(1.0, 0.0)),
    PT(vec3(-1.0, 1.0, 1.0), vec2(1.0, 1.0)),
    PT(vec3(-1.0, 1.0, 1.0), vec2(0.0, 1.0)),
    PT(vec3(-1.0, 1.0, -1.0), vec2(0.0, 1.0)),
    PT(vec3(1.0, -1.0, 1.0), vec2(1.0, 1.0)),
    PT(vec3(1.0, 1.0, 1.0), vec2(0.0, 1.0)),
    PT(vec3(1.0, 1.0, -1.0), vec2(0.0, 1.0))
);

int face_1[4] = int[4](8, 6, 7, 20);
int face_2[4] = int[4](11, 9, 10, 21);
int face_4[4] = int[4](17, 15, 16, 23);
int face_8[4] = int[4](5, 3, 4, 19);
int face_16[4] = int[4](2, 0, 1, 18);
int face_32[4] = int[4](14, 12, 13, 22);

vec4 transform(vec3 p)
{
  return Transform * vec4(p.xzy, 1.0);
}

void emit_face(vec3 normal, int face[4])
{
  vec3 position = gl_in[0].gl_Position.xyz;

  PT vtx0 = vertices[face[0]];
  gl_Position = transform(position + vtx0.Position * 0.5);
  gs_out.Normal = normal.xzy;
  gs_out.Texture = vtx0.Texture;
  EmitVertex();
  PT vtx1 = vertices[face[1]];
  gl_Position = transform(position + vtx1.Position * 0.5);
  gs_out.Normal = normal.xzy;
  gs_out.Texture = vtx1.Texture;
  EmitVertex();
  PT vtx2 = vertices[face[2]];
  gl_Position = transform(position + vtx2.Position * 0.5);
  gs_out.Normal = normal.xzy;
  gs_out.Texture = vtx2.Texture;
  EmitVertex();
  PT vtx3 = vertices[face[3]];
  gl_Position = transform(position + vtx3.Position * 0.5);
  gs_out.Normal = normal.xzy;
  gs_out.Texture = vtx3.Texture;
  EmitVertex();
  EndPrimitive();
}

void main()
{
  gs_out.BlockID = gs_in[0].BlockID;
  int configuration = gs_in[0].Configuration;
  if ((configuration &  1) != 0) emit_face(vec3(-1.0, 0.0, 0.0), face_1);
  if ((configuration &  2) != 0) emit_face(vec3(0.0, -1.0, 0.0), face_2);
  if ((configuration &  4) != 0) emit_face(vec3(0.0, 0.0, -1.0), face_4);
  if ((configuration &  8) != 0) emit_face(vec3(0.0, 0.0, 1.0), face_8);
  if ((configuration & 16) != 0) emit_face(vec3(0.0, 1.0, 0.0), face_16);
  if ((configuration & 32) != 0) emit_face(vec3(1.0, 0.0, 0.0), face_32);
}
