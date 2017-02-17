#pragma once

#include "../State.h"
#include "../StateManager.h"

/**
@brief A State that contains and runs the Demo.
*/
class DemoState2 : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	DemoState2(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~DemoState2();

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
	///The background music id.
	std::string backgroundMusicID;
	///Initital loop bool
	bool initialLoop;
};