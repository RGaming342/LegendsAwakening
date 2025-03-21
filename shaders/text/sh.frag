#version 330

out vec4 FragColor;
in vec2 TexCoord;
in vec4 Color;

uniform sampler2D texture1;

void main()
{
	vec4 txColor = texture(texture1, TexCoord);
	if (length(txColor.rgb) < 0.99) {
        txColor.a = 0.0;  // Make it fully transparent
    }
	FragColor = txColor*Color;
}
