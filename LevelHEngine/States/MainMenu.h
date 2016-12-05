#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "../Core/C_Texture.h"
#include "../Core/C_Audio.h"
#include "../Core/C_Music.h"
#include "../Core/C_Text.h"
#include "../Core/InputManager.h"

/**
@brief The namespace for all states code.
*/
namespace States
{

	/**
	@brief A State that contains and runs the Main Menu.
	@author Jamie Slowgrove
	*/
	class MainMenu : public State
	{
	public:
		/**
		@brief Constructs the State object.
		@param stateManager A pointer to the StateManager.
		@param window A pointer to the window in use.
		*/
		MainMenu(StateManager* stateManager, SDL_Window* window);

		/**
		@brief Destructs the State object.
		*/
		~MainMenu();

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
		///The background music.
		//C_Music* backgroundMusic;
	};

}// End of state namespace