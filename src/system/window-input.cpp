#include "../../include/system/window-input.h"
#include <iostream>



WindowInput::WindowInput(const std::string& title, int width, int height){
	
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		exit(1); // Exit if SDL initialization fails
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF)==0) {
		std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	// Create the window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		exit(1); // Exit if window creation fails
	}
	context = SDL_GL_CreateContext(window);
	if (!context) {
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD"<< std::endl;
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
	SDL_GL_SetSwapInterval(0);
	glViewport(0,0,width,height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
WindowInput::~WindowInput() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void WindowInput::clear(uint32_t color){
	if(color!=0){ glClearColor(((color>>16)&&0xff)/255.0f,((color>>8)&&0xff)/255.0f,(color&&0xff)/255.0f,((color>>24)&&0xff)/255.0f); }
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void WindowInput::display(){
	SDL_GL_SwapWindow(window);
}

void WindowInput::PollEvents() {
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				WindowQueue.push(WindowEvent::CLOSE);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:{
				KeyEvent event;
				event.key = Key::UNKNOWN; // Default to unknown key
				
				// Map SDL keys to our custom key enum
				switch (sdlEvent.key.keysym.scancode) {
					case SDL_SCANCODE_A: event.key = Key::A; break;
					case SDL_SCANCODE_B: event.key = Key::B; break;
					case SDL_SCANCODE_C: event.key = Key::C; break;
					case SDL_SCANCODE_D: event.key = Key::D; break;
					case SDL_SCANCODE_E: event.key = Key::E; break;
					case SDL_SCANCODE_F: event.key = Key::F; break;
					case SDL_SCANCODE_G: event.key = Key::G; break;
					case SDL_SCANCODE_H: event.key = Key::H; break;
					case SDL_SCANCODE_I: event.key = Key::I; break;
					case SDL_SCANCODE_J: event.key = Key::J; break;
					case SDL_SCANCODE_K: event.key = Key::K; break;
					case SDL_SCANCODE_L: event.key = Key::L; break;
					case SDL_SCANCODE_M: event.key = Key::M; break;
					case SDL_SCANCODE_N: event.key = Key::N; break;
					case SDL_SCANCODE_O: event.key = Key::O; break;
					case SDL_SCANCODE_P: event.key = Key::P; break;
					case SDL_SCANCODE_Q: event.key = Key::Q; break;
					case SDL_SCANCODE_R: event.key = Key::R; break;
					case SDL_SCANCODE_S: event.key = Key::S; break;
					case SDL_SCANCODE_T: event.key = Key::T; break;
					case SDL_SCANCODE_U: event.key = Key::U; break;
					case SDL_SCANCODE_V: event.key = Key::V; break;
					case SDL_SCANCODE_W: event.key = Key::W; break;
					case SDL_SCANCODE_X: event.key = Key::X; break;
					case SDL_SCANCODE_Y: event.key = Key::Y; break;
					case SDL_SCANCODE_Z: event.key = Key::Z; break;
					case SDL_SCANCODE_1: event.key = Key::NUM_1; break;
					case SDL_SCANCODE_2: event.key = Key::NUM_2; break;
					case SDL_SCANCODE_3: event.key = Key::NUM_3; break;
					case SDL_SCANCODE_4: event.key = Key::NUM_4; break;
					case SDL_SCANCODE_5: event.key = Key::NUM_5; break;
					case SDL_SCANCODE_6: event.key = Key::NUM_6; break;
					case SDL_SCANCODE_7: event.key = Key::NUM_7; break;
					case SDL_SCANCODE_8: event.key = Key::NUM_8; break;
					case SDL_SCANCODE_9: event.key = Key::NUM_9; break;
					case SDL_SCANCODE_0: event.key = Key::NUM_0; break;
					case SDL_SCANCODE_RETURN: event.key = Key::ENTER; break;
					case SDL_SCANCODE_ESCAPE: event.key = Key::ESC; break;
					case SDL_SCANCODE_SPACE: event.key = Key::SPACE; break;
					case SDL_SCANCODE_LSHIFT: case SDL_SCANCODE_RSHIFT: event.key = Key::SHIFT; break;
					case SDL_SCANCODE_LCTRL: case SDL_SCANCODE_RCTRL: event.key = Key::CTRL; break;
					case SDL_SCANCODE_LALT: case SDL_SCANCODE_RALT: event.key = Key::ALT; break;
					default: event.key = Key::UNKNOWN; break;
				}
				
				// Queue the event only if it is a key event
				if (sdlEvent.type == SDL_KEYDOWN) {
					event.type = KeyEventType::KEYDOWN;
					KeyQueue.push(event);
				} else if (sdlEvent.type == SDL_KEYUP) {
					event.type = KeyEventType::KEYUP;
					KeyQueue.push(event);
				}
				}break;
			case SDL_WINDOWEVENT:{
				WindowEvent windowEvent = WindowEvent::UNKNOWN;
				switch (sdlEvent.window.event) {
					case SDL_WINDOWEVENT_SHOWN:
						windowEvent = WindowEvent::SHOWN;
						break;
					case SDL_WINDOWEVENT_HIDDEN:
						windowEvent = WindowEvent::HIDDEN;
						break;
					case SDL_WINDOWEVENT_EXPOSED:
						windowEvent = WindowEvent::EXPOSED;
						break;
					case SDL_WINDOWEVENT_MOVED:
						windowEvent = WindowEvent::MOVED;
						break;
					case SDL_WINDOWEVENT_RESIZED:
						windowEvent = WindowEvent::RESIZED;
						break;
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						windowEvent = WindowEvent::SIZE_CHANGED;
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						windowEvent = WindowEvent::MINIMIZED;
						break;
					case SDL_WINDOWEVENT_MAXIMIZED:
						windowEvent = WindowEvent::MAXIMIZED;
						break;
					case SDL_WINDOWEVENT_RESTORED:
						windowEvent = WindowEvent::RESTORED;
						break;
					case SDL_WINDOWEVENT_ENTER:
						windowEvent = WindowEvent::ENTER;
						break;
					case SDL_WINDOWEVENT_LEAVE:
						windowEvent = WindowEvent::LEAVE;
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						windowEvent = WindowEvent::FOCUS_GAINED;
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						windowEvent = WindowEvent::FOCUS_LOST;
						break;
					case SDL_WINDOWEVENT_CLOSE:
						windowEvent = WindowEvent::CLOSE;
						break;
				}
				WindowQueue.push(windowEvent);
				}break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP: {
				MouseButton button = MouseButton::UNKNOWN;
				if (sdlEvent.button.button == SDL_BUTTON_LEFT) button = MouseButton::LEFT;
				if (sdlEvent.button.button == SDL_BUTTON_RIGHT) button = MouseButton::RIGHT;
				if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) button = MouseButton::MIDDLE;
				MouseEvent mouseEvent = {
					sdlEvent.type == SDL_MOUSEBUTTONDOWN ? MouseEventType::MOUSEBUTTONDOWN : MouseEventType::MOUSEBUTTONUP,
					button,
					{ 0, 0 },  // No motion in button events
					0
				};
				MouseQueue.push(mouseEvent);
				break;
			}
				
			case SDL_MOUSEMOTION: {
				MouseQueue.push({
					MouseEventType::MOUSEMOTION,
					MouseButton::UNKNOWN,
					{ sdlEvent.motion.xrel, sdlEvent.motion.yrel },
					0
				});
				break;
			}
				
			case SDL_MOUSEWHEEL:
				// Handle mouse wheel scroll
				MouseQueue.push({
					MouseEventType::MOUSEWHEEL,
					MouseButton::UNKNOWN,
					{ 0, 0 },
					sdlEvent.wheel.y  // Scroll amount
				});
				break;
			default:
				break;
		}
	}
}

