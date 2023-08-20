#version 410

layout (location = 0) in vec3 position;

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

out vec3 v_color;

void main()
{
    v_color = colors[gl_VertexID];
    gl_Position = vec4(position, 1.0);
}