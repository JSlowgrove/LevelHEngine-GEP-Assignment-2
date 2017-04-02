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
#include "DemoGame5/DemoState5.h"
#include "DemoGame6/DemoState6.h"
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

	demoButtons[0] = UIManager::initialiseButton("Assets/img/demo1Button.png", "Assets/img/demo1ButtonHeld.png", Vec2(45.0f, 126.0f));
	demoButtons[1] = UIManager::initialiseButton("Assets/img/demo2Button.png", "Assets/img/demo2ButtonHeld.png", Vec2(45.0f, 221.0f));
	demoButtons[2] = UIManager::initialiseButton("Assets/img/demo3Button.png", "Assets/img/demo3ButtonHeld.png", Vec2(45.0f, 316.0f));
	demoButtons[3] = UIManager::initialiseButton("Assets/img/demo4Button.png", "Assets/img/demo4ButtonHeld.png", Vec2(45.0f, 412.0f));
	demoButtons[4] = UIManager::initialiseButton("Assets/img/demo5Button.png", "Assets/img/demo5ButtonHeld.png", Vec2(45.0f, 507.0f));
	demoButtons[5] = UIManager::initialiseButton("Assets/img/demo6Button.png", "Assets/img/demo6ButtonHeld.png", Vec2(45.0f, 603.0f));

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

		//menu input
		if (UIManager::getButton(demoButtons[0])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState1(stateManager, window));
			return true;
		}
		if (UIManager::getButton(demoButtons[1])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState2(stateManager, window));
			return true;
		}
		if (UIManager::getButton(demoButtons[2])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState3(stateManager, window));
			return true;
		}
		if (UIManager::getButton(demoButtons[3])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState4(stateManager, window));
			return true;
		}

		if (UIManager::getButton(demoButtons[4])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState5(stateManager, window));
			return true;
		}

		if (UIManager::getButton(demoButtons[5])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState6(stateManager, window));
			return true;
		}
	}
	return true;
}

void MainMenu::update()
{
	InputManager::updateInputManager();

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

	for (int i = 0; i < 6; i++)
	{
		UIManager::getButton(demoButtons[i])->draw();
	}
}