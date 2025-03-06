#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include "graphics.h"
#include <algorithm>
#include <cmath>

struct CharacterData {
	uint8_t xPos;
	uint8_t yPos;
	uint8_t sizeX;
	uint8_t sizeY;
	uint8_t spaceTop;
};
struct Font {
	Texture texture;                                     // the texture atlas
	std::unordered_map<char, CharacterData> characters;
	uint16_t size;
	uint8_t spacing;
};
class FontLoader {
	public:
		FontLoader();
		~FontLoader();
		
		Font load(const std::string& fontPath, unsigned int fontSize, uint8_t Spacing, bool isPixel = 0);
		
	private:
		FT_Library m_freetypeLibrary;
};








