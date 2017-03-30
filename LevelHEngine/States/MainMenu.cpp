#include "MainMenu.h"

#include <SDL.h>
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"
#include "../ResourceManagement/ResourceManager.h"
#include "DemoGame1/DemoState1.h"
#include "DemoGame2/DemoState2.h"
#include "DemoGame3/DemoState3.h"
#include "DemoGame4/DemoState4.h"
#include "../Core/Logging.h"
#include "../Maths/Convert.h"
#include "../Core/Screenshot.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu")
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	//loading sprites
	menuSprite = ResourceManager::initialiseSprite("Assets/img/mainmenu.png");

	//create game objects
	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;

	auto cube = GameObject::create("cube").lock();
	cube->addComponent<TransformComponent>();
	cube->addComponent<ModelComponent>();

	//awake the game objects
	camera->awake();
	cube->awake();

	cube->getComponent<TransformComponent>().lock()->setScale(Vec3(1.0f, 1.0f, 1.0f));
	cube->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -3.0f));
	cube->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	cube->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "default");

	totalTime = 0.0f;
	initialLoop = true;
}

MainMenu::~MainMenu()
{
	if (!destroyed)
	{
		destroyState();
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

		//tmp
		if (InputManager::isKeyPressed(ONE_KEY))
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState1(stateManager, window));
			return true;
		}
		if (InputManager::isKeyPressed(TWO_KEY))
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState2(stateManager, window));
			return true;
		}
		if (InputManager::isKeyPressed(THREE_KEY))
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState3(stateManager, window));
			return true;
		}
		if (InputManager::isKeyPressed(FOUR_KEY))
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState4(stateManager, window));
			return true;
		}
	}
	return true;
}

void MainMenu::update()
{
	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	totalTime += Application::getDT();

	float r = 0.5f + 0.5f*cos(totalTime*0.1347652371f);
	float g = 0.5f + 0.5f*sin(totalTime);
	float b = 0.5f + 0.5f*cos(totalTime);

	Application::setBackgroundColour(Vec3(b, r, g));

	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "cube")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(Convert::convertDegreeToRadian(50.0f * Application::getDT()),
					Convert::convertDegreeToRadian(50.0f * Application::getDT()),
					Convert::convertDegreeToRadian(50.0f * Application::getDT())
				));

			Application::getGameObjects()[i]->getComponent<ModelComponent>().lock()->setDiffuse(Vec3(r, g, b));
		}
	}
}

void MainMenu::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}

	ResourceManager::getSprite(menuSprite)->pushToScreen(Vec2(0.0f, 0.0f));
}