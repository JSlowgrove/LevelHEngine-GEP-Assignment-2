#include "DemoState4.h"

#include <SDL.h>
#include "../MainMenu.h"
#include "../../Core/GameObject.h"
#include "../../Core/InputManager.h"
#include "../../Core/Application.h"
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


DemoState4::DemoState4(StateManager* stateManager, SDL_Window* window)
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

	auto sphere = GameObject::create("sphere").lock();
	sphere->addComponent<TransformComponent>();
	sphere->addComponent<ModelComponent>();
	sphere->addComponent<BoundingSphereComponent>();

	auto floor = GameObject::create("floor").lock();
	floor->addComponent<TransformComponent>();
	floor->addComponent<ModelComponent>();
	floor->addComponent<BoundingBoxComponent>();

	//Awake the game objects

	camera->awake();
	sphere->awake();
	floor->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));

	sphere->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	sphere->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, 4.0f, 6.0f));
	sphere->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "cyan");
	sphere->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		sphere->getComponent<ModelComponent>().lock()->getMeshID()
	);
	sphere->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
		sphere->getComponent<TransformComponent>().lock()->getScale()
	);

	floor->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 0.1f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	floor->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	floor->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "green");
	floor->getComponent<BoundingBoxComponent>().lock()->initaliseBoundingBox(
		floor->getComponent<ModelComponent>().lock()->getMeshID()
	);
	floor->getComponent<BoundingBoxComponent>().lock()->scaleBoundingBox(
		floor->getComponent<TransformComponent>().lock()->getScale()
	);

	//initalise bool
	initialLoop = true;

	//initalise velocity
	sphereVel = Vec3(0.0f, 0.0f, 0.0f);

	jump = true;
	landed = false;

	//start the music
	//ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

DemoState4::~DemoState4()
{
	if (!destroyed)
	{
		destroyState();
	}
}

bool DemoState4::input()
{
	//Check for user input
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		//apply gravity
		sphereVel.y += -9.81f;
		if (sphereVel.y < -9.81f)
		{
			sphereVel.y = -9.81;
		}

		InputManager::pollInputEvent(incomingEvent);
		if (incomingEvent.type == SDL_QUIT)
		{
			//If player closes the window, end the game loop
			return false;
		}

		//handle sphere
		if (InputManager::isKeyPressed(W_KEY))
		{
			sphereVel.z += -moveVel;
		}
		if (InputManager::isKeyPressed(A_KEY))
		{
			sphereVel.x += -moveVel;
		}
		if (InputManager::isKeyPressed(S_KEY))
		{
			sphereVel.z += moveVel;
		}
		if (InputManager::isKeyPressed(D_KEY))
		{
			sphereVel.x += moveVel;
		}

		if (InputManager::isKeyPressed(D_KEY))
		{
			sphereVel.x += moveVel;
		}

		//handle both
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			if (landed)
			{
				jump = true;
				landed = false;
				sphereVel.y += 100.0f;
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

void DemoState4::update()
{
	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	//Store the next position of the objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "sphere")
		{
			Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->setNextPos(
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->getPos()
				+ (sphereVel * Application::getDT()));
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
						//Logging::logI("Sphere-Box Collision");

						//stop the y velocity
						if (Application::getGameObjects()[i]->getName() == "sphere" && collisonSide.y == -1.0f)
						{
							sphereVel.y = 0.0f;
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
		if (Application::getGameObjects()[i]->getName() == "sphere")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(sphereVel * Application::getDT());
		}
	}

	//Keep the music playing
	//ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());


	if (landed)
	{
		jump = false;
		sphereVel.y = 0.0f;
	}
}

void DemoState4::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}