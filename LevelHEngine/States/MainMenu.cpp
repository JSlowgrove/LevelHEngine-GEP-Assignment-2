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

		auto cube = std::make_shared<Core::GameObject>("cubeOfDoom");
		cube->addComponent<Rendering::CameraComponent>();
		cube->addComponent<Rendering::ModelComponent>();
		cube->getComponent<Rendering::ModelComponent>().lock()->initaliseMesh("Assets/obj/sam.obj", "Assets/mat/sam.png");
		cube->getComponent<Rendering::ModelComponent>().lock()->initaliseShaders("Assets/shaders/vs.texture.txt", "Assets/shaders/fs.texture.txt");

		//initialise a cube with a texture
		Core::Application::getGameObjects().push_back(cube);
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

		//Update the matrix for the render

		//get the camera mats
		Maths::Mat4 proj = Core::Application::getCamera()->getComponent<Rendering::CameraComponent>().lock()->getProjection();
		Maths::Mat4 view = Core::Application::getCamera()->getComponent<Maths::TransformComponent>().lock()->getTransformMat4();

		//loops through the game objects
		for (unsigned int i = 0; i < Core::Application::getGameObjects().size(); i++)
		{
			auto object = Core::Application::getGameObjects()[i];
			if (object->getName() == "cubeOfDoom")
			{
				Maths::Mat4 mat = object->getComponent<Maths::TransformComponent>().lock()->getTransformMat4();
				object->getComponent<Rendering::ModelComponent>().lock()->setRenderMats(view, proj, mat);
			}
		}
	}

	void MainMenu::draw()
	{
		//loops through the game objects
		for (unsigned int i = 0; i < Core::Application::getGameObjects().size(); i++)
		{
			//draw the state
			Core::Application::getGameObjects()[i]->render();
		}
	}

}// End of state namespace