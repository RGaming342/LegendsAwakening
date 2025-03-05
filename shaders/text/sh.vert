#version 330

layout(location = 0) in vec2 aPos;
layout(location = 1) in uint data;
out vec2 TexCoord;
out vec4 Color;

uniform vec3 playerPos;
uniform mat4 modelMX;
uniform mat4 viewProjection;

void main(){
	uint index = data&255u;
	uint R = ((data>>8)&127u)*2u;
	uint G = ((data>>15)&127u)*2u;
	uint B = ((data>>22)&127u)*2u;
	uint A = (((data>>29)&7u)*255u)/7u;
	
	//gl_Position = viewProjection * ((modelMX * vec4(aPos, 1.0)) - vec4(playerPos,0));
	gl_Position = viewProjection * ((modelMX * vec4(aPos, 0.0, 1.0)) - vec4(playerPos,0));
	TexCoord = vec2((index%11u)*0.1,(index/11u)*0.1);
	Color = vec4(R/255.0,G/255.0,B/255.0,A/255.0);
}
