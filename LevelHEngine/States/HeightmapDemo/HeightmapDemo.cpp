#include "HeightmapDemo.h"

#include <SDL.h>
#include <iostream>
#include "../MainMenu.h"
#include "../../Maths/Vec2.h"
#include "../../Core/GameObject.h"
#include "../../Core/InputManager.h"
#include "../../Core/Application.h"
#include "../../Components/CameraComponent.h"
#include "../../Components/CameraControlComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/ModelComponent.h"
#include "../../ResourceManagement/ResourceManager.h"
#include "../../Maths/Convert.h"


HeightmapDemo::HeightmapDemo(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState2"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/DeliberateThought.ogg"))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.1f, 0.1f, 0.2f));

	//Set the camera defaults
	defaultCameraPos = Vec3(-6.7f, -9.3f, -28.2f);
	defaultCameraRotation = Vec3(0.9f, 0.0f, 0.0f);

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

	camera->getComponent<TransformComponent>().lock()->setPos(defaultCameraPos);
	camera->getComponent<TransformComponent>().lock()->setRotation(defaultCameraRotation);

	heightmap->getComponent<TransformComponent>().lock()->setScale(Vec3(1.0f, 1.0f, 1.0f));
	heightmap->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 15.0f, -5.0f));
	heightmap->getComponent<TransformComponent>().lock()->setRotation(Vec3(0.0f, 0.0f, Convert::convertDegreeToRadian(90.0f)));
 	heightmap->getComponent<ModelComponent>().lock()->initaliseHeightmap("Assets/img/map.png", "terrain.png");
 	heightmap->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	//initalise bools
	initialLoop = true;
	helpToggle = true;
	cameraToggle = false;

	//initalise images
	UIImageID = ResourceManager::initialiseSprite("Assets/img/heightmapDemoUI.png");
	helpID = ResourceManager::initialiseSprite("Assets/img/HeightmapHelp.png");
	heightmapImageID = ResourceManager::initialiseSprite("Assets/img/map.png");
	ResourceManager::getSprite(heightmapImageID)->scaleSprite(Vec2(337.0f, 337.0f));

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

HeightmapDemo::~HeightmapDemo()
{
	if (!destroyed)
	{
		destroyState();
	}
}

bool HeightmapDemo::input()
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

		if (InputManager::isKeyReleased(H_KEY))
		{
			//toggle help info
			if (helpToggle)
			{
				helpToggle = false;
			}
			else
			{
				helpToggle = true;
			}
		}

		if (InputManager::isKeyReleased(C_KEY))
		{
			//toggle camera controls
			if (cameraToggle)
			{
				cameraToggle = false;
			}
			else
			{
				cameraToggle = true;
			}
		}

		if (InputManager::isKeyReleased(SPACE_KEY))
		{
			//reset camera
			Application::camera->getComponent<TransformComponent>().lock()->setPos(defaultCameraPos);
			Application::camera->getComponent<TransformComponent>().lock()->setRotation(defaultCameraRotation);
		}

		if (cameraToggle)
		{
			//Handle the camera input
			Application::camera->getComponent<CameraControlComponent>().lock()->handleInput();
		}
	}

	Vec3 pos = Application::camera->getComponent<TransformComponent>().lock()->getPos();
	Vec3 rot = Application::camera->getComponent<TransformComponent>().lock()->getRotation();

	return true;
}

void HeightmapDemo::update()
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

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());

	if (!cameraToggle)
	{
		//loops through the game objects
		for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
		{
			if (Application::getGameObjects()[i]->getName() == "heightmap")
			{
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
					Vec3(0.0f, 0.0f, Convert::convertDegreeToRadian(10.0f * Application::getDT()))
				);
			}
		}
	}
}

void HeightmapDemo::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
	//draw the images
	ResourceManager::getSprite(UIImageID)->pushToScreen(Vec2(0.0f,0.0f));
	if (helpToggle)
	{
		ResourceManager::getSprite(helpID)->pushToScreen(Vec2(11.0f, 81.0f));
	}
	ResourceManager::getSprite(heightmapImageID)->pushToScreen(Vec2(927.0f, 140.0f));
}