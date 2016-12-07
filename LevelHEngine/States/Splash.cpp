#include "Splash.h"

Splash::Splash(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "Splash"), splashTimer(new Timer(3.0f))
{
}

Splash::~Splash()
{
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

void Splash::update(float dt)
{
	//Update the timer
	splashTimer->upadateTimer(dt);

	//exit the splash screen if the timer is up
	if (splashTimer->checkTimer())
	{
		stateManager->changeState(new MainMenu(stateManager, window));
		return;
	}
}

void Splash::draw()
{
}