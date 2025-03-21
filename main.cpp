//  2 cpp START
//>mk-obj "src/system/*.cpp"
//>mk-obj "src/*.cpp"
//;mk-obj "core/logger/logger.cpp"
//args = "main.cpp -lSDL2 -lSDL2_image -lfreetype -lassimp core/logger/logger.o src/*.o src/system/*.o"
//mk-exe args "main"
//END
//https://www.youtube.com/watch?v=it0lsREGdmc&list=PLWTXKdBN8RZe3ytf6qdR4g1JRy0j-93v9
//https://www.youtube.com/watch?v=o7CHV8Osx-M
#include <iostream>
#include "include/title-menu.h"

int main() {
	textManager.loadFont("standard","assets/gontserrat/Gontserrat-Medium.ttf",128,30,1);
	return TitleMenu();
}
