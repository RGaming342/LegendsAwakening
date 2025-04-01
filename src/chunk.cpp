#include "../include/chunk.h"

void push3(std::vector<float>& vec, float a,float b,float c){
	vec.push_back( a );
	vec.push_back( b );
	vec.push_back( c );
}
void pop6(std::vector<float>& vec){
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
}

glm::vec3 normal(const std::vector<float>& vec){
	
	glm::vec3 v2(vec[vec.size() - 9], vec[vec.size() - 8], vec[vec.size() - 7]);
	glm::vec3 v1(vec[vec.size() - 6], vec[vec.size() - 5], vec[vec.size() - 4]);
	glm::vec3 v0(vec[vec.size() - 3], vec[vec.size() - 2], vec[vec.size() - 1]);
	
	// Compute edge vectors
	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;
	
	// Compute normal (cross product)
	glm::vec3 n = glm::normalize(glm::cross(edge1, edge2));
	
	return n;
}

Chunk::Chunk(){
	for(int i=0;i<32;i++){
		for(int k=0;k<32;k++){
			
			push3(vertices, (float)i,(float)0,(float)k );
			push3(vertices, (float)i+1,(float)0,(float)k+1 );
			push3(vertices, (float)i,(float)0,(float)k+1 );
			
			glm::vec3 n = normal(vertices);
			pop6(vertices);
			push3(vertices, n.x,n.y,n.z );
			push3(vertices, (float)i+1,(float)0,(float)k+1 );
			push3(vertices, n.x,n.y,n.z );
			push3(vertices, (float)i,(float)0,(float)k+1 );
			push3(vertices, n.x,n.y,n.z );
			
			push3(vertices, (float)i+1,(float)0,(float)k );
			push3(vertices, (float)i+1,(float)0,(float)k+1 );
			push3(vertices, (float)i,(float)0,(float)k );
			
			n = normal(vertices);
			pop6(vertices);
			push3(vertices, n.x,n.y,n.z );
			push3(vertices, (float)i+1,(float)0,(float)k+1 );
			push3(vertices, n.x,n.y,n.z );
			push3(vertices, (float)i,(float)0,(float)k );
			push3(vertices, n.x,n.y,n.z );
		}
	}
	
	
	
	
}
Chunk::~Chunk(){}



std::vector<float> Chunk::getVertices(){
	return vertices;
}
