#version 410

out vec3 color;

in vec3 v_color;

void main() {
    color = v_color;
}