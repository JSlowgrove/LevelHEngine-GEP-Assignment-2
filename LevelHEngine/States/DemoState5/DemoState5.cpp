#include "DemoState5.h"

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


DemoState5::DemoState5(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState3"),
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
	
	auto tourus = GameObject::create("tourus").lock();
	tourus->addComponent<TransformComponent>();
	tourus->addComponent<ModelComponent>();

	//Awake the game objects

	camera->awake();
	tourus->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));

	tourus->getComponent<TransformComponent>().lock()->setScale(Vec3(1.5f, 1.5f, 1.5f));
	tourus->getComponent<ModelComponent>().lock()->initalisePrimitive(Primitives::TOURUS);
	tourus->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "black");

	//initalise bool
	initialLoop = true;

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	totalTime = 0.0f;
}

DemoState5::~DemoState5()
{
	if (!destroyed)
	{
		destroyState();
	}
}

bool DemoState5::input()
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
			//If Escape is pressed, return to main menu
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new MainMenu(stateManager, window));
			return true;
		}
	}
	return true;
}

void DemoState5::update()
{
	InputManager::updateInputManager();

	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//loops through the game objects
 	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
 	{
 		if (Application::getGameObjects()[i]->getName() == "tourus")
 		{
 			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
 				Vec3(Convert::convertDegreeToRadian(100.0f * Application::getDT()),
					Convert::convertDegreeToRadian(100.0f * Application::getDT()), 0.0f)
 			);
 		}
 	}

	totalTime += Application::getDT();

	//set background colour to change
	float r = 0.5f + 0.5f*cos(totalTime*0.1347652371f);
	float g = 0.5f + 0.5f*sin(totalTime);
	float b = 0.5f + 0.5f*cos(totalTime);
	Application::setBackgroundColour(Vec3(r, g, b));

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());
}

void DemoState5::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}