#version 410

out vec4 color;

in vec2 texCoord;

uniform sampler2D u_texture;
uniform vec3 u_textColor;

void main()
{
    color = texture(u_texture, texCoord) * vec4(u_textColor, 1.0); 
}