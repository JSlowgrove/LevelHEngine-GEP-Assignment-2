#include "CannonGame.h"

#include <SDL.h>
#include <stdlib.h>     
#include <time.h>       
#include "../MainMenu.h"
#include "../../Core/GameObject.h"
#include "../../Core/InputManager.h"
#include "../../Core/Application.h"
#include "../../Core/Logging.h"
#include "../../Components/CameraComponent.h"
#include "../../Components/CameraControlComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/ModelComponent.h"
#include "../../Maths/Vec3.h"
#include "../../ResourceManagement/ResourceManager.h"
#include "../../Maths/Convert.h"
#include "../../Components/BoundingSphereComponent.h"
#include "../../Components/BoundingBoxComponent.h"
#include "../../Physics/Collision.h"
#include "Components/CannonControllerComponent.h"
#include "Components/AimBallComponent.h"
#include "States/Help.h"
#include "States/WinLose.h"


CannonGame::CannonGame(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "CannonGame"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/Voltaic.ogg"))
{
	//initialize random seed:
	srand(time(NULL));

	//Initalise the speed
	moveSpeed = 10.0f;
	
	targetPoleOffset = Vec3(0.0f,-5.0f,0.0f);

	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	ballStartPos = Vec3(0.0f, 0.0f, 15.0f);
	ballScale = Vec3(0.25f, 0.25f, 0.25f);

	//Create the game objects

	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	camera->addComponent<CameraControlComponent>();
	Application::camera = camera;

	auto heightmap = GameObject::create("heightmap").lock();
	heightmap->addComponent<TransformComponent>();
	heightmap->addComponent<ModelComponent>();

	targetPole = GameObject::create("targetPole").lock();
	targetPole->addComponent<TransformComponent>();
	targetPole->addComponent<ModelComponent>();

	auto cannonPole = GameObject::create("cannonPole").lock();
	cannonPole->addComponent<TransformComponent>();
	cannonPole->addComponent<ModelComponent>();

	cannon = GameObject::create("cannon").lock();
	cannon->addComponent<CannonControllerComponent>();
	cannon->addComponent<TransformComponent>();

	cannonball = GameObject::create("cannonball").lock();
	cannonball->addComponent<TransformComponent>();
	cannonball->addComponent<ModelComponent>();
	cannonball->addComponent<BoundingSphereComponent>();

	auto tourus = GameObject::create("tourus").lock();
	tourus->addComponent<TransformComponent>();
	tourus->addComponent<ModelComponent>();

	for (unsigned int i = 0; i < 20; i++)
	{
		aimBalls[i] = GameObject::create("aimBall-" + std::to_string(i)).lock();
		aimBalls[i]->addComponent<TransformComponent>();
		aimBalls[i]->addComponent<ModelComponent>();
		aimBalls[i]->addComponent<AimBallComponent>();

		aimBalls[i]->awake();

		aimBalls[i]->getComponent<TransformComponent>().lock()->setScale(Vec3(0.1f, 0.1f, 0.1f));
		aimBalls[i]->getComponent<TransformComponent>().lock()->setPos(ballStartPos);
		aimBalls[i]->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
		aimBalls[i]->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "white");
		aimBalls[i]->getComponent<AimBallComponent>().lock()->setResetPos(ballStartPos);
	}	
	
	targetBox = GameObject::create("target").lock();
	targetBox->addComponent<TransformComponent>();
	targetBox->addComponent<ModelComponent>();
	targetBox->addComponent<BoundingBoxComponent>();

	//Awake the game objects

	camera->awake();
	cannon->awake();
	cannonball->awake();
	targetBox->awake();
	heightmap->awake();
	targetPole->awake();
	cannonPole->awake();
	tourus->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -24.0f));
	camera->getComponent<CameraControlComponent>().lock()->disableMoveXControl();
	camera->getComponent<CameraControlComponent>().lock()->disableMoveYControl();
	camera->getComponent<CameraControlComponent>().lock()->disableMoveZControl();
	camera->getComponent<CameraControlComponent>().lock()->disableRotateXControl();
	camera->getComponent<CameraControlComponent>().lock()->disableRotateZControl();

	heightmap->getComponent<TransformComponent>().lock()->setScale(Vec3(5.0f, 5.0f, 1.1f));
	heightmap->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -15.0f, -5.0f));
	heightmap->getComponent<TransformComponent>().lock()->setRotation(Vec3(Convert::convertDegreeToRadian(90.0f), 0.0f, Convert::convertDegreeToRadian(90.0f)));
	heightmap->getComponent<ModelComponent>().lock()->initaliseHeightmap("Assets/img/map2.png", "terrain2.png");
	heightmap->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	cannonball->getComponent<TransformComponent>().lock()->setScale(ballScale);
	cannonball->getComponent<TransformComponent>().lock()->setPos(ballStartPos);
	cannonball->getComponent<ModelComponent>().lock()->initaliseMesh("sphere", "cannonball.jpg");
	cannonball->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");
	cannonball->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		cannonball->getComponent<ModelComponent>().lock()->getMeshID()
	);
	cannonball->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
		cannonball->getComponent<TransformComponent>().lock()->getScale()
	);

	tourus->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 10.0f, -80.0f));
	tourus->getComponent<TransformComponent>().lock()->setScale(Vec3(1.5f, 1.5f, 1.5f));
	tourus->getComponent<ModelComponent>().lock()->initalisePrimitive(Primitives::TOURUS);
	tourus->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "white");

	Vec3 newTarget = getNewTargetPos();
	targetBox->getComponent<TransformComponent>().lock()->setPos(newTarget);
	targetBox->getComponent<TransformComponent>().lock()->setScale(Vec3(2.0f, 2.0f, 2.0f));
	targetBox->getComponent<ModelComponent>().lock()->initaliseMesh("cube", "target.jpg");
	targetBox->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");
	targetBox->getComponent<BoundingBoxComponent>().lock()->initaliseBoundingBox(
		targetBox->getComponent<ModelComponent>().lock()->getMeshID()
	);
	targetBox->getComponent<BoundingBoxComponent>().lock()->scaleBoundingBox(
		targetBox->getComponent<TransformComponent>().lock()->getScale()
	);

	targetPole->getComponent<TransformComponent>().lock()->setPos(newTarget + targetPoleOffset);
	targetPole->getComponent<TransformComponent>().lock()->setScale(Vec3(1.0f, 10.0f, 1.0f));
	targetPole->getComponent<ModelComponent>().lock()->initaliseMesh("cube", "sheetmetal.jpg");
	targetPole->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	cannonPole->getComponent<TransformComponent>().lock()->setPos(ballStartPos + Vec3(0.0f, -5.0f ,0.0f));
	cannonPole->getComponent<TransformComponent>().lock()->setScale(Vec3(0.1f, 10.0f, 0.1f));
	cannonPole->getComponent<ModelComponent>().lock()->initaliseMesh("cube", "sheetmetal.jpg");
	cannonPole->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	//initalise bool
	initialLoop = true;

	//initalise velocity
	cannonBallVel = Vec3(0.0f, 0.0f, 0.0f);

	//The cannonball booleans
	fire = false;

	aimTimer = new Timer(0.5f);
	currentLastAimBallIndex = 19;
	newAimBall = true;

	totalTime = 0.0f;

	gameUI = ResourceManager::initialiseSprite("Assets/img/CannonGameUI.png");
	gameHelp = ResourceManager::initialiseSprite("Assets/img/CannonGameHelpBox.png");

	scoreText = new Text("Score: 0", "Assets/font/isl_jupiter.ttf", 120, 255, 255, 255);
	timeText = new Text("Time Left: 60", "Assets/font/isl_jupiter.ttf", 120, 255, 255, 255);

	pointSound = ResourceManager::initialiseAudio("Assets/aud/powerUp1.ogg");
	explosionSound = ResourceManager::initialiseAudio("Assets/aud/explosion1.ogg");
	noBallSound = ResourceManager::initialiseAudio("Assets/aud/lowDown.ogg");

	score = 0;

	missTimer = new Timer(3.0f);

	gameTimer = new Timer(60.0f);

	timeLeft = 60.0f;

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}
//stateManager->removeLastState();
CannonGame::~CannonGame()
{
	delete aimTimer;
	delete missTimer;
	delete gameTimer;
	delete scoreText;
	delete timeText;
	if (!destroyed)
	{
		destroyState();
	}
}

