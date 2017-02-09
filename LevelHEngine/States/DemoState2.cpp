#include "DemoState2.h"

#include "MainMenu.h"
#include "../Core/GameObject.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/CameraComponent.h"
#include "../Components/CameraControlComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ModelComponent.h"


DemoState2::DemoState2(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState2")
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.1f, 0.1f, 0.2f));

	//Create the game objects

	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	camera->addComponent<CameraControlComponent>();
	Application::camera = camera;

	auto heightmap = GameObject::create("heightmap").lock();
	heightmap->addComponent<TransformComponent>();
	heightmap->addComponent<ModelComponent>();
	
	//Awake the game objects

	camera->awake();
	heightmap->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));

	heightmap->getComponent<TransformComponent>().lock()->setScale(Vec3(1.0f, 1.0f, 1.0f));
	heightmap->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));
	heightmap->getComponent<TransformComponent>().lock()->setRotation(Vec3(0.0f, 0.0f, Convert::convertDegreeToRadian(90.0f)));
 	heightmap->getComponent<ModelComponent>().lock()->initaliseHeightmap("Assets/img/map.bmp", "terrain.jpg");
 	heightmap->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	//initalise bool
	initialLoop = true;
}

DemoState2::~DemoState2()
{
}

bool DemoState2::input()
{
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

		if (InputManager::isKeyPressed(ESC_KEY))
		{
			//If Escape is pressed, end the game loop
			return false;
		}

		//Handle the camera input
		Application::camera->getComponent<CameraControlComponent>().lock()->handleInput(incomingEvent);
	}
	return true;
}

void DemoState2::update(float dt)
{
	//hack for initial loop
	if (initialLoop)
	{
		dt = 0.0f;
		initialLoop = false;
	}

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(dt);

	//loops through the game objects
// 	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
// 	{
// 		if (Application::getGameObjects()[i]->getName() == "heightmap")
// 		{
// 			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
// 				Vec3(0.0f, Convert::convertDegreeToRadian(100.0f * dt), 0.0f)
// 			);
// 		}
// 	}
}

void DemoState2::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}