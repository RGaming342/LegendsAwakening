#version 330

out vec4 FragColor;
in vec2 TexCoord;
in vec4 Color;

uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord)*Color;
}
