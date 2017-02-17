#pragma once

#include <vector>
#include <unordered_map>
#include "../Maths/Vec2.h"
#include "InputManagerDefs.h"

/**
@brief Contains static variables and functions for use with input manager.
*/
class InputManager
{
public:

	/**
	@brief A static function to poll the input events.
	@param incomingEvent A reference to the SDL event.
	*/
	static void pollInputEvent(SDL_Event& incomingEvent);

	/**
	@brief A static function to check if a specific key is pressed.
	@param key The key code of the key to check.
	@returns If the key is pressed.
	*/
	static bool isKeyPressed(SDL_Keycode key);

	/**
	@brief A static function to check if a specific key is released.
	@param key The key code of the key to check.
	@returns If the key is released.
	*/
	static bool isKeyReleased(SDL_Keycode key);

	/**
	@brief A static function to check if a specific mouse button is pressed.
	@param key The mouse button to check.
	@returns If the mouse button is pressed.
	*/
	static bool isMouseButtonPressed(uint8_t button);

	/**
	@brief A static function to check if a specific mouse button is released.
	@param key The mouse button to check.
	@returns If the mouse button is released.
	*/
	static bool isMouseButtonReleased(uint8_t button);

	/**
	@brief A static function to get the mouse position.
	@returns The position of the mouse.
	*/
	static Vec2 getMousePos();

private:
		
	///An static enum for the state of the keys and buttons
	enum state
	{
		PRESSED,
		RELEASED,
		NONE
	};

	///The mouse position
	static Vec2 mousePos;
	///An unordered map of keys
	static std::unordered_map<SDL_Keycode, state> keys;
	///An unordered map of mouse buttons
	static std::unordered_map<uint8_t, state> mouseButtons;

	/**
	@brief A static function to poll the key input events.
	@param incomingEvent A reference to the SDL event.
	*/
	static void pollKeyEvent(SDL_Event& incomingEvent);

	/**
	@brief A function to poll the mouse input events.
	@param incomingEvent A reference to the SDL event.
	*/
	static void pollMouseEvent(SDL_Event& incomingEvent);
};