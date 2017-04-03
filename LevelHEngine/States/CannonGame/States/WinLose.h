#pragma once

#include <memory>
#include "../../State.h"
#include "../../StateManager.h"
#include "../../../ResourceManagement/Text.h"

/**
@brief A State that contains and runs the Demo.
*/
class WinLose : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	WinLose(StateManager* stateManager, SDL_Window* window, bool inGameStart, int score);

	/**
	@brief Destructs the State object.
	*/
	~WinLose();

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
	///The Win Lose image
	std::string winLoseID;
	///A boolean for if this is at the game start
	bool gameStart;
	///A pointer for the score text
	Text* scoreText;
};