#include "MainMenu.h"

#include "../Core/GameObject.h"
#include "../Core/InputManager.h"
#include "../Core/Application.h"
#include "../Components/ModelComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoundingSphereComponent.h"
#include "../Physics/Collision.h"

MainMenu::MainMenu(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "MainMenu"), 
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/ExitThePremises.ogg"))
{
	auto camera = GameObject::create("camera").lock();
	camera->addComponent<CameraComponent>();
	camera->addComponent<TransformComponent>();
	Application::camera = camera;

	auto sphere1 = GameObject::create("sphere1").lock();
	sphere1->addComponent<TransformComponent>();
	sphere1->addComponent<ModelComponent>();
	sphere1->addComponent<BoundingSphereComponent>();

	auto sphere2 = GameObject::create("sphere2").lock();
	sphere2->addComponent<TransformComponent>();
	sphere2->addComponent<ModelComponent>();
	sphere2->addComponent<BoundingSphereComponent>();

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

	auto lightingCube = GameObject::create("lightingCube").lock();
	lightingCube->addComponent<TransformComponent>();
	lightingCube->addComponent<ModelComponent>();

	sphere1->awake();
	sphere2->awake();
	camera->awake();
	sam->awake();
	heli->awake();
	barrel->awake();
	background->awake();
	lightingCube->awake();

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 2.0f, -12.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(-15.0f), 0.0f, 0.0f));

	sphere1->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	sphere1->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, -2.0f, 6.0f));
	sphere1->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere1->getComponent<ModelComponent>().lock()->initaliseShaders("default", "cyan");
	sphere1->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		sphere1->getComponent<ModelComponent>().lock()->getMeshID()
	);
 	sphere1->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
 		sphere1->getComponent<TransformComponent>().lock()->getScale()
 	);

	sphere2->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	sphere2->getComponent<TransformComponent>().lock()->setPos(Vec3(2.0f,-2.0f, 6.0f));
	sphere2->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere2->getComponent<ModelComponent>().lock()->initaliseShaders("default", "magenta");
	sphere2->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		sphere2->getComponent<ModelComponent>().lock()->getMeshID()
	);
	sphere2->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
 		sphere2->getComponent<TransformComponent>().lock()->getScale()
 	);

	sam->getComponent<TransformComponent>().lock()->setScale(Vec3(0.2f, 0.2f, 0.2f));
	sam->getComponent<TransformComponent>().lock()->setPos(Vec3(-5.0f, -2.0f, 0.0f));
	sam->getComponent<ModelComponent>().lock()->initaliseMesh("sam", "sam.png");
	sam->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	barrel->getComponent<TransformComponent>().lock()->setScale(Vec3(0.2f, 0.2f, 0.2f));
	barrel->getComponent<TransformComponent>().lock()->setPos(Vec3(5.0f, -3.0f, 0.0f));
	barrel->getComponent<TransformComponent>().lock()->rotate( Vec3(0.0f, 0.0f, 0.0f));
	barrel->getComponent<ModelComponent>().lock()->initaliseMesh("barrel", "barrel.png");
	barrel->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	heli->getComponent<TransformComponent>().lock()->setScale(Vec3(0.03f, 0.03f, 0.03f));
	heli->getComponent<TransformComponent>().lock()->setPos(Vec3(2.5f, 0.0f, 0.0f));
	heli->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	heli->getComponent<ModelComponent>().lock()->initaliseMesh("heli", "heli.png");
	heli->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	background->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -100.0f));
	background->getComponent<TransformComponent>().lock()->setScale(Vec3(125.0f, 125.0f, 125.0f));
	background->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(120.0f), 0.0f, 0.0f));
	background->getComponent<ModelComponent>().lock()->initaliseMesh("flatPlane", "background.jpg");
	background->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	lightingCube->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 0.0f));
	lightingCube ->getComponent<TransformComponent>().lock()->setScale(Vec3(1.0f, 1.0f, 1.0f));
	lightingCube->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	lightingCube->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	lightingCube->getComponent<ModelComponent>().lock()->initaliseShaders("default", "white");
	
	//initalise velocities
	s1V = s2V = Vec3(0.0f, 0.0f, 0.0f);

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
		if (InputManager::isKeyPressed(E_KEY))
		{
			s1V.y = moveVel;
		}
		if (InputManager::isKeyPressed(R_KEY))
		{
			s1V.y = -moveVel;
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

	//Rotate the lighting cube to demonstrate it.
	float tmp = 0.0f;

	//perform collision detection
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->checkForComponent("boundingSphere"))
		{
			//loop through all others with bounding spheres
			for (unsigned int j = 0; j < Application::getGameObjects().size(); j++)
			{
				if (Application::getGameObjects()[j]->checkForComponent("boundingSphere") && j != i)
				{
					//check for collision
					if (Collision::sphereSphereIntersect(
						Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->getPos(),
						Application::getGameObjects()[j]->getComponent<TransformComponent>().lock()->getPos(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
						Application::getGameObjects()[j]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius()
					))
					{
						Logging::logI("Collision");
						tmp += 200.0f;
						//sphere 1
// 						if (s1V.x > 0.0f)
// 						{
// 							s1V.x = -moveVel;
// 						}
// 						else if (s1V.x < 0.0f)
// 						{
// 							s1V.x = moveVel;
// 						}
// 						if (s1V.y > 0.0f)
// 						{
// 							s1V.y = -moveVel;
// 						}
// 						else if (s1V.y < 0.0f)
// 						{
// 							s1V.y = moveVel;
// 						}
// 						if (s1V.z > 0.0f)
// 						{
// 							s1V.z = -moveVel;
// 						}
// 						else if (s1V.z < 0.0f)
// 						{
// 							s1V.z = moveVel;
// 						}
// 
// 						//sphere 2
// 						if (s2V.x > 0.0f)
// 						{
// 							s2V.x = -moveVel;
// 						}
// 						else if (s2V.x < 0.0f)
// 						{
// 							s2V.x = moveVel;
// 						}
// 						if (s2V.y > 0.0f)
// 						{
// 							s2V.y = -moveVel;
// 						}
// 						else if (s2V.y < 0.0f)
// 						{
// 							s2V.y = moveVel;
// 						}
// 						if (s2V.z > 0.0f)
// 						{
// 							s2V.z = -moveVel;
// 						}
// 						else if (s2V.z < 0.0f)
// 						{
// 							s2V.z = moveVel;
// 						}
					}
				}
			}
		}
	}

	//loops through the game objects
 	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
 	{
		if(Application::getGameObjects()[i]->getName() == "heli" || Application::getGameObjects()[i]->getName() == "sam" 
			|| Application::getGameObjects()[i]->getName() == "barrel")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(0.0f, Convert::convertDegreeToRadian(tmp * dt), 0.0f)
			);
// 			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
// 				Vec3(0.0f, Convert::convertDegreeToRadian(200.0f * dt), 0.0f)
// 			);
		}
		if (Application::getGameObjects()[i]->getName() == "lightingCube")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(Convert::convertDegreeToRadian(100.0f * dt), 
					Convert::convertDegreeToRadian(100.0f * dt), 
					0.0f)
			);
		}

		//update positions with new velocities
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