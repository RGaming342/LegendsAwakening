//  2 cpp START
//>mk-obj "src/system/*.cpp"
//>mk-obj "src/*.cpp"
//;mk-obj "core/logger/logger.cpp"
//args = "main.cpp -lSDL2 -lSDL2_image -lfreetype -lassimp core/logger/logger.o src/*.o src/system/*.o"
//mk-exe args "main"
//END
#include <iostream>
#include "include/title-menu.h"

int main() {
	textManager.loadFont("standard","assets/gontserrat/Gontserrat-Medium.ttf",128,30,1);
	return TitleMenu();
}
