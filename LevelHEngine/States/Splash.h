#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "../Core/Timer.h"
#include "../Core/InputManager.h"
#include "MainMenu.h"


/**
@brief The namespace for all states code.
*/
namespace States
{

	/**
	@brief A State that contains and runs the splash screen.
	*/
	class Splash : public State
	{
	public:
		/**
		@brief Constructs the State object.
		@param stateManager A pointer to the StateManager.
		@param window A pointer to the window in use.
		*/
		Splash(StateManager* stateManager, SDL_Window* window);

		/**
		@brief Destructs the State object.
		*/
		~Splash();

		/**
		@brief Handles the State input.
		@returns If false then quit the State.
		*/
		bool input();

		/**
		@brief A function to update the State.
		@param dt The delta time.
		*/
		void update(float dt);

		/**
		@brief A function to draw the State to the screen.
		*/
		void draw();

	private:
		///The timer keeping the splash screen open
		Core::Timer* splashTimer;
	};

}// End of states namespace
