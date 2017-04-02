#include "State.h"
#include "../Core/Application.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../UI/UIManager.h"

State::State(StateManager * stateManager, SDL_Window* window, std::string name)
{
	//sets the pointer to the state manager
	this->stateManager = stateManager;
	//sets the pointer to the window
	this->window = window;
	//set the name
	this->name = name;
	destroyed = false;
}

State::~State() 
{
}

SDL_Window* State::getWindow()
{
	//return the window
	return window;
}

std::string State::getName()
{
	//return the state name
	return name;
}

void State::destroyState()
{
	//delete all UI
	UIManager::deleteAllUI();
	//delete all game objects
	Application::getGameObjects().clear();
	//stop all music
	ResourceManager::stopAllMusic();
	//Delete all resources
	ResourceManager::deleteAllAudio();
	ResourceManager::deleteAllMusic();
	ResourceManager::deleteAllMeshes();
	ResourceManager::deleteAllShaders();
	ResourceManager::deleteAllSprites();
	//set the state to destroyed
	destroyed = true;
}
