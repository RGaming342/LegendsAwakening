#pragma once

#include "system/graphics.h"
#include <string>
#include <unordered_map>
#include <memory>

class ShaderManager {
	public:
		ShaderManager();
		~ShaderManager();
		
		bool load(const std::string& key, const std::string& filename);
		bool use(const std::string& key);
		void unload(const std::string& key);
		void unloadAll();
		Shader* get(const std::string& key);
	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>> shaderMap;
};
