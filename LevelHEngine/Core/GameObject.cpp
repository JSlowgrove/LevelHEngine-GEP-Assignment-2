#include "GameObject.h"

GameObject::GameObject(std::string name) : name(name), std::enable_shared_from_this<GameObject>()
{
	// Add the shared_ptr to created GameObject to the vector in Application
	Application::getGameObjects().push_back(shared_from_this());
}

GameObject::~GameObject()
{
}

std::weak_ptr<GameObject> GameObject::create(std::string name)
{
	//create a new game object
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>(name);

	//return the object
	return object;
}

void GameObject::awake()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->awake();
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
			components.at(i)->destroy();
			components.erase(components.begin() + i);
			i--;
		}
		else
		{
			components.at(i)->update();
		}
	}
}

void GameObject::render()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->render();
	}
}

void GameObject::destroy()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->destroy();
	}
}
