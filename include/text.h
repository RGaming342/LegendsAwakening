#pragma once

#include "system/graphics.h"
#include "system/font.h"
#include "../core/logger/logger.h"

class TextManager{
	public:
		TextManager();
		~TextManager();
		
		void makeString(std::string id, std::string fontID, glm::vec3 pos, glm::vec3 rot, float Scale, std::string str, float SPACE);
		
		void setFont(std::string id, std::string fontID);
		
		void loadFont(std::string fontID,std::string path,int size, uint8_t Spacing,bool isPixel=0);
		
		void setString(std::string id,std::string str, float SPACE);
		std::string getString(std::string id);
		void draw(std::string id);
		void setRotation(std::string id, glm::vec3 rot);
		glm::vec3 getRotation(std::string id);
		void setPosition(std::string id, glm::vec3 pos);
		glm::vec3 getPosition(std::string id);
		void setColor(std::string id, glm::ivec4 color);
		glm::ivec4 getColor(std::string id);
		
		void setScale(std::string id, float Scale);
		glm::vec2 getSize(std::string id);
		
		void setPlayerPosAndView(const glm::vec3& playerPos,const glm::mat4& viewProjection);
	private:
		struct TextData{
			std::string text;
			glm::vec3 POS,ROT;
			glm::mat4 modelMX;
			uint8_t R,G,B,A;
			std::vector<float> Positions;
			std::vector<unsigned int> Data;
			std::string font;
			float spacing;
			glm::vec2 size;
			float scale=1;
		};
		glm::vec3 playerPosition;
		glm::mat4 vpMX;
		Shader shader;
		RenderObj Renderer;
		FontLoader FTloader;
		std::unordered_map<std::string,Font> fonts;
		std::unordered_map<std::string,TextData> texts;
		void makeMatrix(std::string id);
};
