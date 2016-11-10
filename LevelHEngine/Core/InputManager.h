#pragma once

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "../Maths/Vec2.h"
#include "InputManagerDefs.h"

namespace Core
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void pollInputEvent(SDL_Event& incomingEvent);
		bool isKeyPressed(SDL_Keycode key);
		bool isKeyReleased(SDL_Keycode key);
		bool isMouseButtonPressed(uint8_t button);
		bool isMouseButtonReleased(uint8_t button);
		Maths::Vec2 getMousePos();

	private:
		enum state 
		{
			PRESSED,
			RELEASED,
			NONE
		};

		Maths::Vec2 mousePos;
		std::unordered_map<SDL_Keycode, state> keys;
		std::unordered_map<uint8_t, state> mouseButtons;

		void pollKeyEvent(SDL_Event& incomingEvent);
		void pollMouseEvent(SDL_Event& incomingEvent);		
	};

}//End of core namespace