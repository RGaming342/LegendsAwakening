#include "../include/text.h"



TextManager::TextManager():Renderer(DrawType::QUAD){
	if(shader.load("shaders/text/sh.vert","shaders/text/sh.frag")){
		Error("Failed to load text shaders.");
	}
	Renderer.setInput(0,0,2,2,0,0,RenderType::STATIC);
	Renderer.setInput(1,1,2,1,0,1,RenderType::STATIC);
	Renderer.setInput(2,1,2,1,1,1,RenderType::STATIC);
}
TextManager::~TextManager(){ shader.unload(); }

void TextManager::makeString(std::string id, std::string fontID, glm::vec3 pos, glm::vec3 rot, std::string str, float SPACE){
	texts[id].POS = pos;
	texts[id].ROT = rot;
	makeMatrix(id);
	texts[id].font = fontID;
	texts[id].text = str;
	texts[id].spacing = SPACE;
	setColor(id,glm::ivec4(255,255,255,255));
}

void TextManager::setFont(std::string id, std::string fontID){
	texts[id].font = fontID;
	setString(id,texts[id].text,texts[id].spacing);
}
void TextManager::loadFont(std::string fontID,std::string path,int size, uint8_t Spacing,bool isPixel){
	fonts[fontID] = FTloader.load(path,size,Spacing,isPixel);
}

void TextManager::setColor(std::string id, glm::ivec4 color){
	texts[id].R = color.x;
	texts[id].G = color.y;
	texts[id].B = color.z;
	texts[id].A = color.w;
	setString(id,texts[id].text,texts[id].spacing);
}
glm::ivec4 TextManager::getColor(std::string id){
	const auto& data = texts[id];
	return glm::ivec4(data.R,data.G,data.B,data.A);
}

void TextManager::setString(std::string id, std::string str, float SPACE){
	texts[id].text = str;
	texts[id].spacing = SPACE;
	uint32_t color = texts[id].R|(texts[id].G<<8)|(texts[id].B<<16)|(texts[id].A<<24);
	
	std::vector<float> pos;
	std::vector<unsigned int> data;
	
	float Bottom=1,Right=0;
	
	Font& font = fonts[texts[id].font];
	
	float aspectRatio = (float)font.texture.getSize().x / (float)font.texture.getSize().y;
	float Quad[4][2] = {{0,1},{0,0},{0,0},{0,1}};
	
	for(unsigned int i=0;i<texts[id].text.size();i++){
		char ch = str[i];
		switch(ch){
			case '\0':{ i=-1; continue; }break;
			case '\n':{
				for(int j=0;j<4;j++){
					Quad[j][1] -= 1;
					Quad[j][0] = 0;
				}
				Bottom -= 1;
			}break;
			case ' ':{
				float width = (float)font.characters[' '].sizeX/((float)font.texture.getSize().x/10);
				for(int j=0;j<4;j++){
					Quad[j][0] += width;
				}
				Right += width;
			}break;
			default:{
				if(font.characters.find(ch) == font.characters.end()){
					continue;
				}
				auto& info = font.characters[ch];
				float width = (float)info.sizeX/((float)font.texture.getSize().x/10);
				Quad[0][0] += width;
				Quad[1][0] += width;
				for(int j=0;j<4;j++){
					pos.push_back(Quad[j][0]);
					pos.push_back(Quad[j][1]);
				}
				unsigned int DATA = 0;
				
				DATA = (((info.xPos)*1000)+(int)(width*1000));
				DATA |= ((info.yPos+1)*1000)<<16;
				data.push_back(DATA);
				data.push_back(color);
				DATA = (((info.xPos)*1000)+(int)(width*1000));
				DATA |= ((info.yPos)*1000)<<16;
				data.push_back(DATA);
				data.push_back(color);
				DATA = (info.xPos)*1000;
				DATA |= ((info.yPos)*1000)<<16;
				data.push_back(DATA);
				data.push_back(color);
				DATA = (info.xPos)*1000;
				DATA |= ((info.yPos+1)*1000)<<16;
				data.push_back(DATA);
				data.push_back(color);
				
				Quad[0][0] += SPACE;
				Quad[1][0] += SPACE;
				Quad[2][0] += width+SPACE;
				Quad[3][0] += width+SPACE;
				if(Quad[3][0]>Right){
					Right = Quad[3][0];
				}
			}
		};
	}
	Right -= SPACE;
	texts[id].size = glm::vec2(Right,Bottom);
	for(unsigned int i=0;i<pos.size();i+=2){
		pos[i] -= Right/2;
		pos[i+1] -= Bottom/2;
	}
	texts[id].Positions = pos;
	texts[id].Data = data;
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

glm::vec2 getSize(std::string id){
	return texts[id].size;
}



