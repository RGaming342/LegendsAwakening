#pragma once



#include "system/glm.h"
#include "system/graphics.h"

class Chunk{
	public:
		Chunk();
		~Chunk();
		
		std::vector<float> getVertices();
		
	private:
		std::vector<float> vertices;
		glm::ivec3 POS;
};
