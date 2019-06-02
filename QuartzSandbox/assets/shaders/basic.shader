#shader vertex
#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in vec3 a_color;

out vec2 pass_uv;
out vec3 pass_position;
out vec3 pass_color;

uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position   =  u_projection * u_view * vec4(a_pos, 1.0);
    pass_uv       = a_uv;
    pass_position = a_pos;
    pass_color    = a_color;
}

#shader pixel
#version 330 core

out vec4          out_fragcolor;

in vec2           pass_uv;
in vec3           pass_position;
in vec3           pass_color;

uniform vec3      u_color;
uniform sampler2D u_sampler;

void main()
{
    out_fragcolor = texture2D(u_sampler, pass_uv) * vec4(pass_color, 1.0f);
}
