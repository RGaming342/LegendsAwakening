#include "../../include/system/font.h"



FontLoader::FontLoader(){
	if(FT_Init_FreeType(&m_freetypeLibrary)){
		std::cerr << "Error initializing FreeType" << std::endl;
	}
}
FontLoader::~FontLoader(){
	FT_Done_FreeType(m_freetypeLibrary);
}
Font FontLoader::load(const std::string& fontPath, unsigned int fontSize, bool isPixel) {
	FT_Face face;
	if(FT_New_Face(m_freetypeLibrary, fontPath.c_str(), 0, &face)){
		std::cerr << "Error loading font: " << fontPath << std::endl;
		return Font();
	}
	
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	
	unsigned int maxHeight = 0;
	unsigned int maxWidth = 0;
	unsigned int bottom = 0;
	
	for (unsigned char c = 32; c < 128; ++c) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "Could not load character " << c << std::endl;
			continue;
		}
		unsigned int x = face->glyph->bitmap.width;
		unsigned int y = (face->glyph->bitmap.rows+face->glyph->bitmap_top);
		unsigned int b = face->glyph->bitmap_top;
		if(y<1000)
			maxHeight = std::max(maxHeight, y);
		if(x<1000)
			maxWidth = std::max(maxWidth, x);
		if(b<1000)
			bottom = std::max(bottom, b);
	}
	
	unsigned int height = maxHeight*10;
	unsigned int width = maxWidth*10;
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	std::vector<unsigned char> atlasData(width * height, 0);
	
	int xOffset = 0, yOffset = 0;
	uint8_t dx=0,dy=0;
	
	Font font;
	font.size = fontSize;
	
	for (unsigned char c = 32; c < 128; ++c) {
		font.characters[c] = {dx,dy,0,0,0};
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "Could not load character " << c << std::endl;
			xOffset += maxWidth;
			dx++;
			if (xOffset + maxWidth > width) {
				xOffset = 0;
				yOffset += maxHeight;
				dx=0;
				dy++;
			}
			continue;
		}
		
		FT_Bitmap bitmap = face->glyph->bitmap;
		if(bitmap.rows<1000&&bitmap.width<1000&&face->glyph->bitmap_top<1000){
			font.characters[c].sizeY = bitmap.rows;
			font.characters[c].sizeX = bitmap.width;
			font.characters[c].spaceTop = face->glyph->bitmap_top;
		}else{continue;}
		for (unsigned int y = 0; y < bitmap.rows; ++y) {
			for (unsigned int x = 0; x < bitmap.width; ++x) {
				if (bitmap.buffer[y * bitmap.width + x]) {
					unsigned int texX = xOffset + x;
					unsigned int texY = yOffset + -y+(face->glyph->bitmap_top+bottom);
					if (texX < width && texY < height) {
						atlasData[texY * width + texX] = 255;
					}
				}
			}
		}
		
		xOffset += maxWidth;
		dx++;
		if (xOffset + maxWidth > width) {
			xOffset = 0;
			yOffset += maxHeight;
			dx=0;
			dy++;
		}
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, atlasData.data());
	
	font.texture.setRaw(textureID);
	if(isPixel){
		font.texture.setFarFilter(font.texture.pixel);
		font.texture.setNearFilter(font.texture.pixel);
	}else{
		font.texture.setFarFilter(font.texture.blend);
		font.texture.setNearFilter(font.texture.blend);
	}
	FT_Done_Face(face);
	return font;
}











