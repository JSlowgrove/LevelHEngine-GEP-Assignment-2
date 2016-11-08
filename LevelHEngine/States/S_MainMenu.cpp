#include "S_MainMenu.h"

S_MainMenu::S_MainMenu(S_StateManager* stateManager, SDL_Renderer* renderer, M_Vec2 dimensions)
	: S_State(stateManager, renderer, dimensions)/*,
	//backgroundMusic(new C_Music("Assets/Audio/[INSERTNAME].ogg"))*/
{
}

S_MainMenu::~S_MainMenu()
{
	//Stop music
	//backgroundMusic->stopMusic();
	//Delete audio pointers
	//delete backgroundMusic;
	//delete pointers
}

bool S_MainMenu::input()
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

void S_MainMenu::update(float dt)
{
	//Keep the music playing
	//backgroundMusic->startMusic();
}

void S_MainMenu::draw()
{
}