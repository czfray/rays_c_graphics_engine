#version 150 core

uniform vec3 testColor;
out vec4 outColor;

void main()
{
    outColor = vec4(testColor, 1.0);
}