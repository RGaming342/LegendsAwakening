#include "../include/texture-manager.h"

TextureManager::TextureManager(){}
TextureManager::~TextureManager(){ unloadAll(); }

bool TextureManager::load(const std::string& key, const std::string& filename){
	if (textureMap.find(key) != textureMap.end()) {
		return 0;
	}
	auto newTexture = std::make_unique<Texture>();
	if(newTexture->load(filename)){
		return 1;
	}
	textureMap[key] = std::move(newTexture);
	return 0;
}
bool TextureManager::bind(const std::string& key){
	auto it = textureMap.find(key);
	if (it != textureMap.end()) {
		it->second->bind();
		return 0;
	}
	return 1;
}
void TextureManager::unload(const std::string& key){
	auto it = textureMap.find(key);
	if (it != textureMap.end()) {
		it->second->unload();
		textureMap.erase(it);
	}
}
void TextureManager::unloadAll(){
	for (auto& texture : textureMap) {
		texture.second->unload();
	}
	textureMap.clear();
}
