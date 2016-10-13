#include "SM_MainMenu.h"

SM_MainMenu::SM_MainMenu(S_StateManager* stateManager, SDL_Renderer* renderer, C_Vec2 dimensions)
	: S_State(stateManager, renderer, dimensions)/*,
	//backgroundMusic(new C_Music("Assets/Audio/[INSERTNAME].ogg"))*/
{
	//Initialise universal speed
	universalSpeed = new float(0.0f);
}

SM_MainMenu::~SM_MainMenu()
{
	//Stop music
	//backgroundMusic->stopMusic();
	//Delete audio pointers
	//delete backgroundMusic;
	//delete pointers
	delete universalSpeed;
}

bool SM_MainMenu::input()
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

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: //If Escape is pressed, end the game loop

				return false;
				break;
			}
		}
	}
	return true;
}

void SM_MainMenu::update(float dt)
{
	//Keep the music playing
	//backgroundMusic->startMusic();
}

void SM_MainMenu::draw()
{
}