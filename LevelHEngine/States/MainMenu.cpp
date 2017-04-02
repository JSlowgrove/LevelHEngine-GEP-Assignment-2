#include "MainMenu.h"

#include <SDL.h>
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"
#include "../ResourceManagement/ResourceManager.h"
#include "CannonGame/CannonGame.h"
#include "HeightmapDemo/HeightmapDemo.h"
#include "FlockingDemo/FlockingDemo.h"
#include "DemoState5/DemoState5.h"
#include "DemoState6/DemoState6.h"
#include "Assignment1Demo/Assignment1Demo.h"
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

	menuButtons[0] = UIManager::initialiseButton("Assets/img/CannonGameButton.png", "Assets/img/CannonGameButtonHeld.png", Vec2(45.0f, 126.0f));
	menuButtons[1] = UIManager::initialiseButton("Assets/img/HeightmapDemoButton.png", "Assets/img/HeightmapDemoButtonHeld.png", Vec2(45.0f, 221.0f));
	menuButtons[2] = UIManager::initialiseButton("Assets/img/FlockingDemoButton.png", "Assets/img/FlockingDemoButtonHeld.png", Vec2(45.0f, 316.0f));
	menuButtons[3] = UIManager::initialiseButton("Assets/img/AStarLOSDemoButton.png", "Assets/img/AStarLOSDemoButtonHeld.png", Vec2(45.0f, 412.0f));
	menuButtons[4] = UIManager::initialiseButton("Assets/img/AsteroidsButton.png", "Assets/img/AsteroidsButtonHeld.png", Vec2(45.0f, 507.0f));
	menuButtons[5] = UIManager::initialiseButton("Assets/img/Assignment1DemoButton.png", "Assets/img/Assignment1DemoButtonHeld.png", Vec2(45.0f, 603.0f));

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
		if (UIManager::getButton(menuButtons[0])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new CannonGame(stateManager, window));
			return true;
		}

		if (UIManager::getButton(menuButtons[1])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new HeightmapDemo(stateManager, window));
			return true;
		}
		if (UIManager::getButton(menuButtons[2])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new FlockingDemo(stateManager, window));
			return true;
		}

		if (UIManager::getButton(menuButtons[3])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState6(stateManager, window));
			return true;
		}

		if (UIManager::getButton(menuButtons[4])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new DemoState5(stateManager, window));
			return true;
		}

		if (UIManager::getButton(menuButtons[5])->input())
		{
			//swtich to demo state
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new Assignment1Demo(stateManager, window));
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
		UIManager::getButton(menuButtons[i])->draw();
	}
}