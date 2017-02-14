#pragma once
#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Vec3.h"

#define moveVel 10.0f;

/**
@brief A State that contains and runs the Demo.
*/
class DemoState1 : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	DemoState1(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~DemoState1();

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
	///The mouse press sound id.
	std::string mousePressSoundID;
	///The sphere velocities
	Vec3 s1V, s2V;
	///Other bools
	bool initialLoop, jump, resetPos;
};