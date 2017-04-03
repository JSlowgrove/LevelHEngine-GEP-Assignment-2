#include "AimBallComponent.h"

#include "../../../Core/Application.h"
#include "../../../Core/Logging.h"
#include "../../../Core/InputManager.h"
#include "../../../Components/TransformComponent.h"

AimBallComponent::~AimBallComponent()
{
}

void AimBallComponent::onAwake()
{
	id = "aimballcomponent";
	velocities = Vec3(0.0f, 0.0f, 0.0f);
	inUse = false;
}

void AimBallComponent::onDestroy()
{
}

void AimBallComponent::setVelocities(Vec3 inVel)
{
	velocities = inVel;
}

void AimBallComponent::update()
{
	getGameObject().lock()->getComponent<TransformComponent>().lock()->translate(velocities * Application::getDT());
}

void AimBallComponent::resetBall()
{
	getGameObject().lock()->getComponent<TransformComponent>().lock()->setPos(resetPos);
	velocities = Vec3(0.0f, 0.0f, 0.0f);
}

void AimBallComponent::applyGravity()
{
	if (inUse)
	{
		velocities.y += -1.0f;
		if (velocities.y < -9.81f)
		{
			velocities.y = -9.81;
		}
	}
}
