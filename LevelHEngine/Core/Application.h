#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <memory>
#include "Logging.h"
#include "WindowFrame.h"
#include "../Maths/Vec2.h"
#include "../States/StateManager.h"
#include "../States/Splash.h"

/**
@brief The namespace for all core code.
*/
namespace Core
{

	/**
	@brief Contains details and functions for the application.
	*/
	class Application
	{
	public:

		/**
		@brief Constructs Application.
		@param title The title of the window.
		@param windowPos The position of the window.
		@param windowRes The resolution of the window.
		@param fullscreen If the window should be fullscreen.
		@param frameRate The frame rate of the window.
		*/
		Application(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate);

		/**
		@brief Destructs Application.
		*/
		~Application();

		/**
		@brief Runs Application.
		@param argc The command line argument count.
		@param argv The command line argument vector.
		*/
		void run(int argc, char *argv[]);

		/**
		@brief Destroys the Application.
		*/
		void destroy();

	private:
		/**
		@brief Initialise SDL.
		@returns If the initialisation succeeded.
		*/
		bool initSDL();

		/**
		@brief Initialise SDL TTF.
		@returns If the initialisation succeeded.
		*/
		bool initTTF();

		/**
		@brief Initialise SDL Mixer.
		@returns If the initialisation succeeded.
		*/
		bool initMixer();

		/**
		@brief Initialise GLEW.
		@returns If the initialisation succeeded.
		*/
		bool initGLEW();

		///A pointer for the window.
		SDL_Window *window;
		///The SDL OpenGL context.
		SDL_GLContext glcontext;
		///A pointer to the state manager.
		States::StateManager* stateManager;
	};

}// End of Core namespace