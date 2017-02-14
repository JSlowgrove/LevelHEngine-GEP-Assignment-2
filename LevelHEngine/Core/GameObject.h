#pragma once

#include <memory>
#include <vector>
#include "../Components/Component.h"
#include "Application.h"

///Forward declarations
class Application;
class Component;

/**
@brief Contains details and functions for the game object.
*/
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:		
	/**
	@brief Constructs Application.
	@param name The name of the game object.
	*/
	GameObject(std::string name);

	/**
	@brief Destructs GameObject (virtual).
	*/
	virtual ~GameObject();

	/**
	@brief A template for adding components to the components vector.
	*/
	template <class T>
	std::weak_ptr<T> addComponent()
	{
		// Create new component
		std::shared_ptr<T> component(new T()); 
			
		//Store the new component in the game object component vector
		components.push_back(component);

		// Store a reference to the game object inside component
		component->gameObject = shared_from_this();
		//Activate the component
		component->onAwake();

		//store the id
		componentIDs.push_back(component->getID());

		//Return a weak pointer to the component to allow instance use.
		return component; 
	}

	/**
	@brief A template for getting a component from the components vector.
	*/
	template<class T>
	std::weak_ptr<T> getComponent()
	{
		//loop though the components
		for (unsigned int i = 0; i < components.size(); i++)
		{
			// Get a weak pointer for the current component
			std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(components.at(i));

			// Check if the component is found
			if (component.get() != nullptr)
			{
				//return a weak pointer to the component.
				return component;
			}
		}

		//if the component isn't found return a NULL weak pointer
		return std::weak_ptr<T>(); 
	}

	/**
	@brief A static function to create a game object.
	@param name The name to give to the game object.
	@returns A weak pointer to the created game object.
	*/
	static std::weak_ptr<GameObject> create(std::string name);

	/**
	@brief A function to set the name of the game object.
	@param inName The name to give to the game object.
	*/
	void setName(std::string inName) { name = inName; }

	/**
	@brief A function to get the name of the game object.
	@param The name of the game object.
	*/
	std::string getName() { return name; }

	/**
	@brief A virtual function for the game objects awake.
	*/
	virtual void awake();

	/**
	@brief A virtual function for the game objects update.
	*/
	virtual void update();

	/**
	@brief A virtual function for the game objects render.
	*/
	virtual void render();

	/**
	@brief A virtual function for the game objects destroy.
	*/
	virtual void destroy();

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
	@brief A function to check the if the game object has a specific componet.
	@param id The type ID of the component to check for.
	@return If the game object contains the component.
	*/
	bool checkForComponent(std::string id);

private:
	///The name of the game object.
	std::string name;
	///A vector of components attached to the game object.
	std::vector < std::shared_ptr<Component> > components;
	///A vector of the component ID's contained in the game object.
	std::vector < std::string > componentIDs;
	///A boolean for if the game object is destroyed.
	bool destroyed;
};