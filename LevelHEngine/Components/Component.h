#pragma once

#include <memory>
#include "../Core/GameObject.h"

class GameObject;
class Application;

class Component
{
	friend class GameObject;

public:
	virtual ~Component();
	std::weak_ptr<GameObject> getGameObject();

	virtual void onAwake();
	virtual void onUpdate();
	virtual void onRender();
	virtual void onDestroy();
	void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
	bool getDestroyed() { return destroyed; }
	std::string getID() { return id; }

private:
	std::weak_ptr<GameObject> gameObject;
	bool destroyed;

protected:
	std::string id;
};