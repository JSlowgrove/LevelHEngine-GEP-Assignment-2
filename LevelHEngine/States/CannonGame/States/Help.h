#pragma once

#include <memory>
#include "../../State.h"
#include "../../StateManager.h"

/**
@brief A State that contains and runs the Demo.
*/
class Help : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	Help(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~Help();

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
	///The game help info
	std::string gameHelp;
};