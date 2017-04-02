#include "DemoState1.h"

#include <SDL.h>
#include "../MainMenu.h"
#include "../../Core/GameObject.h"
#include "../../Core/InputManager.h"
#include "../../Core/Application.h"
#include "../../Core/Logging.h"
#include "../../Components/ModelComponent.h"
#include "../../Components/CameraComponent.h"
#include "../../Components/CameraControlComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/BoundingSphereComponent.h"
#include "../../Components/BoundingBoxComponent.h"
#include "../../ResourceManagement/ResourceManager.h"
#include "../../Physics/Collision.h"
#include "../../ResourceManagement/ResourceManager.h"
#include "../../Maths/Convert.h"
#include "../../Maths/Vec2.h"

DemoState1::DemoState1(StateManager* stateManager, SDL_Window* window)
	: State(stateManager, window, "DemoState1"),
	backgroundMusicID(ResourceManager::initialiseMusic("Assets/aud/ExitThePremises.ogg"))
{
	//Set the background colour
	Application::setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	//Create the game objects

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

	auto floor = GameObject::create("floor").lock();
	floor->addComponent<TransformComponent>();
	floor->addComponent<ModelComponent>();
	floor->addComponent<BoundingBoxComponent>();

	//Awake the game objects

	sphere1->awake();
	sphere2->awake();
	camera->awake();
	sam->awake();
	heli->awake();
	barrel->awake();
	background->awake();
	floor->awake();
	lightingCube->awake();

	//Initalise the game objects

	camera->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 2.0f, -12.0f));
	camera->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(-15.0f), 0.0f, 0.0f));

	sphere1->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	sphere1->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, 4.0f, 6.0f));
	sphere1->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere1->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "cyan");
	sphere1->getComponent<BoundingSphereComponent>().lock()->initaliseBoundingSphere(
		sphere1->getComponent<ModelComponent>().lock()->getMeshID()
	);
	sphere1->getComponent<BoundingSphereComponent>().lock()->scaleBoundingSphere(
		sphere1->getComponent<TransformComponent>().lock()->getScale()
	);

	sphere2->getComponent<TransformComponent>().lock()->setScale(Vec3(0.5f, 0.5f, 0.5f));
	sphere2->getComponent<TransformComponent>().lock()->setPos(Vec3(2.0f, 4.0f, 6.0f));
	sphere2->getComponent<ModelComponent>().lock()->initaliseMesh("sphere");
	sphere2->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "magenta");
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
	barrel->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	barrel->getComponent<ModelComponent>().lock()->initaliseMesh("barrel", "barrel.png");
	barrel->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	heli->getComponent<TransformComponent>().lock()->setScale(Vec3(0.03f, 0.03f, 0.03f));
	heli->getComponent<TransformComponent>().lock()->setPos(Vec3(2.0f, 0.0f, 0.0f));
	heli->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	heli->getComponent<ModelComponent>().lock()->initaliseMesh("heli", "heli.png");
	heli->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	background->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, 0.0f, -100.0f));
	background->getComponent<TransformComponent>().lock()->setScale(Vec3(125.0f, 125.0f, 125.0f));
	background->getComponent<TransformComponent>().lock()->rotate(Vec3(Convert::convertDegreeToRadian(120.0f), 0.0f, 0.0f));
	background->getComponent<ModelComponent>().lock()->initaliseMesh("flatPlane", "background.jpg");
	background->getComponent<ModelComponent>().lock()->initaliseShaders("texture", "texture");

	lightingCube->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -2.0f, 0.0f));
	lightingCube->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	lightingCube->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "white");

	floor->getComponent<TransformComponent>().lock()->setPos(Vec3(0.0f, -3.0f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->setScale(Vec3(10.0f, 0.1f, 5.0f));
	floor->getComponent<TransformComponent>().lock()->rotate(Vec3(0.0f, 0.0f, 0.0f));
	floor->getComponent<ModelComponent>().lock()->initaliseMesh("cube");
	floor->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders("default", "green");
	floor->getComponent<BoundingBoxComponent>().lock()->initaliseBoundingBox(
		floor->getComponent<ModelComponent>().lock()->getMeshID()
	);
	floor->getComponent<BoundingBoxComponent>().lock()->scaleBoundingBox(
		floor->getComponent<TransformComponent>().lock()->getScale()
	);

	//initalise velocities
	s1V = s2V = Vec3(0.0f, -9.81f, 0.0f);

	//initalise bools
	initialLoop = true;
	resetPos = false;

	//initalise the info images
	escInfo = ResourceManager::initialiseSprite("Assets/img/demo1esc.png");
	quickUserGuide = ResourceManager::initialiseSprite("Assets/img/demo1quickuserguide.png");

	//start the music
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//initialise the mouse press sound
	mousePressSoundID = ResourceManager::initialiseAudio("Assets/aud/threeTone2.ogg");
}

DemoState1::~DemoState1()
{
	if (!destroyed)
	{
		destroyState();
	}
}

bool DemoState1::input()
{
	//reset bool
	resetPos = false;

	//Check for user input
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		//reset velocities
		s1V = s2V = Vec3(0.0f, -9.81f, 0.0f);

		InputManager::pollInputEvent(incomingEvent);
		if (incomingEvent.type == SDL_QUIT)
		{
			//If player closes the window, end the game loop
			return false;
		}
		if (InputManager::isKeyPressed(ESC_KEY))
		{
			//If Escape is pressed, return to main menu
			Application::drawLoadingScreen();
			destroyState();
			stateManager->changeState(new MainMenu(stateManager, window));
			return true;

			//If Escape is pressed, end the game loop
			//return false;
		}

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
		//handle both
		if (InputManager::isKeyPressed(SPACE_KEY))
		{
			resetPos = true;
		}

		//if the mouse left button is pressed
		if (InputManager::isMouseButtonPressed(MOUSE_LEFT))
		{
			ResourceManager::getAudio(mousePressSoundID)->playEffect();
			std::string message = "Mouse press window position: " + std::to_string(InputManager::getMousePos().x) 
				+ "," + std::to_string(InputManager::getMousePos().y);
			Logging::logI(message);
		}
	}
	return true;
}

