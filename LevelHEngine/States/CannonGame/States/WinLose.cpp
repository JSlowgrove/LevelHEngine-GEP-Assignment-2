#include "WinLose.h"

#include "../../MainMenu.h"
#include "../../../Core/InputManager.h"
#include "../../../ResourceManagement/ResourceManager.h"
#include "../../../Core/Application.h"
#include "Help.h"


WinLose::WinLose(StateManager* stateManager, SDL_Window* window, bool inGameStart, int score)
	: State(stateManager, window, "CannonGameHelp"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/Voltaic.ogg"))
{
	winLoseID = ResourceManager::initialiseSprite("Assets/img/winLose.png");
	gameStart = inGameStart;
	scoreText = new Text("Score: " + std::to_string(score), "Assets/font/isl_jupiter.ttf", 120, 255, 255, 255);
}

WinLose::~WinLose()
{
	delete scoreText;
}

bool WinLose::input()
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

		if (InputManager::isKeyReleased(RETURN_KEY))
		{
			stateManager->removeLastState();
		}

		if (InputManager::isKeyReleased(H_KEY))
		{
			stateManager->addState(new Help(stateManager, window));
		}
	}

	return true;
}

void WinLose::update()
{
	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

void WinLose::draw()
{
	ResourceManager::getSprite(winLoseID)->pushToScreen(Vec2(180.0f, 80.0f));
	if (!gameStart)
	{
		scoreText->pushToScreen(Vec2(450.0f, 400.0f));
	}
}