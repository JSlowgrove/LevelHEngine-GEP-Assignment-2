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
#include "GameObject.h"

/**
@brief The namespace for all core code.
*/
namespace Core
{
	///forward declaration of game object
	class GameObject;

	/**
	@brief Contains details and functions for the application.
	*/
	class Application
	{
	public:

		/**
		@brief A static function to initialise Application.
		@param title The title of the window.
		@param windowPos The position of the window.
		@param windowRes The resolution of the window.
		@param fullscreen If the window should be fullscreen.
		@param frameRate The frame rate of the window.
		*/
		static void init(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate);

		/**
		@brief A static function that runs Application.
		@param argc The command line argument count.
		@param argv The command line argument vector.
		*/
		static void run(int argc, char *argv[]);

		/**
		@brief A static function that destroys the Application.
		*/
		static void destroy();


		/**
		@brief A static function to get game objects.
		*/
		static std::vector<std::shared_ptr<GameObject> >& getGameObjects();

	private:
		/**
		@brief A static function to initialise SDL.
		@returns If the initialisation succeeded.
		*/
		static bool initSDL();

		/**
		@brief A static function to initialise SDL TTF.
		@returns If the initialisation succeeded.
		*/
		static bool initTTF();

		/**
		@brief A static function to initialise SDL Mixer.
		@returns If the initialisation succeeded.
		*/
		static bool initMixer();

		/**
		@brief A static function to initialise GLEW.
		@returns If the initialisation succeeded.
		*/
		static bool initGLEW();

		///A pointer for the window.
		static SDL_Window *window;
		///The SDL OpenGL context.
		static SDL_GLContext glcontext;
		///A pointer to the state manager.
		static States::StateManager* stateManager;
		///A vector of the game objects.
		static std::vector< std::shared_ptr<GameObject> > gameObjects;
	};

}// End of Core namespace