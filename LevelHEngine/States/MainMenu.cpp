#include "MainMenu.h"

#include "../Core/InputManager.h"
#include "DemoState1.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu")
{
}

MainMenu::~MainMenu()
{
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
	}
	return true;
}

void MainMenu::update(float dt)
{
	//swtich to demo state
	stateManager->changeState(new DemoState1(stateManager, window));
	return;
}

void MainMenu::draw()
{
}