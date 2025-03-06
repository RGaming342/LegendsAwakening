#version 330

out vec4 FragColor;
in vec2 TexCoord;
in vec4 Color;

uniform sampler2D texture1;

void main()
{
	vec4 txColor = texture(texture1, TexCoord);
	if(txColor.x<0.5){
		txColor.w = 0;
	}
	FragColor = texture(texture1, TexCoord)*Color;
}
