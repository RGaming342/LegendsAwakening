#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCD;
out vec3 Color;
out vec2 texcd;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    Color = color;
    texcd = texCD;
}
