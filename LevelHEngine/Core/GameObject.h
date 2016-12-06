#pragma once

#include <memory>
#include <vector>
#include "Component.h"
#include "Application.h"

class Application;

/**
@brief The namespace for all core code.
*/
namespace Core
{

	class Component;

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
			component->awake();

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
			for (int i = 0; i < components.size(); i++)
			{
				// Get a weak pointer for the current component
				std::weak_ptr<T> component = dynamic_cast<T*>(components.at(i).get());

				// Check if the component is found
				if (component.valid())
				{
					//return a weak pointer to the component.
					return component;
				}
			}

			//if the component isn't found return a NULL weak pointer
			return weak_ptr<T>(); 
		}


		static std::weak_ptr<GameObject> create(std::string name);

		void setName(std::string name) { this->name = name; }
		std::string getName() { return name; }
		virtual void awake();
		virtual void update();
		virtual void render();
		virtual void destroy();
		void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
		bool getDestroyed() { return destroyed; }

	private:
		///The name of the game object
		std::string name;
		///A vector of components attached to the game object.
		std::vector < std::shared_ptr<Component> > components;
		bool destroyed;
	};

}//End of core namespace