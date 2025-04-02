#include "../include/chunk.h"

void sp(Chunk::Vertex& vex, float a,float b,float c){
	vex.pos.x = a;
	vex.pos.y = b;
	vex.pos.z = c;
}
void sn(Chunk::Vertex& vex, glm::vec3 v){
	vex.norm.x = v.x;
	vex.norm.y = v.y;
	vex.norm.z = v.z;
}
void sc(Chunk::Vertex& vex, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	vex.r=r;
	vex.g=g;
	vex.b=b;
	vex.a=a;
}

glm::vec3 normal(Chunk::Vertex& vex1,Chunk::Vertex& vex2,Chunk::Vertex& vex3){
	
	glm::vec3 v2(vex1.pos.x, vex1.pos.y, vex1.pos.z);
	glm::vec3 v1(vex2.pos.x, vex2.pos.y, vex2.pos.z);
	glm::vec3 v0(vex3.pos.x, vex3.pos.y, vex3.pos.z);
	
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
			Vertex vex1;
			Vertex vex2;
			Vertex vex3;
			
			sp(vex1, (float)i,  (float)0,(float)k   );
			sp(vex2, (float)i+1,(float)0,(float)k+1 );
			sp(vex3, (float)i,  (float)0,(float)k+1 );
			
			glm::vec3 n = normal(vex1,vex2,vex3);
			sn(vex1, n );
			sn(vex2, n );
			sn(vex3, n );
			
			pushVertex(vex1);
			pushVertex(vex2);
			pushVertex(vex3);
			
			sp(vex1, (float)i+1,(float)0,(float)k   );
			sp(vex2, (float)i+1,(float)0,(float)k+1 );
			sp(vex3, (float)i,  (float)0,(float)k   );
			
			n = normal(vex1,vex2,vex3);
			sn(vex1, n );
			sn(vex2, n );
			sn(vex3, n );
			
			pushVertex(vex1);
			pushVertex(vex2);
			pushVertex(vex3);
			
		}
	}
	
	
	
	
}
Chunk::~Chunk(){}



Chunk::Vertices Chunk::getVertices(){
	return vertices;
}
void Chunk::pushVertex(Vertex& vex){
	uint RGBA = vex.r|(vex.g<<8)|(vex.b<<16)|(vex.a<<24);
	vertices.vertex.push_back(vex.pos.x);
	vertices.vertex.push_back(vex.pos.y);
	vertices.vertex.push_back(vex.pos.z);
	vertices.vertex.push_back(vex.norm.x);
	vertices.vertex.push_back(vex.norm.y);
	vertices.vertex.push_back(vex.norm.z);
	vertices.color.push_back(RGBA);
}


