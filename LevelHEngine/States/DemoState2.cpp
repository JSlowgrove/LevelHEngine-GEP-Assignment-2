#include "DemoState2.h"

#include "MainMenu.h"
#include "../Core/GameObject.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

DemoState2::DemoState2(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState2")
{
	//Create the game objects

	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;
	
	//Awake the game objects

	camera->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 2.0f, -12.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(-15.0f), 0.0f, 0.0f));
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
	}
	return true;
}

void DemoState2::update(float dt)
{
}

void DemoState2::draw()
{
}