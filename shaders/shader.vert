#version 460

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 camera;

void main() {
    gl_Position = camera * vec4(position, 1.0);
}
