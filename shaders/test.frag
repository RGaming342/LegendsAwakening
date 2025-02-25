#version 330

out vec4 FragColor; // Output fragment color
in vec3 Color;
void main()
{
    FragColor = vec4(Color, 1.0); // Orange color (RGBA)
}
