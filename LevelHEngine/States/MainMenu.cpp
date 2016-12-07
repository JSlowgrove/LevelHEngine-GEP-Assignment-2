#include "MainMenu.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu"), backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/Cipher.ogg"))
{
	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	auto cube = std::make_shared<GameObject>("cubeOfDoom");
	cube->addComponent<CameraComponent>();
	cube->addComponent<ModelComponent>();
	cube->getComponent<ModelComponent>().lock()->initaliseMesh("Assets/obj/sam.obj", "Assets/mat/sam.png");
	cube->getComponent<ModelComponent>().lock()->initaliseShaders("Assets/shaders/vs.texture.txt", "Assets/shaders/fs.texture.txt");

	//initialise a cube with a texture
	Application::getGameObjects().push_back(cube);
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
	Mat4 proj = Application::getCamera()->getComponent<CameraComponent>().lock()->getProjection();
	Mat4 view = Application::getCamera()->getComponent<TransformComponent>().lock()->getTransformMat4();

	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		auto object = Application::getGameObjects()[i];
		if (object->getName() == "cubeOfDoom")
		{
			Mat4 mat = object->getComponent<TransformComponent>().lock()->getTransformMat4();
			object->getComponent<ModelComponent>().lock()->setRenderMats(view, proj, mat);
		}
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