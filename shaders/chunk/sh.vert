#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 n;
layout(location = 2) in uint Col;
out vec3 Normal;
//out vec3 Color;

uniform mat4 viewProjection;
uniform vec3 PLpos;

void main(){
	gl_Position = viewProjection * vec4(pos-PLpos, 1.0);
	Normal = n;
	//Color = color;
}