void DemoState1::update()
{
	InputManager::updateInputManager();

	//hack for initial loop
	if (initialLoop)
	{
		Application::setDT(0.0f);
		initialLoop = false;
	}

	//Store the next position of the objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "sphere1")
		{
			Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->setNextPos(
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->getPos()
				+ (s1V * Application::getDT()));
		}
		if (Application::getGameObjects()[i]->getName() == "sphere2")
		{
			Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->setNextPos(
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->getPos()
				+ (s2V * Application::getDT()));
		}
	}

	//Keep the music playing
	ResourceManager::getMusic(backgroundMusicID)->startMusic();

	//perform collision detection
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->checkForComponent("boundingSphere"))
		{
			//loop through all others with bounding spheres
			for (unsigned int j = 0; j < Application::getGameObjects().size(); j++)
			{
				//sphere box collision check
				if (Application::getGameObjects()[j]->checkForComponent("boundingBox"))
				{
					Vec3 collisonSide = Vec3(0.0f, 0.0f, 0.0f);
					//check for collision
					if (Collision::sphereCubeIntersect(
						Application::getGameObjects()[j]->getComponent<TransformComponent>().lock()->getPos(),
						Application::getGameObjects()[j]->getComponent<BoundingBoxComponent>().lock()->getBoundingBoxDimensions(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getNextPos(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
						collisonSide
					))
					{
						//Logging::logI("Sphere-Box Collision");

						//stop the y velocity
						if (Application::getGameObjects()[i]->getName() == "sphere1" && collisonSide.y == -1.0f)
						{
							s1V.y = 0.0f;
						}
						if (Application::getGameObjects()[i]->getName() == "sphere2" && collisonSide.y == -1.0f)
						{
							s2V.y = 0.0f;
						}
					}
				}
				//sphere sphere collision check
				if (Application::getGameObjects()[j]->checkForComponent("boundingSphere") && j != i)
				{
					//check for collision and react.
					if (Collision::sphereSphereIntersect(
						Application::getGameObjects()[j]->getComponent<BoundingSphereComponent>().lock()->getNextPos(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getNextPos(),
						Application::getGameObjects()[j]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
						Application::getGameObjects()[i]->getComponent<BoundingSphereComponent>().lock()->getBoundingSphereRadius(),
						s1V, s2V
					))
					{
						//Logging::logI("Sphere-Sphere Collision");
					}
				}
			}
		}
	}

	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		if (Application::getGameObjects()[i]->getName() == "heli" || Application::getGameObjects()[i]->getName() == "sam"
			|| Application::getGameObjects()[i]->getName() == "barrel")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(0.0f, Convert::convertDegreeToRadian(200.0f * Application::getDT()), 0.0f)
			);
		}
		if (Application::getGameObjects()[i]->getName() == "lightingCube")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->rotate(
				Vec3(Convert::convertDegreeToRadian(100.0f * Application::getDT()),
					Convert::convertDegreeToRadian(100.0f * Application::getDT()),
					0.0f)
			);
		}

		//update positions with new velocities
		if (Application::getGameObjects()[i]->getName() == "sphere1")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(s1V * Application::getDT());
			if (resetPos)
			{
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->setPos(Vec3(-2.0f, 4.0f, 6.0f));
			}
		}
		if (Application::getGameObjects()[i]->getName() == "sphere2")
		{
			Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->translate(s2V * Application::getDT());
			if (resetPos)
			{
				Application::getGameObjects()[i]->getComponent<TransformComponent>().lock()->setPos(Vec3(2.0f, 4.0f, 6.0f));
			}
		}
	}
}

void DemoState1::draw()
{
	//loops through the game objects
	for (unsigned int i = 0; i < Application::getGameObjects().size(); i++)
	{
		//draw the state
		Application::getGameObjects()[i]->render();
	}

	//draw the demo info
	ResourceManager::getSprite(escInfo)->pushToScreen(Vec2(10.0f, 10.0f));
	ResourceManager::getSprite(quickUserGuide)->pushToScreen(Vec2(1030.0f, 10.0f));
}