#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include "Logging.h"
#include "WindowFrame.h"
#include "../Maths/Vec2.h"

/**
@brief The namespace for all core code.
*/
namespace Core
{

	/**
	@brief Contains details and functions for the application that inherits WindowFrame.
	*/
	class Application : public WindowFrame
	{
	public:
		Application(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate);
		~Application();
		void init(int argc, char *argv[]);
		void run();
		void destroy();

	private:
		bool initSDL();
		bool initTTF();
		bool initMixer();
		bool initGLEW();

		SDL_Window *window;
		SDL_GLContext glcontext;




		//TMP
		bool tmpInput();
	};

}// End of Core namespace