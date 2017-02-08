#include "CameraControlComponent.h"
#include "TransformComponent.h"
#include "../Core/InputManager.h"

CameraControlComponent::~CameraControlComponent()
{
}

void CameraControlComponent::onAwake()
{
	id = "cameraControl";
	speed = 10.0f;
	movementVel = Vec3(0.0f, 0.0f, 0.0f);
}

void CameraControlComponent::onDestroy()
{
}

void CameraControlComponent::handleInput(SDL_Event &incomingEvent)
{
	//reset velocity
	movementVel = Vec3(0.0f, 0.0f, 0.0f);

	if (InputManager::isKeyPressed(W_KEY))
	{
		movementVel.z = speed;
	}
	if (InputManager::isKeyPressed(A_KEY))
	{
		movementVel.x = speed;
	}
	if (InputManager::isKeyPressed(S_KEY))
	{
		movementVel.z = -speed;
	}
	if (InputManager::isKeyPressed(D_KEY))
	{
		movementVel.x = -speed;
	}
	if (InputManager::isKeyPressed(Q_KEY))
	{
		movementVel.y = -speed;
	}
	if (InputManager::isKeyPressed(E_KEY))
	{
		movementVel.y = speed;
	}
}

void CameraControlComponent::updateCamera(float dt)
{
	getGameObject().lock()->getComponent<TransformComponent>().lock()->translate(movementVel * dt);
}

void CameraControlComponent::setSpeed(float speed)
{
	this->speed = speed;
}