#pragma once

#include <memory>
#include "../Core/GameObject.h"

class GameObject;

class Component
{
	friend class GameObject;

public:
	Component();
	virtual ~Component();
	std::weak_ptr<GameObject> getGameObject();

	virtual void awake();
	virtual void update();
	virtual void render();
	virtual void destroy();
	void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
	bool getDestroyed() { return destroyed; }

private:
	std::weak_ptr<GameObject> gameObject;
	bool destroyed;
};