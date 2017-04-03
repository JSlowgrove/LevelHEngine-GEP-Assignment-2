#include "Splash.h"

#include "MainMenu.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../ResourceManagement/ResourceManager.h"

Splash::Splash(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "Splash"), splashTimer(new Timer(3.0f))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));
	splashSprite = ResourceManager::initialiseSprite("Assets/img/splash.png");
}

Splash::~Splash()
{
	if (!destroyed)
	{
		destroyState();
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
	//Update the timer
	splashTimer->upadateTimer(Application::getDT());

	//exit the splash screen if the timer is up
	if (splashTimer->checkTimer())
	{
		Application::drawLoadingScreen();
		destroyState();
		stateManager->changeState(new MainMenu(stateManager, window));
		return;
	}
}

void Splash::draw()
{
	ResourceManager::getSprite(splashSprite)->pushToScreen(Vec2(0.0f, 0.0f));
}