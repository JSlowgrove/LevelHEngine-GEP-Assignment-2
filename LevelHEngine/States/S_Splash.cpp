#include "S_Splash.h"

S_Splash::S_Splash(S_StateManager* stateManager, SDL_Renderer* renderer, C_Vec2 dimensions)
	: S_State(stateManager, renderer, dimensions),
	splash(new C_Texture("Assets/Images/splash.png", renderer)),
	splashTimer(new C_Timer(3.0f))
{
}

S_Splash::~S_Splash()
{
	delete splash;
}

bool S_Splash::input()
{
	//Check for user input
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: //If player closes the window, end the game loop

			return false;
			break;
		}
	}
	return true;
}

void S_Splash::update(float dt)
{
	//Update the timer
	splashTimer->upadateTimer(dt);

	//exit the splash screen if the timer is up
	if (splashTimer->checkTimer())
	{
		stateManager->changeState(new SM_MainMenu(stateManager, renderer, dimensions));
		return;
	}
}

void S_Splash::draw()
{
	//draw the image
	splash->pushToScreen(
		renderer, 
		C_Vec2((dimensions.x * 0.5f) - (dimensions.y * 0.375f), dimensions.y * 0.125f),
		C_Vec2(dimensions.y * 0.75f, dimensions.y * 0.75f)
		);
}