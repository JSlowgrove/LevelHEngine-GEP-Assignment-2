#include "MainMenu.h"

/**
@brief The namespace for all states code.
*/
namespace States
{

	MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
		: State(stateManager, window, "MainMenu")/*, backgroundMusic(new ResourceManagement::Music("Assets/Audio/[INSERTNAME].ogg"))*/
	{
	}

	MainMenu::~MainMenu()
	{
		//Stop music
		//backgroundMusic->stopMusic();
		//Delete audio pointers
		//delete backgroundMusic;
	}

	bool MainMenu::input()
	{
		//Check for user input
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			Core::InputManager::pollInputEvent(incomingEvent);
			if (incomingEvent.type == SDL_QUIT)
			{
				//If player closes the window, end the game loop
				return false;
			}
			if (Core::InputManager::isKeyPressed(ESC_KEY))
			{
				//If Escape is pressed, end the game loop
				return false;
			}
		}
		return true;
	}

	void MainMenu::update(float dt)
	{
		//Keep the music playing
		//backgroundMusic->startMusic();
	}

	void MainMenu::draw()
	{
	}

}// End of state namespace