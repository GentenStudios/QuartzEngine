#shader vertex
#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;

out vec2 pass_uv;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    pass_uv     = a_uv;
}

#shader pixel
#version 330 core

out vec4          out_fragcolor;

in vec2           pass_uv;

uniform vec3      u_color;
uniform sampler2D u_sampler;

void main()
{
    out_fragcolor = texture2D(u_sampler, pass_uv) * vec4(u_color, 1.0f);
}
