#version 330

layout(location = 0) in vec3 aPos;
out vec3 TexCoord;

uniform mat4 viewProjection;

void main(){
	gl_Position = viewProjection * vec4(aPos*vec3(1000000,1000000,1000000), 1.0);
	TexCoord = aPos;
}
