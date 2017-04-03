#include "FlockingDemo.h"

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


FlockingDemo::FlockingDemo(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "FlockingDemo"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/LongTimeComing.ogg"))
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

	//Initlaise the flocks
	flock = new Flocking(25, boidSpriteID, WindowFrame::getWindowRes().x, WindowFrame::getWindowRes().y, 25.0f);
	flock3D = new Flocking(25, "cube", "default", "magenta", 15.0f, 10.0f, 5.0f, 2.0f);

	//Initalise the flocking as 3D
	use3D = true;

	//initlaise the ID images
	UIID = ResourceManager::initialiseSprite("Assets/img/FlockingDemoUI.png");
	helpID = ResourceManager::initialiseSprite("Assets/img/FlockingDemoHelp.png");
	help = true;

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

FlockingDemo::~FlockingDemo()
{
	delete flock;
	delete flock3D;
	if (!destroyed)
	{
		destroyState();
	}
}

bool FlockingDemo::input()
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
			if (use3D)
			{				
				flock3D->setRule1(1);
				flock3D->setRule2(1);
				flock3D->setRule3(1);
			}
			else
			{
				flock->setRule1(1);
				flock->setRule2(1);
				flock->setRule3(1);
			}
		}

		if (InputManager::isKeyReleased(ONE_KEY))
		{
			//If 1 is pressed only rule 1 is active & deactivate all other rules
			if (use3D)
			{
				flock3D->setRule1(1);
				flock3D->setRule2(0);
				flock3D->setRule3(0);
			}
			else
			{
				flock->setRule1(1);
				flock->setRule2(0);
				flock->setRule3(0);
			}
		}
			
		if (InputManager::isKeyReleased(TWO_KEY))
		{
			//If 2 is pressed only rule 2 is active & deactivate all other rules 
			if (use3D)
			{
				flock3D->setRule1(0);
				flock3D->setRule2(1);
				flock3D->setRule3(0);
			}
			else
			{
				flock->setRule1(0);
				flock->setRule2(1);
				flock->setRule3(0);
			}
		}

		if (InputManager::isKeyReleased(THREE_KEY))
		{
			//If 3 is pressed only rule 3 is active & deactivate all other rules 
			if (use3D)
			{
				flock3D->setRule1(0);
				flock3D->setRule2(0);
				flock3D->setRule3(1);
			}
			else
			{
				flock->setRule1(0);
				flock->setRule2(0);
				flock->setRule3(1);
			}
		}
		
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			//If Space is pressed scatter the flock by inverting rule 1
			if (use3D)
			{
				flock3D->setRule1(-1);
				flock3D->setRule2(1);
				flock3D->setRule3(1);
			}
			else
			{
				flock->setRule1(-1);
				flock->setRule2(1);
				flock->setRule3(1);
			}
		}

		if (InputManager::isKeyReleased(SPACE_KEY))
		{
			//If Space is released activate all rules
			if (use3D)
			{
				flock3D->setRule1(1);
				flock3D->setRule2(1);
				flock3D->setRule3(1);
			}
			else
			{
				flock->setRule1(1);
				flock->setRule2(1);
				flock->setRule3(1);
			}
		}

		if (InputManager::isKeyReleased(S_KEY))
		{
			//toggle 3D
			if (use3D)
			{
				use3D = false;
			}
			else
			{
				use3D = true;
			}
		}

		if (InputManager::isKeyReleased(H_KEY))
		{
			//toggle help
			if (help)
			{
				help = false;
			}
			else
			{
				help = true;
			}
		}
	}
	return true;
}

void FlockingDemo::update()
{
	InputManager::updateInputManager();

	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	//Update the flock
	if (use3D)
	{
		flock3D->update3D();
	}
	else
	{
		flock->update2D();
	}

	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//Update the camera
	Application::camera->getComponent<CameraControlComponent>().lock()->updateCamera(Application::getDT());
}

void FlockingDemo::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (use3D)
		{
			//draw the state
			Application::getGameObjects()[i]->render();
		}
		else
		{
			//check to see of not a boid
			std::size_t found = Application::getGameObjects()[i]->getName().find("boid");
			if (found == std::string::npos)
			{
				//draw the state
				Application::getGameObjects()[i]->render();
			}
		}
	}

	if (!use3D)
	{
		flock->draw2D();
	}

	//draw UI
	ResourceManager::getSprite(UIID)->pushToScreen(Vec2(0.0f, 0.0f));
	if (help)
	{
		ResourceManager::getSprite(helpID)->pushToScreen(Vec2(180.0f, 80.0f));
	}
}