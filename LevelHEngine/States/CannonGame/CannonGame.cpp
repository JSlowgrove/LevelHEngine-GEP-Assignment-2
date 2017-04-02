#include "CannonGame.h"

#include <SDL.h>
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


CannonGame::CannonGame(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState4"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/ShowYourMoves.ogg"))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	//Create the game objects

	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	camera->addComponent<CameraControlComponent>();
	Application::camera = camera;

	auto cannonball = GameObject::create("cannonball").lock();
	cannonball->addComponent<TransformComponent>();
	cannonball->addComponent<ModelComponent>();
	cannonball->addComponent<BoundingSphereComponent>();

	auto targetBox = GameObject::create("box").lock();
	targetBox->addComponent<TransformComponent>();
	targetBox->addComponent<ModelComponent>();
	targetBox->addComponent<BoundingBoxComponent>();

	//Awake the game objects

	camera->awake();
	cannonball->awake();
	targetBox->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));

	cannonball->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	cannonball->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, 4.0f, 6.0f));
	cannonball->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	cannonball->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "cyan");
	cannonball->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		cannonball->getComponent<ModelComponent>().lock()->getMeshID()
	);
	cannonball->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
		cannonball->getComponent<TransformComponent>().lock()->getScale()
	);

	targetBox->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 5.0f));
	targetBox->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 2.0f, 5.0f));
	targetBox->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	targetBox->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "green");
	targetBox->getComponent<BoundingBoxComponent>().lock()->initaliseBoundingBox(
		targetBox->getComponent<ModelComponent>().lock()->getMeshID()
	);
	targetBox->getComponent<BoundingBoxComponent>().lock()->scaleBoundingBox(
		targetBox->getComponent<TransformComponent>().lock()->getScale()
	);

	//initalise bool
	initialLoop = true;

	//initalise velocity
	cannonBallVel = Vec3(0.0f, 0.0f, 0.0f);
	cannonPower = 50.0f;
	cannonAngle = Vec3(0.0f, Convert::convertDegreeToRadian(50.0f), -Convert::convertDegreeToRadian(50.0f));

	//initalise the cannon rotation
	cannonRot = Vec3(0.0f, 0.0f, 0.0f);

	//The cannonball booleans
	fire = false;
	landed = true;

	float A = Convert::convertDegreeToRadian(50.0f);

	cannonLaunchVel = Vec3(0.0f, sin(cannonAngle.y) * cannonPower, cos(cannonAngle.z) * -cannonPower);

	//start the music
	//ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

CannonGame::~CannonGame()
{
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
		if (incomingEvent.type == SDL_QUIT)
		{
			//If player closes the window, end the game loop
			return false;
		}

		//handle box
		if (InputManager::isKeyPressed(LEFT_KEY))
		{
			cannonRot.z -= rotVel;
		}
		if (InputManager::isKeyReleased(LEFT_KEY))
		{
			cannonRot.z = 0.0f;
		}
		if (InputManager::isKeyPressed(RIGHT_KEY))
		{
			cannonRot.z += rotVel;
		}
		if (InputManager::isKeyReleased(RIGHT_KEY))
		{
			cannonRot.z = 0.0f;
		}

		//tmp
		if (InputManager::isKeyReleased(L_KEY))
		{
			landed = true;
		}

		//handle both
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			if (landed)
			{
				fire = true;
				landed = false;
				cannonBallVel = cannonLaunchVel;
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
	}
	return true;
}

void CannonGame::update()
{
	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	//apply gravity
	if (fire)
	{
		cannonBallVel.y += -1.0f;
		if (cannonBallVel.y < -9.81f)
		{
			cannonBallVel.y = -9.81;
		}
	}

	//Store the next position of the objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "cannonball")
		{
			Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->setNextPos(
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->getPos()
				+ (cannonBallVel * Application::getDT()));
		}
	}

	//perform collision detection
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->checkForComponent("boundingSphere"))
		{
			//loop through all others with bounding spheres
			for (unsigned int j = 0; j < Application::getGameObjects().size(); j++)
			{
				//sphere box collision check
				if (Application::getGameObjects()[j]->checkForComponent("boundingBox"))
				{
					Vec3 collisonSide = Vec3(0.0f, 0.0f, 0.0f);
					//check for collision
					if (Collision::sphereCubeIntersect(
						Application::getGameObjects()[j]->getComponent<TransformComponent>().lock()->getPos(),
						Application::getGameObjects()[j]->getComponent<BoundingBoxComponent>().lock()->getBoundingBoxDimensions(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getNextPos(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
						collisonSide
					))
					{
						Logging::logI("Sphere-Box Collision");

						//stop the y velocity
						if (Application::getGameObjects()[i]->getName() == "cannonball")
						{
							cannonBallVel.y = 0.0f;
							landed = true;
						}
					}
				}
			}
		}
	}

	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//update positions with new velocities
		if (Application::getGameObjects()[i]->getName() == "cannonball")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(cannonBallVel * Application::getDT());
		}
		//update box rotation
		if (Application::getGameObjects()[i]->getName() == "box")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(cannonRot * Application::getDT());
		}
	}

	//Keep the music playing
	//ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());


	if (landed)
	{
		fire = false;
		cannonBallVel = Vec3(0.0f,0.0f,0.0f);
	}
}

void CannonGame::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}