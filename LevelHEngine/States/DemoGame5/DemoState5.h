#pragma once

#include "../State.h"
#include "../StateManager.h"
#include "../../AI/Flocking.h"

/**
@brief A State that contains and runs the Demo.
*/
class DemoState5 : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	DemoState5(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~DemoState5();

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
	///The boid sprite id.
	std::string boidSpriteID;
	///The Flocking objects
	Flocking* flock;
	Flocking* flock3D;
	///Initital loop bool
	bool initialLoop;
	///A boolean for 3D
	bool use3D;
	///A boolean for if help should display
	bool help;
	///The UI textures
	std::string UIID;
	std::string helpID;
};