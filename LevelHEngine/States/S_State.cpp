#include "S_State.h"

S_State::S_State(S_StateManager * stateManager, SDL_Renderer* renderer, C_Vec2 dimensions)
	: stateManager(stateManager), renderer(renderer), dimensions(dimensions), window(nullptr)
{
}

S_State::S_State(S_StateManager * stateManager, SDL_Window* window, C_Vec2 dimensions)
	: stateManager(stateManager), window(window), dimensions(dimensions), renderer(nullptr)
{
}

S_State::~S_State()
{
}

SDL_Window* S_State::getWindow()
{
	return window;
}