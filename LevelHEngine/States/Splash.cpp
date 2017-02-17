#include "Splash.h"

#include "MainMenu.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"
#include "../Maths/Convert.h"

Splash::Splash(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "Splash"), splashTimer(new Timer(3.0f))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	//create game objects
	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;

	auto splash = GameObject::create("splash").lock();
	splash->addComponent<TransformComponent>();
	splash->addComponent<ModelComponent>();

	//awake the game objects
	camera->awake();
	splash->awake();

	//initalise the game objects
	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f,02.0f, -10.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));

	splash->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -2.0f, 0.0f));
	splash->getComponent<TransformComponent>().lock()->setScale(Vec3(11.2f, 1.0f, 6.3f));
	splash->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(90.0f), 0.0f, 0.0f));
	splash->getComponent<ModelComponent>().lock()->initaliseMesh("flatPlane", "splash.jpg");
	splash->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "textureInv");
}

Splash::~Splash()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "splash")
		{
			//destroy the state
			Application::getGameObjects()[i]->destroy();
			//remove it from the list if game objects
			Application::getGameObjects().erase(Application::getGameObjects().begin() + i);
		}
	}
}

bool Splash::input()
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

void Splash::update()
{
#if _DEBUG
	stateManager->changeState(new MainMenu(stateManager, window));
	return;
#else
	//Update the timer
	splashTimer->upadateTimer(dt);

	//exit the splash screen if the timer is up
	if (splashTimer->checkTimer())
	{
		stateManager->changeState(new MainMenu(stateManager, window));
		return;
	}
#endif
}

void Splash::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}