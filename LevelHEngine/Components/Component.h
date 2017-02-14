#pragma once

#include <memory>
#include "../Core/GameObject.h"

///forward declareations
class GameObject;
class Application;

/**
@brief A class that handles the components.
*/
class Component
{
	///Declare the game object as a friend
	friend class GameObject;

public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~Component();

	/**
	@brief A function to get the game object linked with the component.
	@returns Returns a weak pointer to the linked game object.
	*/
	std::weak_ptr<GameObject> getGameObject();

	/**
	@brief A virtual function for the componets awake.
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets update.
	*/
	virtual void onUpdate();

	/**
	@brief A virtual function for the componets render.
	*/
	virtual void onRender();

	/**
	@brief A virtual function for the componets destroy.
	*/
	virtual void onDestroy();

	/**
	@brief A function to set the componets destroyed boolean.
	@param inDestroyed A boolean for the state of destroyed.
	*/
	void setDestroyed(bool inDestroyed) { destroyed = inDestroyed; }

	/**
	@brief A function to get the componets destroyed boolean.
	@return The boolean for the state of destroyed.
	*/
	bool getDestroyed() { return destroyed; }

	/**
	@brief A function to set the components type ID.
	@param id The components type ID.
	*/
	std::string getID() { return id; }

private:
	///A weak pointer to the linked game object
	std::weak_ptr<GameObject> gameObject;
	///A boolean for if the component has been destroyed
	bool destroyed;

protected:
	///The ID of the component type
	std::string id;
};