#version 330 core


in vec3 TexCoord;

uniform sampler2DArray u_TexArray;

out vec4 FragColor;

void main()
{
	vec4 texel = texture(u_TexArray, TexCoord);
	FragColor = texel;
}
