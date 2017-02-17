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
	rotateSpeed = 1.0f;
	movementVel = Vec3(0.0f, 0.0f, 0.0f);
	rotationVel = Vec3(0.0f, 0.0f, 0.0f);
}

void CameraControlComponent::onDestroy()
{
}

void CameraControlComponent::handleInput()
{
	//reset velocity
	movementVel = Vec3(0.0f, 0.0f, 0.0f);
	rotationVel = Vec3(0.0f, 0.0f, 0.0f);

	//movements
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

	//rotations
	if (InputManager::isKeyPressed(UP_KEY))
	{
		rotationVel.x = rotateSpeed;
	}
	if (InputManager::isKeyPressed(LEFT_KEY))
	{
		rotationVel.y = -rotateSpeed;
	}
	if (InputManager::isKeyPressed(DOWN_KEY))
	{
		rotationVel.x = -rotateSpeed;
	}
	if (InputManager::isKeyPressed(RIGHT_KEY))
	{
		rotationVel.y = rotateSpeed;
	}
	if (InputManager::isKeyPressed(PAGEUP_KEY))
	{
		rotationVel.z = rotateSpeed;
	}
	if (InputManager::isKeyPressed(PAGEDOWN_KEY))
	{
		rotationVel.z = -rotateSpeed;
	}
}

void CameraControlComponent::updateCamera(float dt)
{
	getGameObject().lock()->getComponent<TransformComponent>().lock()->translate(movementVel * dt);
	getGameObject().lock()->getComponent<TransformComponent>().lock()->rotate(rotationVel * dt);
}

void CameraControlComponent::setSpeed(float inSpeed)
{
	speed = inSpeed;
}

void CameraControlComponent::setRotateSpeed(float inRotateSpeed)
{
	rotateSpeed = inRotateSpeed;
}