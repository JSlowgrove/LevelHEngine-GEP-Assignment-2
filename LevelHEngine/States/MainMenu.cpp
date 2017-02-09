#include "MainMenu.h"

#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"
#include "DemoState1.h"
#include "DemoState2.h"
#include "DemoState3.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu")
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	//create game objects
	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;

	auto loading = GameObject::create("loading").lock();
	loading->addComponent<TransformComponent>();
	loading->addComponent<ModelComponent>();

	//awake the game objects
	camera->awake();
	loading->awake();

	//initalise the game objects
	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 02.0f, -10.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));

	loading->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -2.0f, 0.0f));
	loading->getComponent<TransformComponent>().lock()->setScale(Vec3(11.2f, 1.0f, 6.3f));
	loading->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(90.0f), 0.0f, 0.0f));
	loading->getComponent<ModelComponent>().lock()->initaliseMesh("flatPlane", "loading.png");
	loading->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "textureInv");

	//draw the first frame
	draw();
}

MainMenu::~MainMenu()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "loading")
		{
			//destroy the state
			Application::getGameObjects()[i]->destroy();
			//remove it from the list if game objects
			Application::getGameObjects().erase(Application::getGameObjects().begin() + i);
		}
	}
}

bool MainMenu::input()
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

void MainMenu::update(float dt)
{
	//swtich to demo state
	//stateManager->changeState(new DemoState1(stateManager, window));
	//stateManager->changeState(new DemoState2(stateManager, window));
	stateManager->changeState(new DemoState3(stateManager, window));
	return;
}

void MainMenu::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}