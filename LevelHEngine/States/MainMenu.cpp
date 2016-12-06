#include "MainMenu.h"

/**
@brief The namespace for all states code.
*/
namespace States
{

	MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
		: State(stateManager, window, "MainMenu"), backgroundMusicID(ResourceManagment::ResourceManager::initialiseMusic("Assets/aud/Cipher.ogg"))
	{
		//start the music
		ResourceManagment::ResourceManager::getMusic(backgroundMusicID)->startMusic();
	}

	MainMenu::~MainMenu()
	{
		//Stop music
		ResourceManagment::ResourceManager::getMusic(backgroundMusicID)->stopMusic();
		//Delete music pointers
		ResourceManagment::ResourceManager::deleteMusic(backgroundMusicID);
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
		ResourceManagment::ResourceManager::getMusic(backgroundMusicID)->startMusic();
	}

	void MainMenu::draw()
	{
	}

}// End of state namespace