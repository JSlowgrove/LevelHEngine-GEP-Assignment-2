#pragma once

#include <SDL.h>
#include <string.h>
#include "../Maths/M_Vec2.h"

///Forward declaration of StateManager for the pointer to the StateManager.
class S_StateManager;

/**
@brief Contains State functions and data to be inherited by all other states.
@author Jamie Slowgrove
*/
class S_State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param dimensions The screen dimensions.
	*/
	S_State(S_StateManager* stateManager, SDL_Renderer* renderer, M_Vec2 dimensions);

	/**
	Constructs a State object with a window.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	@param dimensions The screen dimensions.
	*/
	S_State(S_StateManager* stateManager, SDL_Window* window, M_Vec2 dimensions);

	/**
	@brief A virtual destructor for the State object.
	*/
	virtual ~S_State();

	/**
	@brief A pure virtual function to handle the user input for use with the State.
	@returns If false then quit State.
	*/
	virtual bool input() = 0;

	/**
	@brief A pure virtual function to update the State to allow the State to run.
	@param dt The delta time.
	*/
	virtual void update(float deltaTime) = 0;

	/**
	@brief A pure virtual function to draw to the screen using the renderer.
	*/
	virtual void draw() = 0;

	/**
	@brief A function to return the window.
	@returns A pointer to the window.
	*/
	SDL_Window* getWindow();

protected:
	///A pointer to the state manager.
	S_StateManager* stateManager;
	///A pointer to the renderer.
	SDL_Renderer* renderer;
	///The screen dimensions.
	M_Vec2 dimensions;
	///A window to display to
	SDL_Window* window;
};