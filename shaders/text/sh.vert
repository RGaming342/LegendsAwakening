#version 330

layout(location = 0) in vec2 aPos;
layout(location = 1) in uint data;
layout(location = 2) in uint color;
out vec2 TexCoord;
out vec4 Color;

uniform vec3 playerPos;
uniform mat4 modelMX;
uniform mat4 viewProjection;

void main(){
	uint R = color&0xffu;
	uint G = (color>>8)&0xffu;
	uint B = (color>>16)&0xffu;
	uint A = (color>>24)&0xffu;
	
	float Xtx = (float(data&0xFFFFu)/10000);
	float Ytx = (float((data>>16)&0xFFFFu)/10000);
	
	gl_Position = viewProjection * ((modelMX * vec4(aPos, 0.0, 1.0)) - vec4(playerPos,0));
	TexCoord = vec2(Xtx,Ytx);
	Color = vec4(R/255.0,G/255.0,B/255.0,A/255.0);
}
