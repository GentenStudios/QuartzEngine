#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in int a_TexLayer;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 TexCoord;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_Pos, 1.f);
	TexCoord = vec3(a_UV, a_TexLayer);
}
