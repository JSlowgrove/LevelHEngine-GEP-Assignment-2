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
	float timeLeft;

	float totalTime;

	///A shared pointer to the cannon
	std::shared_ptr<GameObject> cannon;
	std::shared_ptr<GameObject> cannonball;
	std::shared_ptr<GameObject> targetBox;
	std::shared_ptr<GameObject> targetPole;

	std::shared_ptr<GameObject> aimBalls[20];

	Timer* aimTimer;
	Timer* gameTimer;
	Timer* missTimer;

	bool fire, newAimBall;

	Vec3 targetPoleOffset;

	Vec3 ballStartPos, ballScale;

	std::string pointSound;
	std::string noBallSound;
	std::string explosionSound;

	std::string gameUI;
	std::string gameHelp;

	int score;

	unsigned int currentLastAimBallIndex;

	Text* scoreText;
	Text* timeText;

	Vec3 getNewTargetPos();
};