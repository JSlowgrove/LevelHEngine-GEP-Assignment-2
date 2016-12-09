#include "MainMenu.h"

#include "../Core/GameObject.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu"), backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/ExitThePremises.ogg"))
{
	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;

	auto sphere1 = GameObject::create("sphere1").lock();
	sphere1->addComponent<TransformComponent>();
	sphere1->addComponent<ModelComponent>();

	auto sphere2 = GameObject::create("sphere2").lock();
	sphere2->addComponent<TransformComponent>();
	sphere2->addComponent<ModelComponent>();

	auto sam = GameObject::create("sam").lock();
	sam->addComponent<TransformComponent>();
	sam->addComponent<ModelComponent>();

	auto barrel = GameObject::create("barrel").lock();
	barrel->addComponent<TransformComponent>();
	barrel->addComponent<ModelComponent>();

	auto heli = GameObject::create("heli").lock();
	heli->addComponent<TransformComponent>();
	heli->addComponent<ModelComponent>();

	auto background = GameObject::create("backgroundPlane").lock();
	background->addComponent<TransformComponent>();
	background->addComponent<ModelComponent>();

	auto floor = GameObject::create("floor").lock();
	floor->addComponent<TransformComponent>();
	floor->addComponent<ModelComponent>();

	auto leftWall = GameObject::create("leftWall").lock();
	leftWall->addComponent<TransformComponent>();
	leftWall->addComponent<ModelComponent>();

	auto rightWall = GameObject::create("rightWall").lock();
	rightWall->addComponent<TransformComponent>();
	rightWall->addComponent<ModelComponent>();

	auto backWall = GameObject::create("backWall").lock();
	backWall->addComponent<TransformComponent>();
	backWall->addComponent<ModelComponent>();

	auto frontWall = GameObject::create("frontWall").lock();
	frontWall->addComponent<TransformComponent>();
	frontWall->addComponent<ModelComponent>();

	sphere1->awake();
	sphere2->awake();
	camera->awake();
	sam->awake();
	heli->awake();
	barrel->awake();
	background->awake();
	floor->awake();
	leftWall->awake();
	rightWall->awake();
	backWall->awake();
	frontWall->awake();

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 2.0f, -12.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(-15.0f), 0.0f, 0.0f));

	sphere1->getComponent<TransformComponent>().lock()->setScale(Vec3(0.1f, 0.1f, 0.1f));
	sphere1->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, -2.0f, 6.0f));
	sphere1->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere1->getComponent<ModelComponent>().lock()->initaliseShaders("default", "cyan");

	sphere2->getComponent<TransformComponent>().lock()->setScale(Vec3(0.1f, 0.1f, 0.1f));
	sphere2->getComponent<TransformComponent>().lock()->setPos(Vec3(2.0f,-2.0f, 6.0f));
	sphere2->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere2->getComponent<ModelComponent>().lock()->initaliseShaders("default", "magenta");

	sam->getComponent<TransformComponent>().lock()->setScale(Vec3(0.2f, 0.2f, 0.2f));
	sam->getComponent<TransformComponent>().lock()->setPos(Vec3(-5.0f, -2.0f, 0.0f));
	sam->getComponent<ModelComponent>().lock()->initaliseMesh("sam", "sam.png");
	sam->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	barrel->getComponent<TransformComponent>().lock()->setScale(Vec3(0.2f, 0.2f, 0.2f));
	barrel->getComponent<TransformComponent>().lock()->setPos(Vec3(5.0f, -2.0f, 0.0f));
	barrel->getComponent<TransformComponent>().lock()->rotate( Vec3(0.0f, 0.0f, 0.0f));
	barrel->getComponent<ModelComponent>().lock()->initaliseMesh("barrel", "barrel.png");
	barrel->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	heli->getComponent<TransformComponent>().lock()->setScale(Vec3(0.03f, 0.03f, 0.03f));
	heli->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -2.0f, 0.0f));
	heli->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	heli->getComponent<ModelComponent>().lock()->initaliseMesh("heli", "heli.png");
	heli->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	background->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -100.0f));
	background->getComponent<TransformComponent>().lock()->setScale(Vec3(125.0f, 125.0f, 125.0f));
	background->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(120.0f), 0.0f, 0.0f));
	background->getComponent<ModelComponent>().lock()->initaliseMesh("flatPlane", "background.jpg");
	background->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	floor->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 0.1f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	floor->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	floor->getComponent<ModelComponent>().lock()->initaliseShaders("default", "green");

	leftWall->getComponent<TransformComponent>().lock()->setPos(Vec3(-5.2f, -3.0f, 5.5f));
	leftWall->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 1.0f, 5.5f));
	leftWall->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	leftWall->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	leftWall->getComponent<ModelComponent>().lock()->initaliseShaders("default", "white");

	rightWall->getComponent<TransformComponent>().lock()->setPos(Vec3(5.2f, -3.0f, 5.5f));
	rightWall->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 1.0f, 5.5f));
	rightWall->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	rightWall->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	rightWall->getComponent<ModelComponent>().lock()->initaliseShaders("default", "white");

	backWall->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 3.0f));
	backWall->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 1.0f, 0.5f));
	backWall->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	backWall->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	backWall->getComponent<ModelComponent>().lock()->initaliseShaders("default", "white");

	frontWall->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 8.0f));
	frontWall->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 1.0f, 0.5f));
	frontWall->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	frontWall->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	frontWall->getComponent<ModelComponent>().lock()->initaliseShaders("default", "white");

	//initalise bools
	s1F = s1B = s1L = s1R = s2F = s2B = s2L = s2R = false;

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();
}

MainMenu::~MainMenu()
{
	//Stop music
	ResourceManager::getMusic(backgroundMusicID)->stopMusic();
	//Delete music pointers
	ResourceManager::deleteMusic(backgroundMusicID);
	//Delete shaders
	ResourceManager::deleteAllShaders();
	//delete meshes
	ResourceManager::deleteAllMeshes();
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

		//reset velocities
		s1V = s2V = Vec3(0.0f, 0.0f, 0.0f);

		//handle sphere 1
		if (InputManager::isKeyPressed(W_KEY))
		{
			s1V.z = -moveVel;
		}
		if (InputManager::isKeyPressed(A_KEY))
		{
			s1V.x = -moveVel;
		}
		if (InputManager::isKeyPressed(S_KEY))
		{
			s1V.z = moveVel;
		}
		if (InputManager::isKeyPressed(D_KEY))
		{
			s1V.x = moveVel;
		}

		//handle sphere 2
		if (InputManager::isKeyPressed(UP_KEY))
		{
			s2V.z = -moveVel;
		}
		if (InputManager::isKeyPressed(LEFT_KEY))
		{
			s2V.x = -moveVel;
		}
		if (InputManager::isKeyPressed(DOWN_KEY))
		{
			s2V.z = moveVel;
		}
		if (InputManager::isKeyPressed(RIGHT_KEY))
		{
			s2V.x = moveVel;
		}

	}
	return true;
}

void MainMenu::update(float dt)
{
	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//loops through the game objects
 	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
 	{
		if(Application::getGameObjects()[i]->getName() == "heli" || Application::getGameObjects()[i]->getName() == "sam" 
			|| Application::getGameObjects()[i]->getName() == "barrel")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(0.0f, Convert::convertDegreeToRadian(200.0f * dt), 0.0f)
			);
		}
		if (Application::getGameObjects()[i]->getName() == "sphere1")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(s1V * dt);
		}
		if (Application::getGameObjects()[i]->getName() == "sphere2")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(s2V * dt);
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