#include "State.h"

State::State(StateManager * stateManager, SDL_Window* window, std::string name)
{
	//sets the pointer to the state manager
	this->stateManager = stateManager;
	//sets the pointer to the window
	this->window = window;
	//set the name
	this->name = name;
}

State::~State() 
{
}

SDL_Window* State::getWindow()
{
	//return the window
	return window;
}

std::string State::getName()
{
	//return the state name
	return name;
}