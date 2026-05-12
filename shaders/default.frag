#version 150 core

in vec2 _texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform vec4 color;

void main()
{
    outColor = texture(tex, _texcoord) * color;
}