// Set the window title
void WindowInput::SetTitle(const std::string& title) {
	SDL_SetWindowTitle(window, title.c_str());
}

WindowInput::KeyEvent WindowInput::getKey(){
	if(!KeyQueue.empty()){
		auto v = KeyQueue.front();
		KeyQueue.pop();
		return v;
	}else{
		return {KeyEventType::NONE, Key::NONE};
	}
}
bool WindowInput::isThereKey(){
	return !KeyQueue.empty();
}
void WindowInput::ClearKeys(){
	while (!KeyQueue.empty()) {
		KeyQueue.pop();
	}
}

WindowEvent WindowInput::getWindowEvent(){
	if(!WindowQueue.empty()){
		auto v = WindowQueue.front();
		WindowQueue.pop();
		return v;
	}else{
		return WindowEvent::NONE;
	}
}
bool WindowInput::isThereWindowEvent(){
	return !WindowQueue.empty();
}
void WindowInput::ClearWindowEvents(){
	while (!WindowQueue.empty()) {
		WindowQueue.pop();
	}
}
glm::ivec2 WindowInput::getWindowSize(){
	int w,h;
	SDL_GetWindowSize(window,&w,&h);
	return glm::ivec2(w,h);
}

WindowInput::MouseEvent WindowInput::getMouseEvent() {
	if (!MouseQueue.empty()) {
		MouseEvent e = MouseQueue.front();
		MouseQueue.pop();
		return e;
	}
	return { MouseEventType::NONE, MouseButton::UNKNOWN, {0, 0}, 0 };  // Default empty event
}
bool WindowInput::isThereMouseEvent() {
	return !MouseQueue.empty();
}
void WindowInput::ClearMouseEvents() {
	while (!MouseQueue.empty()) {
		MouseQueue.pop();
	}
}
glm::ivec2 WindowInput::getMousePosision(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	return glm::ivec2{x, y};
}










