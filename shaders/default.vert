#version 150 core

in vec2 position;
in vec4 color;
in vec2 texcoord;

out vec4 _color;
out vec2 _texcoord;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    _color = color;
    _texcoord = texcoord;
}