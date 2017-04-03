#pragma once

#include <memory>
#include "../State.h"
#include "../StateManager.h"
#include "../../Maths/Vec3.h"
#include "../../Core/GameObject.h"
#include "../../Core/Timer.h"
#include "../../ResourceManagement/Text.h"

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
	///The movement speed
	float moveSpeed;
	///The time left in the game
	float timeLeft;
	///The total time
	float totalTime;

	///A shared pointer to the cannon
	std::shared_ptr<GameObject> cannon;
	///A shared pointer to the cannonball
	std::shared_ptr<GameObject> cannonball;
	///A shared pointer to the target box
	std::shared_ptr<GameObject> targetBox;
	///A shared pointer to the target pole
	std::shared_ptr<GameObject> targetPole;
	///An array of shared pointers to the aiming balls
	std::shared_ptr<GameObject> aimBalls[20];

	///A timer for the aim balls spawning
	Timer* aimTimer;
	///A timer for the game
	Timer* gameTimer;
	///A timer for respawning the cannonball after a miss.
	Timer* missTimer;
	///A bool for if the cannonball is in the air
	bool fire;
	///A bool fo if a new ball should spawn
	bool newAimBall;
	///The position offset of the target pole and target box
	Vec3 targetPoleOffset;
	///The initali ball vectors
	Vec3 ballStartPos, ballScale;
	///The sound effects
	std::string pointSound;
	std::string noBallSound;
	std::string explosionSound;
	///The UI images
	std::string gameUI;
	std::string gameHelp;
	///The player score
	int score;
	///The index of the last aim ball
	unsigned int currentLastAimBallIndex;
	///The info text
	Text* scoreText;
	Text* timeText;
	
	/**
	@brief A function to generate a new postion for the target.
	*/
	Vec3 getNewTargetPos();
};