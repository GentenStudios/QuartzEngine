#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform int TexLayer;

uniform sampler2DArray TexArray;

void main()
{
	FragColor = texture(TexArray, vec3(TexCoord, TexLayer)).rgba;
}
