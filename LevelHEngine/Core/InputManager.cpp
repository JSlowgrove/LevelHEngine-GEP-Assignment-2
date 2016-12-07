#include "InputManager.h"

Vec2 InputManager::mousePos = Vec2(0.0f, 0.0f);

//initialise the keys
std::unordered_map<SDL_Keycode, InputManager::state> InputManager::keys =
{
	{ SDLK_a, NONE },{ SDLK_b, NONE },{ SDLK_c, NONE },{ SDLK_d, NONE },{ SDLK_e, NONE },{ SDLK_f, NONE },{ SDLK_g, NONE },
	{ SDLK_h, NONE },{ SDLK_i, NONE },{ SDLK_j, NONE },{ SDLK_k, NONE },{ SDLK_l, NONE },{ SDLK_o, NONE },{ SDLK_m, NONE },
	{ SDLK_n, NONE },{ SDLK_p, NONE },{ SDLK_q, NONE },{ SDLK_r, NONE },{ SDLK_s, NONE },{ SDLK_t, NONE },{ SDLK_u, NONE },
	{ SDLK_v, NONE },{ SDLK_w, NONE },{ SDLK_y, NONE },{ SDLK_x, NONE },{ SDLK_z, NONE },{ SDLK_ESCAPE, NONE },{ SDLK_SPACE, NONE },
	{ SDLK_F1, NONE },{ SDLK_F2, NONE },{ SDLK_F3, NONE },{ SDLK_F4, NONE },{ SDLK_F5, NONE },{ SDLK_F6, NONE },{ SDLK_F7, NONE },
	{ SDLK_F8, NONE },{ SDLK_F9, NONE },{ SDLK_F10, NONE },{ SDLK_F11, NONE },{ SDLK_F12, NONE },{ SDLK_1, NONE },{ SDLK_2, NONE },
	{ SDLK_3, NONE },{ SDLK_4, NONE },{ SDLK_5, NONE },{ SDLK_6, NONE },{ SDLK_7, NONE },{ SDLK_8, NONE },{ SDLK_9, NONE },
	{ SDLK_0, NONE },{ SDLK_COLON, NONE },{ SDLK_SEMICOLON, NONE },{ SDLK_LESS, NONE },{ SDLK_EQUALS, NONE },{ SDLK_GREATER, NONE },
	{ SDLK_QUESTION, NONE },{ SDLK_AT, NONE },{ SDLK_LEFTBRACKET, NONE },{ SDLK_BACKSLASH, NONE },{ SDLK_RIGHTBRACKET, NONE },
	{ SDLK_CARET, NONE },{ SDLK_UNDERSCORE, NONE },{ SDLK_BACKQUOTE, NONE },{ SDLK_PAUSE, NONE },{ SDLK_INSERT, NONE },
	{ SDLK_HOME, NONE },{ SDLK_PAGEUP, NONE },{ SDLK_DELETE, NONE },{ SDLK_END, NONE },{ SDLK_PAGEDOWN, NONE },{ SDLK_RIGHT, NONE },
	{ SDLK_LEFT, NONE },{ SDLK_DOWN, NONE },{ SDLK_UP, NONE },{ SDLK_KP_DIVIDE, NONE },{ SDLK_KP_MULTIPLY, NONE },
	{ SDLK_KP_MINUS, NONE },{ SDLK_KP_PLUS, NONE },{ SDLK_KP_ENTER, NONE },{ SDLK_KP_1, NONE },{ SDLK_KP_2, NONE },
	{ SDLK_KP_3, NONE },{ SDLK_KP_4, NONE },{ SDLK_KP_5, NONE },{ SDLK_KP_6, NONE },{ SDLK_KP_7, NONE },{ SDLK_KP_8, NONE },
	{ SDLK_KP_9, NONE },{ SDLK_KP_0, NONE },{ SDLK_KP_PERIOD, NONE },{ SDLK_KP_EQUALS, NONE },{ SDLK_LCTRL, NONE },
	{ SDLK_LSHIFT, NONE },{ SDLK_LALT, NONE },{ SDLK_RCTRL, NONE },{ SDLK_RSHIFT, NONE },{ SDLK_RALT, NONE },{ SDLK_RETURN, NONE },
	{ SDLK_BACKSPACE, NONE },{ SDLK_TAB, NONE },{ SDLK_EXCLAIM, NONE },{ SDLK_QUOTEDBL, NONE },{ SDLK_HASH, NONE },
	{ SDLK_PERCENT, NONE },{ SDLK_DOLLAR, NONE },{ SDLK_AMPERSAND, NONE },{ SDLK_QUOTE, NONE },{ SDLK_LEFTPAREN, NONE },
	{ SDLK_RIGHTPAREN, NONE },{ SDLK_ASTERISK, NONE },{ SDLK_PLUS, NONE },{ SDLK_COMMA, NONE },{ SDLK_MINUS, NONE },
	{ SDLK_PERIOD, NONE },{ SDLK_SLASH, NONE }
};

//initialise the mouse buttons
std::unordered_map<uint8_t, InputManager::state> InputManager::mouseButtons =
{
	{ SDL_BUTTON_LEFT, NONE },{ SDL_BUTTON_RIGHT, NONE }
};

void InputManager::pollInputEvent(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		pollKeyEvent(incomingEvent);
		break;

	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		pollMouseEvent(incomingEvent);
		break;
	}
}

void InputManager::pollKeyEvent(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:
		keys[incomingEvent.key.keysym.sym] = PRESSED;
		break;

	case SDL_KEYUP:
		keys[incomingEvent.key.keysym.sym] = RELEASED;
		break;
	}
}

void InputManager::pollMouseEvent(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_MOUSEMOTION:
		mousePos.x = ((float)incomingEvent.motion.x);
		mousePos.y = ((float)incomingEvent.motion.y);
		break;

	case SDL_MOUSEBUTTONDOWN:
		mouseButtons[incomingEvent.button.button] = PRESSED;
		break;

	case SDL_MOUSEBUTTONUP:
		mouseButtons[incomingEvent.button.button] = RELEASED;
		break;
	}
}

bool InputManager::isKeyPressed(SDL_Keycode key)
{
	if (keys[key] == PRESSED)
	{
		return true;
	}
	return false;
}

bool InputManager::isKeyReleased(SDL_Keycode key)
{
	if (keys[key] == RELEASED)
	{
		return true;
	}
	return false;
}

bool InputManager::isMouseButtonPressed(uint8_t button)
{
	if (mouseButtons[button] == PRESSED)
	{
		return true;
	}
	return false;
}

bool InputManager::isMouseButtonReleased(uint8_t button)
{
	if (mouseButtons[button] == RELEASED)
	{
		return true;
	}
	return false;
}

Vec2 InputManager::getMousePos()
{
	return mousePos;
}