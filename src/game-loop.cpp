#include "../include/game-loop.h"

class SkyBox{
	public:
		SkyBox():renderer(DrawType::QUAD){
			skyboxSH.load("shaders/skybox/sh.vert","shaders/skybox/sh.frag");
			if(skyboxTX.loadBox("assets/skybox/","png")){ Error("Failed to load SkyBox"); }
			skyboxTX.setFarFilter(skyboxTX.blend);
			skyboxTX.setNearFilter(skyboxTX.blend);
			renderer.setInput(0,0,3,3,0,0,RenderType::STATIC);
			renderer.setData(0,VertexData);
		}
		~SkyBox(){}
		void render(const glm::mat4& VPMX){
			skyboxSH.use();
			skyboxSH.setMat4("viewProjection",VPMX);
			skyboxTX.bind();
			renderer.draw();
		}
	private:
		const std::vector<float> VertexData = {
			-1.0f, -1.0f,  1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,   -1.0f,  1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,   -1.0f, -1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,   -1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,   -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,   -1.0f, -1.0f,  1.0f
		};
		Texture skyboxTX;
		Shader skyboxSH;
		RenderObj renderer;
};

std::unordered_map<Key,bool> keyStates;

void move(glm::vec3& position,glm::vec3 rotation,glm::vec3 mv){
	glm::mat4 rotP = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	
	glm::mat4 rot   = rotP * rotY;
	
	position += glm::normalize(glm::vec3(glm::vec4(1,0,0,0) * rotY)) * mv.x;
	position.y += mv.y;
	position += glm::normalize(glm::vec3(glm::vec4(0,0,1,0) * rot))  * mv.z;
	
}
glm::mat4 makeVMX(glm::vec3 rot){
	glm::quat orientation = glm::angleAxis(glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::angleAxis(glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::angleAxis(glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	return glm::mat4_cast(orientation);
}
void handlePlayerMovement(glm::vec3& position,const glm::vec3& rotation,glm::vec3& velocity,const glm::vec3& maxSpeed){
	velocity = glm::vec3(0,0,0);
	if(keyStates[Key::W]){ velocity.z += -maxSpeed.z; }
	if(keyStates[Key::S]){ velocity.z += maxSpeed.z; }
	if(keyStates[Key::A]){ velocity.x += -maxSpeed.x; }
	if(keyStates[Key::D]){ velocity.x += maxSpeed.x; }
	if(keyStates[Key::L_SHIFT]){ position.y += -maxSpeed.y; }
	if(keyStates[Key::SPACE]){ position.y += maxSpeed.y; }
	
	move(position,rotation,velocity);
}
void handlePlayerLooking(const glm::vec2& MousePosition,glm::vec3& rotation,const float& maxPitch,const float sensitivity){
	
	glm::vec2 delta = MousePosition * sensitivity;
	
	rotation.y += delta.x;
	rotation.x += delta.y;
	
	if (rotation.x > maxPitch) rotation.x = maxPitch;
	if (rotation.x < -maxPitch) rotation.x = -maxPitch;
	
	if (rotation.y < 0.0f) rotation.y += 360.0f;
	if (rotation.y >= 360.0f) rotation.y -= 360.0f;
}











void GameLoop(){
	//glClearColor(0x87/255.0f, 0xCE/255.0f, 0xEB/255.0f, 1.0f);
	SkyBox skybox;
	
	
	textManager.makeString("play","standard",glm::vec3(0,0,0),glm::vec3(0,0,0),1,"Play",0.025);
	glm::vec3 PLpos(0,0,0);
	glm::vec3 PLrot(0,0,0);
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600,0.1f,100000000.0f);
	glm::mat4 viewPorjectionMX = projection * makeVMX(PLrot);
	
	textManager.setPlayerPosAndView(PLpos,viewPorjectionMX);
	textManager.setColor("play",glm::ivec4(255,0,0,255));
	
	bool MS_ENB=false,WIRE=false;
	
	
	
	RenderObj meshtest(DrawType::TRIANGLE);
	meshtest.setInput(0,0,6,3,0,0,RenderType::STATIC);
	meshtest.setInput(1,0,6,3,3,0,RenderType::STATIC);
	
	Model model;
	model.load("assets/test.obj");
	auto vtc = model.getVertices();
	Chunk chunk;
	std::vector<float> v = chunk.getVertices();
	for(uint i=0;i<vtc.size();i++){
		v.push_back(vtc[i].position.x);
		v.push_back(vtc[i].position.y);
		v.push_back(vtc[i].position.z);
		v.push_back(vtc[i].normal.x);
		v.push_back(vtc[i].normal.y);
		v.push_back(vtc[i].normal.z);
	}
	meshtest.setData(0,v);
	Shader standardShader;
	standardShader.load("shaders/std.vert","shaders/std.frag");
	
	glm::vec3 velocity(0,0,0);
	glm::vec3 maxSpeed(0.1,0.1,0.15);
	while(true){
		glm::mat4 viewPorjectionMX = projection * makeVMX(PLrot);
		standardShader.setMat4("viewProjection",viewPorjectionMX);
		standardShader.setVec3("PLpos",PLpos);
		textManager.setPlayerPosAndView(PLpos,viewPorjectionMX);
		handlePlayerMovement(PLpos,PLrot,velocity,maxSpeed);
		window.PollEvents();
		if(window.getWindowEvent() == WindowEvent::CLOSE){
			break;
		}
		while(window.isThereKey()){
			WindowInput::KeyEvent key = window.getKey();
			if(key.type == KeyEventType::KEYDOWN){
				keyStates[key.key] = true;
				if(key.key == Key::M){
					MS_ENB = !MS_ENB;
					SDL_SetRelativeMouseMode((MS_ENB)?SDL_TRUE:SDL_FALSE);
					if(MS_ENB){ window.getMousePosition(); }
				}
				if(key.key == Key::G){
					WIRE = !WIRE;
					glPolygonMode(GL_FRONT_AND_BACK, (WIRE)?GL_LINE:GL_FILL);
				}
			}else if(key.type == KeyEventType::KEYUP){
				keyStates[key.key] = false;
			}
		}
		if(MS_ENB){
			glm::ivec2 mousepos = window.getMousePosition();
			handlePlayerLooking(mousepos,PLrot,90.0f,1);
		}
		
		window.clear();
		skybox.render(viewPorjectionMX);
		textManager.draw("play");
		standardShader.use();
		meshtest.draw();
		window.display();
		
		
		SDL_Delay(16);
	}
	
	
	
	
	
}






/*
proper mouse looking logic
3d model loading
chunk system
basic gravity
basic terrain collision
*/




