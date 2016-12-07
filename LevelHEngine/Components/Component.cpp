#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

std::weak_ptr<GameObject> Component::getGameObject()
{
	return gameObject;
}

void Component::awake()
{

}

void Component::update()
{

}

void Component::render()
{

}

void Component::destroy()
{

}

