//  2 cpp START
//>mk-obj "src/system/*.cpp"
//>mk-obj "src/*.cpp"
//args = "main.cpp -lSDL2 -lSDL2_image src/*.o src/system/*.o"
//mk-exe args "main"
//END

#include <iostream>
#include "include/system/file.h"
#include "include/system/graphics.h"
#include "include/texture-manager.h"
#include "include/shader-manager.h"
#include "include/system/window-input.h"

int main() {
	
	WindowInput window("Legends Awakening",800,600);
	Shader sh;
	if(sh.load("shaders/test.vert","shaders/test.frag")){
		std::cerr<<"Error1"<<std::endl;
	}
	RenderObj tri(DrawType::TRIANGLE);
	tri.setInput(0,0,6,3,0,0,RenderType::STATIC);
	tri.setInput(1,0,6,3,3,0,RenderType::STATIC);
	std::vector<float> posColor = {
		0.0f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f};
	tri.setData(0,posColor);
	while(true){
		window.PollEvents();
		if(window.getWindowEvent() == WindowEvent::CLOSE){
			break;
		}
		
		window.clear();
		sh.use();
		tri.draw();
		window.display();
		
		SDL_Delay(16);
	}
	
	
	
	
	return 0;
}
