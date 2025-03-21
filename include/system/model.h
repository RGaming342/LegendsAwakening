#pragma once



#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <iostream>
#include "glm.h"



class Model {
	public:
		struct Vertex {
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoords;
		};
		Model() = default;
		~Model() = default;
		
		Model(Model&& other) noexcept {}
		Model& operator=(Model&& other) noexcept {
			if (this != &other) {
				vertices = other.vertices;
				indices = other.indices;
			}
			return *this;
		}
		
		bool load(const std::string& path);
		
		const std::vector<Vertex>& getVertices() const { return vertices; }
		const std::vector<unsigned int>& getIndices() const { return indices; }
		
	private:
		// Helper functions
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
};
