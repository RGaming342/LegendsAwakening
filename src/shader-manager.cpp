#include "../include/shader-manager.h"

ShaderManager::ShaderManager(){}
ShaderManager::~ShaderManager(){ unloadAll(); }

bool ShaderManager::load(const std::string& key, const std::string& filename){
	if (shaderMap.find(key) != shaderMap.end()) {
		return 0;
	}
	auto newshader = std::make_unique<Shader>();
	if(newshader->load(filename+".vert",filename+".frag")){
		return 1;
	}
	shaderMap[key] = std::move(newshader);
	return 0;
}
bool ShaderManager::use(const std::string& key){
	auto it = shaderMap.find(key);
	if (it != shaderMap.end()) {
		it->second->use();
		return 0;
	}
	return 1;
}
void ShaderManager::unload(const std::string& key){
	auto it = shaderMap.find(key);
	if (it != shaderMap.end()) {
		it->second->unload();
		shaderMap.erase(it);
	}
}
void ShaderManager::unloadAll(){
	for (auto& shader : shaderMap) {
		shader.second->unload();
	}
	shaderMap.clear();
}
Shader* ShaderManager::get(const std::string& key){
	return shaderMap[key].get();
}

