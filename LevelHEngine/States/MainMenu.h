#pragma once

#include "State.h"
#include "StateManager.h"
#include "../UI/UIManager.h"

/**
@brief A State that contains and runs the Main Menu.
*/
class MainMenu : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	MainMenu(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~MainMenu();

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
	///The menu sprite
	std::string menuSprite;
	///The menu buttons
	std::string menuButtons[4];
	///A boolean for the inital loop
	bool initialLoop;
	///The total running time
	float totalTime;
	///The background music ID
	std::string backgroundMusicID;
};