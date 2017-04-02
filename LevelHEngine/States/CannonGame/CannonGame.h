#pragma once

#include "../State.h"
#include "../StateManager.h"
#include "../../Maths/Vec3.h"

#define moveVel 10.0f;
#define rotVel 5.0f;

/**
@brief A State that contains and runs the Demo.
*/
class CannonGame : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	CannonGame(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~CannonGame();

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
	///The sphere velocity
	Vec3 cannonBallVel;
	///The cannon velocity
	float cannonPower;
	///The cannon angle
	Vec3 cannonAngle;
	///The cannon velocity
	Vec3 cannonRot;
	///The cannon launch veclocity
	Vec3 cannonLaunchVel;

	bool fire, landed;
};