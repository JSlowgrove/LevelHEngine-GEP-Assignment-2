#pragma once

#include <SDL.h>
#include <string.h>
#include "../Core/WindowFrame.h"

///Forward declaration of StateManager for the pointer to the StateManager
class StateManager;

/**
@brief Creates a State object to be inherited.
*/
class State
{
public:
	/**
	@brief Constructs a State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	@param name The name of the state.
	*/
	State(StateManager* stateManager, SDL_Window* window, std::string name);

	/**
	@brief A virtual destructor for the State object.
	*/
	virtual ~State();

	/**
	@brief A pure virtual function to handle the user input for use with the State.
	@returns If false then quit State.
	*/
	virtual bool input() = 0;

	/**
	@brief A pure virtual function to update the State to allow the State to run.
	*/
	virtual void update() = 0;

	/**
	@brief A pure virtual function to draw to the screen using the window.
	*/
	virtual void draw() = 0;

	/**
	@brief Gets the window
	@returns A pointer to the window
	*/
	SDL_Window* getWindow();

	/**
	@brief Gets the name of the state
	@returns The name of the state
	*/
	std::string getName();

protected:
	///A pointer to the state manager
	StateManager* stateManager;
	///The window to display to
	SDL_Window* window;
	///The state name
	std::string name;
};