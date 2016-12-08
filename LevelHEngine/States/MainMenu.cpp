#include "MainMenu.h"

#include "../Core/GameObject.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu"), backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/Cipher.ogg"))
{
	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();


	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>().lock()->setPos(Vec3(0.0f,0.0f,-50.0f));
	Application::camera = camera;

	auto cube = GameObject::create("cubeOfDoom").lock();
	cube->addComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, 0.0f));
	auto model = cube->addComponent<ModelComponent>().lock();
	model->initaliseMesh("sam", "sam.png");
	model->initaliseShaders("texture", "texture");

	camera->awake();
	cube->awake();

}

MainMenu::~MainMenu()
{
	//Stop music
	ResourceManager::getMusic(backgroundMusicID)->stopMusic();
	//Delete music pointers
	ResourceManager::deleteMusic(backgroundMusicID);
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
	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//Update the matrix for the render

	//get the camera mats
	
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		
	}
}

void MainMenu::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}
}