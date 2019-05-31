#version 330 core

out vec4 FragColor;

in vec2 pass_uv;

uniform vec3 u_color;
uniform sampler2D u_sampler;

void main()
{
	FragColor = texture(u_sampler, pass_uv) * vec4(u_color, 1.0f);
}
