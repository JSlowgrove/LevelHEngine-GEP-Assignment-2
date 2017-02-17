#pragma once

#include <SDL.h>
#include "State.h"
#include "StateManager.h"
#include "../Core/Timer.h"


/**
@brief A State that contains and runs the splash screen.
*/
class Splash : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	Splash(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~Splash();

	/**
	@brief Handles the State input.
	@returns If false then quit the State.
	*/
	bool input();

	/**
	@brief A function to update the State.
	*/
	void update();

	/**
	@brief A function to draw the State to the screen.
	*/
	void draw();

private:
	///The timer keeping the splash screen open
	Timer* splashTimer;
};
