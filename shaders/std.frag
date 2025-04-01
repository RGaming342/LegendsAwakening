#version 330

out vec4 FragColor;
in vec3 Normal;

uniform sampler2D texture1;

void main(){
	vec3 lightDir = vec3(0,1,0);
	vec3 norm = normalize(Normal);
	float diff = (dot(norm, lightDir) * 0.5) + 0.5;;
	vec3 color = diff * vec3(0.75,0.75,0.75);
	FragColor = vec4(color,1);
}
