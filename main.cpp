//  2 cpp START
//>mk-obj "src/system/*.cpp"
//>mk-obj "src/*.cpp"
//args = "main.cpp -lSDL2 -lSDL2_image -lfreetype src/*.o src/system/*.o"
//mk-exe args "main"
//END

#include <iostream>
#include "include/system/file.h"
#include "include/system/graphics.h"
#include "include/texture-manager.h"
#include "include/shader-manager.h"
#include "include/system/window-input.h"
#include "include/system/font.h"

int main() {
	
	WindowInput window("Legends Awakening",600,600);
	Shader sh;
	if(sh.load("shaders/test.vert","shaders/test.frag")){
		std::cerr<<"Error1"<<std::endl;
	}
	RenderObj tri(DrawType::TRIANGLE_STRIP);
	tri.setInput(0,0,3,3,0,0,RenderType::STATIC);
	tri.setInput(1,1,3,3,0,0,RenderType::STATIC);
	tri.setInput(2,2,2,2,0,0,RenderType::STATIC);
	std::vector<float> pos = {
		-1.0f,  1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
		-1.0f,  -1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f};
	tri.setData(0,pos);
	std::vector<float> tex = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f};
	tri.setData(2,tex);
	std::vector<float> color = {
		1.0f,  0.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
		0.0f,  0.0f, 1.0f,
		1.0f,  1.0f, 1.0f};
	tri.setData(1,color);
	
	FontLoader FTloader;
	auto font = FTloader.load("assets/gontserrat/Gontserrat-Medium.ttf",128,0);
	
	while(true){
		window.PollEvents();
		if(window.getWindowEvent() == WindowEvent::CLOSE){
			break;
		}
		
		window.clear();
		sh.use();
		font.texture.bind();
		tri.draw();
		window.display();
		
		SDL_Delay(16);
	}
	
	
	
	
	return 0;
}
