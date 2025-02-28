#version 330

out vec4 FragColor;
in vec3 Color;
in vec2 texcd;

uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, texcd)*vec4(Color,1.0);
}
