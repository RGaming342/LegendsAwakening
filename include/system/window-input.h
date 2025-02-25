#pragma once

#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "glm/vec2.hpp"
#include "glad.h"
#include <cstdint>

enum class WindowEvent {
	UNKNOWN = -1,
	NONE,
	SHOWN,
	HIDDEN,
	EXPOSED,
	MOVED,
	RESIZED,
	SIZE_CHANGED,
	MINIMIZED,
	MAXIMIZED,
	RESTORED,
	ENTER,
	LEAVE,
	FOCUS_GAINED,
	FOCUS_LOST,
	CLOSE,
};
enum class Key {
	UNKNOWN = -1,    // Special case: Invalid or no key
	NONE = 0,
	A,  B,  C,  D,  E,  F,
	G,  H,  I,  J,  K,  L,
	M,  N,  O,  P,  Q,  R,
	S,  T,  U,  V,  W,  X,
	Y,  Z,
	NUM_1, NUM_2, NUM_3,
	NUM_4, NUM_5, NUM_6,
	NUM_7, NUM_8, NUM_9,
	NUM_0,
	ENTER, ESC,
	SPACE,
	SHIFT, CTRL, ALT,
};
enum class MouseEventType {
	NONE,
	MOUSEBUTTONDOWN, MOUSEBUTTONUP,
	MOUSEMOTION, MOUSEWHEEL
};
enum class MouseButton {
	UNKNOWN = -1,
	LEFT,
	RIGHT,
	MIDDLE,
};
enum class KeyEventType{ KEYDOWN, KEYUP, NONE };

class WindowInput {
	public:
		struct KeyEvent{ KeyEventType type; Key key; };
		
		
		struct MouseEvent {
			MouseEventType type;
			MouseButton button;
			glm::ivec2 motion;
			int wheel;  // Positive for scroll up, negative for scroll down
		};
		
		WindowInput(const std::string& title, int width, int height);
		~WindowInput();
		void clear(uint32_t color=0);
		void display();
		
		void PollEvents();
		void SetTitle(const std::string& title);
		
		KeyEvent getKey();
		bool isThereKey();
		void ClearKeys();
		
		WindowEvent getWindowEvent();
		bool isThereWindowEvent();
		void ClearWindowEvents();
		glm::ivec2 getWindowSize();
		
		MouseEvent getMouseEvent();
		bool isThereMouseEvent();
		void ClearMouseEvents();
		glm::ivec2 getMousePosision();
		
	private:
		SDL_GLContext context;
		SDL_Window* window;
		SDL_Event sdlEvent;
		std::queue<KeyEvent> KeyQueue;
		std::queue<WindowEvent> WindowQueue;
		std::queue<MouseEvent> MouseQueue;
};
