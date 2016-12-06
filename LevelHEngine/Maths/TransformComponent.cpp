#include "TransformComponent.h"

namespace Maths
{

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::awake()
	{
		onAwake();
	}

	void TransformComponent::update()
	{
		onUpdate();
	}

	void TransformComponent::destroy()
	{
		onDestroy();
	}

	void TransformComponent::onAwake()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	void TransformComponent::onUpdate()
	{

	}

	void TransformComponent::onDestroy()
	{

	}

}