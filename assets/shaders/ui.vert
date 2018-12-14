#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

uniform mat4 u_projection;

out vec3 pass_color;
out vec3 pass_position;

void main()
{
	gl_Position = u_projection * vec4(a_position, 1.0);
	
	pass_color = a_color;
	pass_position = a_position;
}