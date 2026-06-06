#version 150 core

in vec3 position;
in vec2 texcoord;

out vec2 _texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
    _texcoord = texcoord;
}