bool CannonGame::input()
{
	InputManager::updateInputManager();

	//Check for user input
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		InputManager::pollInputEvent(incomingEvent);

		cannon->getComponent<CannonControllerComponent>().lock()->handleInput();

		if (incomingEvent.type == SDL_QUIT)
		{
			//If player closes the window, end the game loop
			return false;
		}

		//handle both
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			if (!fire)
			{
				fire = true;
				cannonBallVel = cannon->getComponent<CannonControllerComponent>().lock()->getCannonLaunchVelocities();
				ResourceManager::getAudio(explosionSound)->playEffect();
				missTimer->resetTimer();
			}
			else
			{
				ResourceManager::getAudio(noBallSound)->playEffect();
			}
		}

		if (InputManager::isKeyPressed(ESC_KEY))
		{
			//If Escape is pressed, return to main menu
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new MainMenu(stateManager, window));
			return true;
		}

		if (InputManager::isKeyReleased(H_KEY))
		{
			stateManager->addState(new Help(stateManager, window));
		}

		Application::camera->getComponent<CameraControlComponent>().lock()->handleInput();
	}

	Vec3 pos = Application::camera->getComponent<TransformComponent>().lock()->getPos();
	return true;
}

void CannonGame::update()
{
	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;

		//stwitch to start state
		stateManager->addState(new WinLose(stateManager, window, true, score));
	}

	timeLeft -= Application::getDT();

	gameTimer->upadateTimer(Application::getDT());
	if (gameTimer->checkTimer())
	{
		stateManager->addState(new WinLose(stateManager, window, false, score));

		cannonball->getComponent<TransformComponent>().lock()->setPos(ballStartPos);
		fire = false;
		cannonBallVel = Vec3(0.0f, 0.0f, 0.0f);
		gameTimer->resetTimer();
		score = 0;
		scoreText->setText("Score: " + std::to_string(score));
		timeLeft = 60.0f;
	}

	//apply gravity
	if (fire)
	{
		cannonBallVel.y += -1.0f;
		if (cannonBallVel.y < -9.81f)
		{
			cannonBallVel.y = -9.81;
		}
		missTimer->upadateTimer(Application::getDT());
		if (missTimer->checkTimer())
		{
			cannonball->getComponent<TransformComponent>().lock()->setPos(ballStartPos);
			fire = false;
			cannonBallVel = Vec3(0.0f, 0.0f, 0.0f);
		}
	}

	aimTimer->upadateTimer(Application::getDT());
	if (aimTimer->checkTimer())
	{
		newAimBall = true;
		aimTimer->resetTimer();
	}

	//Store the next position of the cannonball
	cannonball->getComponent<BoundingSphereComponent>().lock()->setNextPos(
		cannonball->getComponent<TransformComponent>().lock()->getPos()
		+ (cannonBallVel * Application::getDT()));


	//perform collision detection
	//check for collision
	if (Collision::sphereCubeIntersect(
		targetBox->getComponent<TransformComponent>().lock()->getPos(),
		targetBox->getComponent<BoundingBoxComponent>().lock()->getBoundingBoxDimensions(),
		cannonball->getComponent<BoundingSphereComponent>().lock()->getNextPos(),
		cannonball->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
		Vec3(0.0f, 0.0f, 0.0f)
	))
	{
		Logging::logI("Sphere-Box Collision");
		Vec3 newTarget = getNewTargetPos();
		targetBox->getComponent<TransformComponent>().lock()->setPos(newTarget);
		targetPole->getComponent<TransformComponent>().lock()->setPos(newTarget + targetPoleOffset);
		fire = false;
		cannonball->getComponent<TransformComponent>().lock()->setPos(ballStartPos);
		cannonBallVel = Vec3(0.0f, 0.0f, 0.0f);
		score++;
		scoreText->setText("Score: " + std::to_string(score));
		ResourceManager::getAudio(pointSound)->playEffect();
	}

	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//update positions with new velocities
		if (Application::getGameObjects()[i]->getName() == "cannonball")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(cannonBallVel * Application::getDT());
		}
		//check to see if a aim ball
		std::size_t found = Application::getGameObjects()[i]->getName().find("aimBall");
		if (found != std::string::npos)
		{
			//apply gravity and update
			Application::getGameObjects()[i]->getComponent<AimBallComponent>().lock()->applyGravity();
			Application::getGameObjects()[i]->getComponent<AimBallComponent>().lock()->update();
		}

		if (Application::getGameObjects()[i]->getName() == "cannontourus")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(Convert::convertDegreeToRadian(100.0f * Application::getDT()),
					Convert::convertDegreeToRadian(100.0f * Application::getDT()), 0.0f)
			);
		}

		if (Application::getGameObjects()[i]->getName() == "tourus")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(Convert::convertDegreeToRadian(100.0f * Application::getDT()),
					Convert::convertDegreeToRadian(100.0f * Application::getDT()), 0.0f)
			);
		}
	}

	if (newAimBall)
	{
		newAimBall = false;
		aimBalls[currentLastAimBallIndex]->getComponent<AimBallComponent>().lock()->resetBall();
		aimBalls[currentLastAimBallIndex]->getComponent<AimBallComponent>().lock()->setVelocities(cannon->getComponent<CannonControllerComponent>().lock()->getCannonLaunchVelocities());
		aimBalls[currentLastAimBallIndex]->getComponent<AimBallComponent>().lock()->setUse(true);
		if (currentLastAimBallIndex != 0)
		{
			currentLastAimBallIndex--;
		}
		else
		{
			currentLastAimBallIndex = 19;
		}
	}

	timeText->setText("Time Left: " + std::to_string(int(timeLeft)));

	//Update the cannon position
	cannon->getComponent<CannonControllerComponent>().lock()->update();

	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());
}

void CannonGame::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
	scoreText->pushToScreen(Vec2(20.0f, 600.0f));
	timeText->pushToScreen(Vec2(710.0f, 600.0f));
	ResourceManager::getSprite(gameUI)->pushToScreen(Vec2(0.0f, 0.0f));
	ResourceManager::getSprite(gameHelp)->pushToScreen(Vec2(0.0f, 0.0f));
}

Vec3 CannonGame::getNewTargetPos()
{
	float x = ((rand() % 500) - 250) * 0.1f;
	float y = 0.0f;
	float z = ((rand() % 150) + 100) * 0.1f;
	return Vec3(x, y, -z);
}
