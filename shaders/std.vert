#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
out vec3 Normal;

uniform mat4 viewProjection;
uniform vec3 PLpos;

void main(){
	gl_Position = viewProjection * vec4(aPos-PLpos, 1.0);
	Normal = aNormal;
}
