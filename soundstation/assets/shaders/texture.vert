#version 410

// square
// take up the entire screen
vec2 position[4] = vec2[](
    vec2(-1.0, -1.0),
    vec2(1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, 1.0)
);

vec2 texCoords[4] = vec2[](
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0)
);

int indices[6] = int[](
    0, 1, 2,
    2, 1, 3
);

out vec2 texCoord;

void main() {
    gl_Position = vec4(position[indices[gl_VertexID]], 0.0, 1.0);
    texCoord = texCoords[indices[gl_VertexID]];
}