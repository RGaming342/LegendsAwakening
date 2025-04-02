#pragma once



#include "system/glm.h"
#include "system/graphics.h"
#include "half_float.h"

class Chunk{
	public:
		struct Vertices{
			std::vector<float> vertex;
			std::vector<uint> color;
		};
		struct Vertex{
			glm::vec3 pos;
			glm::vec3 norm;
			uint8_t r,g,b,a;
		};
		
		Chunk();
		~Chunk();
		
		Vertices getVertices();
		
		void pushVertex(Vertex& vex);
	private:
		Vertices vertices;
		glm::ivec3 POS;
};
