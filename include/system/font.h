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
	uint16_t xPos;      // 2 bytes for the x position in the texture atlas
	uint16_t yPos;      // 2 bytes for the y position in the texture atlas
};
struct Font {
	Texture texture;                                     // the texture atlas
	std::unordered_map<char, CharacterData> characters;
};
class FontLoader {
	public:
		FontLoader();
		~FontLoader();
		
		Font load(const std::string& fontPath, unsigned int fontSize, bool isPixel = 0);
		
	private:
		FT_Library m_freetypeLibrary;
};








