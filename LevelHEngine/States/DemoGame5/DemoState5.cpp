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


DemoState5::DemoState5(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState5"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/ShowYourMoves.ogg"))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.1f));

	//Create the game objects

	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	camera->addComponent<CameraControlComponent>();
	Application::camera = camera;

	//Awake the game objects

	camera->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -20.0f));

	//Initialise the boid sprite
	boidSpriteID = ResourceManager::initialiseSprite("Assets/img/boid.png");
	ResourceManager::getSprite(boidSpriteID)->scaleSprite(Vec2(25.0f, 25.0f));

	//Initlaise the flock
	flock = new Flocking(25, boidSpriteID, WindowFrame::getWindowRes().x, WindowFrame::getWindowRes().y, 25.0f);

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

DemoState5::~DemoState5()
{
	delete flock;
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

		if (InputManager::isKeyReleased(RETURN_KEY))
		{
			//If Enter is pressed all rules are active
			flock->setRule1(1);
			flock->setRule2(1);
			flock->setRule3(1);
		}

		if (InputManager::isKeyReleased(ONE_KEY))
		{
			//If 1 is pressed only rule 1 is active
			flock->setRule1(1);
			//deactivate all other rules
			flock->setRule2(0);
			flock->setRule3(0);
		}
			
		if (InputManager::isKeyReleased(TWO_KEY))
		{
			//If Escape is pressed, return to main 
			flock->setRule2(1);
			//deactivate all other rules
			flock->setRule1(0);
			flock->setRule3(0);
		}

		if (InputManager::isKeyReleased(THREE_KEY))
		{
			//If 3 is pressed only rule 3 is active
			flock->setRule3(1);
			//deactivate all other rules
			flock->setRule1(0);
			flock->setRule2(0);
		}
		
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			//If Space is pressed scatter the flock
			flock->setRule2(1);
			flock->setRule3(1);
			//invert rule 1
			flock->setRule1(-1);
		}

		if (InputManager::isKeyReleased(SPACE_KEY))
		{
			//If Space is released activate all rules
			flock->setRule1(1);
			flock->setRule2(1);
			flock->setRule3(1);
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

	//Update the flock
	flock->update();

	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

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

	flock->draw();
}