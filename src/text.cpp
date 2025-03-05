#include "../include/text.h"



TextManager::TextManager():Renderer(DrawType::QUAD){
	if(shader.load("shaders/text/sh.vert","shaders/text/sh.frag")){
		Error("Failed to load text shaders.");
	}
	Renderer.setInput(0,0,2,2,0,0,RenderType::STATIC);
	Renderer.setInput(1,1,1,1,0,1,RenderType::STATIC);
}
TextManager::~TextManager(){ shader.unload(); }

void TextManager::makeString(std::string id, std::string fontID, glm::vec3 pos, glm::vec3 rot, std::string str){
	texts[id].POS = pos;
	texts[id].ROT = rot;
	makeMatrix(id);
	texts[id].font = fontID;
	texts[id].text = str;
	setColor(id,glm::ivec4(255,255,255,7));
}

void TextManager::setFont(std::string id, std::string fontID){
	texts[id].font = fontID;
	setString(id,texts[id].text);
}
void TextManager::loadFont(std::string fontID,std::string path,int size,bool isPixel){
	fonts[fontID] = FTloader.load(path,size,isPixel);
}

void TextManager::setColor(std::string id, glm::ivec4 color){
	texts[id].R = color.x/2;
	texts[id].G = color.y/2;
	texts[id].B = color.z/2;
	texts[id].A = color.w;
	setString(id,texts[id].text);
}
glm::ivec4 TextManager::getColor(std::string id){
	const auto& data = texts[id];
	return glm::ivec4(data.R*2,data.G*2,data.B*2,data.A);
}

void TextManager::setString(std::string id, std::string str){
	texts[id].text = str;
	uint32_t color = texts[id].R|(texts[id].G<<7)|(texts[id].B<<14)|(texts[id].A<<21);
	
	float Quad[4][2] = {{1,1},{1,0},{0,0},{0,1}};
	
	std::vector<float> pos = {
		1.0f,  1.0f,
		1.0f,  -1.0f,
		-1.0f,  -1.0f,
		-1.0f,  1.0f};
	texts[id].Positions = pos;
	std::vector<unsigned int> data = {
		(120u|(color<<8)),
		(10u|(color<<8)),
		(0u|(color<<8)),
		(110u|(color<<8))
	};
	texts[id].Data = data;
	
	int Bottom=1,Right=0;
	
	Font& font = fonts[texts[id].font];
	
	int aspectRatio = font.texture.getSize().x / font.texture.getSize().y;
	
	for(unsigned int i=0;i<texts[id].text.size();i++){
		char ch = str[i];
		
		switch(ch){
			case '\0':{ i=-1; continue; }break;
			case '\n':{
				for(int j=0;j<4;j++){
					Quad[j][1] += 1;
					Quad[j][0] = 1;
				}
				Quad[2][0] = 0;
				Quad[3][0] = 0;
				Bottom += 1;
			}break;
			case ' ':{
				for(int j=0;j<4;j++){
					Quad[j][0] += aspectRatio;
				}
				Right += aspectRatio;
			}break;
			default:{
				
				
				
				
				
				
			}
		};
		
		
		
		
		
		
		
	}
	
	
}

std::string TextManager::getString(std::string id){
	return texts[id].text;
}

void TextManager::draw(std::string id) {
	shader.use();
	shader.setMat4("viewProjection",vpMX);
	shader.setMat4("modelMX",texts[id].modelMX);
	shader.setVec3("playerPos",playerPosition);
	fonts[texts[id].font].texture.bind();
	Renderer.setData(0,texts[id].Positions);
	Renderer.setData(1,texts[id].Data);
	Renderer.draw();
}
void TextManager::setRotation(std::string id, glm::vec3 rot){
	texts[id].ROT = rot;
	makeMatrix(id);
}
glm::vec3 TextManager::getRotation(std::string id){
	return texts[id].ROT;
}
void TextManager::setPosition(std::string id, glm::vec3 pos){
	texts[id].POS = pos;
	makeMatrix(id);
}
glm::vec3 TextManager::getPosition(std::string id){
	return texts[id].POS;
}
void TextManager::setPlayerPosAndView(const glm::vec3& playerPos,const glm::mat4& viewProjection){
	playerPosition = playerPos;
	vpMX = viewProjection;
}
void TextManager::makeMatrix(std::string id){
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(texts[id].ROT.y), glm::vec3(0.0f,1.0f,0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(texts[id].ROT.x), glm::vec3(1.0f,0.0f,0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(texts[id].ROT.z), glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), texts[id].POS);
	texts[id].modelMX = translationMatrix * rotationMatrix;
}





