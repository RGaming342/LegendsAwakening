#pragma once


#include "Global.h"
#include "game-loop.h"


inline int TitleMenu(){
	
	GameLoop();
	
	textManager.makeString("play","standard",glm::vec3(0,0,0),glm::vec3(0,0,0),100,"Play",0.025);
	textManager.makeString("quit","standard",glm::vec3(0,-100,0),glm::vec3(0,0,0),100,"Quit",0.025);
	glm::vec3 playerPos(0,0,0);
	auto windowSize = window.getWindowSize();
	glm::mat4 viewPorjectionMX = glm::ortho(-((float)windowSize.x/2),(float)windowSize.x/2,-((float)windowSize.y/2),(float)windowSize.y/2,-1.0f,10.0f);
	/*glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600,0.001f,1000.0f);
	glm::quat orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 viewPorjectionMX = projection * glm::mat4_cast(orientation);
	*/
	textManager.setPlayerPosAndView(playerPos,viewPorjectionMX);
	
	while(true){
		window.PollEvents();
		if(window.getWindowEvent() == WindowEvent::CLOSE){
			break;
		}
		
		window.clear();
		textManager.draw("play");
		textManager.draw("quit");
		window.display();
		
		
		SDL_Delay(16);
	}
	
	return 0;
}




