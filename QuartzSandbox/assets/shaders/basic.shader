#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 pColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	pColor = aColor;
}

#shader pixel
#version 330 core

out vec4 FragColor;

in vec3 pColor;

void main()
{
	FragColor = vec4(pColor, 1.0f);
}
