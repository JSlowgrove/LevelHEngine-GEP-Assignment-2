#include "CannonControllerComponent.h"

#include "../../../ResourceManagement/ResourceManager.h"
#include "../../../Core/Logging.h"
#include "../../../Maths/Convert.h"
#include "../../../Core/InputManager.h"
#include "../../../Components/TransformComponent.h"

CannonControllerComponent::~CannonControllerComponent()
{
}

void CannonControllerComponent::onAwake()
{		
	id = "cannoncontroller";
	rotationSpeed = 1.0f;
	cannonPower = 50.0f;
	cannonAngle = Vec2(270.0f, 45.0f);
}

void CannonControllerComponent::onDestroy()
{
}

void CannonControllerComponent::handleInput()
{
		//handle height
		if (InputManager::isKeyPressed(W_KEY))
		{
			if (cannonAngle.y <= 90.0f - rotationSpeed)
			{
				cannonAngle.y += rotationSpeed;
			}				
		}
		if (InputManager::isKeyPressed(S_KEY))
		{
			if (cannonAngle.y >= 0.0f + rotationSpeed)
			{
				cannonAngle.y -= rotationSpeed;
			}
		}

		//handle direction
		if (InputManager::isKeyPressed(D_KEY))
		{
			if (cannonAngle.x <= 360.0f - rotationSpeed)
			{
				cannonAngle.x += rotationSpeed;
				cannonRot.x += rotationSpeed;
			}
		}
		if (InputManager::isKeyPressed(A_KEY))
		{
			if (cannonAngle.x >= 180.0f + rotationSpeed)
			{
				cannonAngle.x -= rotationSpeed;
			}
		}
}

void CannonControllerComponent::update()
{
	getGameObject().lock()->getComponent<TransformComponent>().lock()->setRotation(Vec3(0.0f, Convert::convertDegreeToRadian(cannonAngle.y) * Application::getDT(), Convert::convertDegreeToRadian(cannonAngle.x) * Application::getDT()));
}

Vec3 CannonControllerComponent::calculateLaunchVeclocites()
{
	float alpha = Convert::convertDegreeToRadian(cannonAngle.x);
	float beta = Convert::convertDegreeToRadian(cannonAngle.y);
	
	float x = cos(alpha) * cos(beta);
	float z = sin(alpha) * cos(beta);
	float y = sin(beta);
	return Vec3(x * cannonPower, y * cannonPower, z * cannonPower);
}
