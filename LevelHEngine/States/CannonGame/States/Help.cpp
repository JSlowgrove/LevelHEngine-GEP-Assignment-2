#include "Help.h"

#include "../../MainMenu.h"
#include "../../../Core/InputManager.h"
#include "../../../ResourceManagement/ResourceManager.h"
#include "../../../Core/Application.h"


Help::Help(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "CannonGameHelp"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/Voltaic.ogg"))
{
	gameHelp = ResourceManager::initialiseSprite("Assets/img/CannonGameHelp.png");
}

Help::~Help()
{
}

bool Help::input()
{
	InputManager::updateInputManager();

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
			//If Escape is pressed, return to game
			Application::drawLoadingScreen();
			stateManager->destructPreviousState();
			stateManager->changeState(new MainMenu(stateManager, window));
			return true;
		}

		if (InputManager::isKeyReleased(H_KEY))
		{
			stateManager->removeLastState();
		}
	}

	return true;
}

void Help::update()
{
	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

void Help::draw()
{
	ResourceManager::getSprite(gameHelp)->pushToScreen(Vec2(180.0f, 80.0f));
}