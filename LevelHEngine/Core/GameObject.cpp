#include "GameObject.h"

GameObject::GameObject(std::string name) : name(name)
{
}

GameObject::~GameObject()
{
}

std::weak_ptr<GameObject> GameObject::create(std::string name)
{
	//create a new game object
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>(name);
	Application::getGameObjects().push_back(object);
	//return the object
	return object;
}

void GameObject::awake()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->onAwake();
	}
}

void GameObject::update()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		// Check each component has not been destroyed before updating
		if (components.at(i)->getDestroyed() == true)
		{
			// If it has remove the reference from this GameObject
			components.at(i)->onDestroy();
			components.erase(components.begin() + i);
			i--;
		}
		else
		{
			components.at(i)->onUpdate();
		}
	}
}

void GameObject::render()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->onRender();
	}
}

void GameObject::destroy()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->onDestroy();
	}
}

bool GameObject::checkForComponent(std::string id)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components.at(i)->getID() == id)
		{
			return true;
		}
	}
	return false;
}