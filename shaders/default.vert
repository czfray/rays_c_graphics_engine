#version 150 core

in vec2 position;
in vec4 color;
in vec2 texcoord;

out vec4 _color;
out vec2 _texcoord;

uniform mat4 trans;

void main()
{
    gl_Position = trans * vec4(position, 0.0, 1.0);
    _color = color;
    _texcoord = texcoord;
}