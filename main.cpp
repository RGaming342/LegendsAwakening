//  2 cpp START
//>mk-obj "src/system/*.cpp"
//>mk-obj "src/*.cpp"
//;mk-obj "core/logger/logger.cpp"
//args = "main.cpp -lSDL2 -lSDL2_image -lfreetype core/logger/logger.o src/*.o src/system/*.o"
//mk-exe args "main"
//END

#include <iostream>
#include "include/system/file.h"
#include "include/system/graphics.h"
#include "include/texture-manager.h"
#include "include/shader-manager.h"
#include "include/system/window-input.h"
#include "include/system/font.h"
#include "include/text.h"

int main() {
	
	WindowInput window("Legends Awakening",800,600);
	/*Shader sh;
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
	*/
	//FontLoader FTloader;
	//auto font = FTloader.load("assets/gontserrat/Gontserrat-Medium.ttf",128,0);
	
	TextManager texts;
	texts.loadFont("mid","assets/gontserrat/Gontserrat-Medium.ttf",128,30);
	texts.makeString("test","mid",glm::vec3(0,0,-5),glm::vec3(0,0,0),"this seems to work?\nRight?\nthis is 1 string\nNot 4\n(it has auto centering)",0.025);
	
	glm::vec3 playerPos(0,0,0);
	//glm::mat4 viewPorjectionMX = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-10.0f,100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600,0.001f,1000.0f);
	glm::quat orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 viewPorjectionMX = projection * glm::mat4_cast(orientation);
	
	texts.setPlayerPosAndView(playerPos,viewPorjectionMX);
	
	while(true){
		window.PollEvents();
		if(window.getWindowEvent() == WindowEvent::CLOSE){
			break;
		}
		
		window.clear();
		//sh.use();
		//font.texture.bind();
		//tri.draw();
		texts.draw("test");
		window.display();
		
		SDL_Delay(16);
	}
	
	
	
	
	return 0;
}
