#pragma once

#include "system/graphics.h"
#include <string>
#include <unordered_map>
#include <memory>

class TextureManager {
	public:
		TextureManager();
		~TextureManager();
		
		bool load(const std::string& key, const std::string& filename);
		bool bind(const std::string& key);
		void unload(const std::string& key);
		void unloadAll();
	private:
		std::unordered_map<std::string, std::unique_ptr<Texture>> textureMap;
};
