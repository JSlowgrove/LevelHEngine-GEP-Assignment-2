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
	moveX = moveY = moveZ = rotX = rotY = rotZ = true;
}

void CameraControlComponent::onDestroy()
{
}

void CameraControlComponent::handleInput()
{
	//movements
	if (InputManager::isKeyPressed(W_KEY) && moveZ)
	{
		movementVel.z = speed;
	}
	if (InputManager::isKeyReleased(W_KEY) && moveZ)
	{
		movementVel.z = 0.0f;
	}

	if (InputManager::isKeyPressed(A_KEY) && moveX)
	{
		movementVel.x = speed;
	}
	if (InputManager::isKeyReleased(A_KEY) && moveX)
	{
		movementVel.x = 0.0f;
	}

	if (InputManager::isKeyPressed(S_KEY) && moveZ)
	{
		movementVel.z = -speed;
	}
	if (InputManager::isKeyReleased(S_KEY) && moveZ)
	{
		movementVel.z = 0.0f;
	}

	if (InputManager::isKeyPressed(D_KEY) && moveX)
	{
		movementVel.x = -speed;
	}
	if (InputManager::isKeyReleased(D_KEY) && moveX)
	{
		movementVel.x = 0.0f;
	}

	if (InputManager::isKeyPressed(Q_KEY) && moveY)
	{
		movementVel.y = -speed;
	}
	if (InputManager::isKeyReleased(Q_KEY) && moveY)
	{
		movementVel.y = 0.0f;
	}

	if (InputManager::isKeyPressed(E_KEY) && moveY)
	{
		movementVel.y = speed;
	}

	if (InputManager::isKeyReleased(E_KEY) && moveY)
	{
		movementVel.y = 0.0f;
	}

	//rotations
	if (InputManager::isKeyPressed(UP_KEY) && rotX)
	{
		rotationVel.x = rotateSpeed;
	}
	if (InputManager::isKeyPressed(LEFT_KEY) && rotY)
	{
		rotationVel.y = -rotateSpeed;
	}
	if (InputManager::isKeyPressed(DOWN_KEY) && rotX)
	{
		rotationVel.x = -rotateSpeed;
	}
	if (InputManager::isKeyPressed(RIGHT_KEY) && rotY)
	{
		rotationVel.y = rotateSpeed;
	}
	if (InputManager::isKeyPressed(O_KEY) && rotZ)
	{
		rotationVel.z = rotateSpeed;
	}
	if (InputManager::isKeyPressed(P_KEY) && rotZ)
	{
		rotationVel.z = -rotateSpeed;
	}

	if (InputManager::isKeyReleased(UP_KEY) && rotX)
	{
		rotationVel.x = 0.0f;
	}
	if (InputManager::isKeyReleased(LEFT_KEY) && rotY)
	{
		rotationVel.y = 0.0f;
	}
	if (InputManager::isKeyReleased(DOWN_KEY) && rotX)
	{
		rotationVel.x = 0.0f;
	}
	if (InputManager::isKeyReleased(RIGHT_KEY) && rotY)
	{
		rotationVel.y = 0.0f;
	}
	if (InputManager::isKeyReleased(O_KEY) && rotZ)
	{
		rotationVel.z = 0.0f;
	}
	if (InputManager::isKeyReleased(P_KEY) && rotZ)
	{
		rotationVel.z = 0.0f;
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