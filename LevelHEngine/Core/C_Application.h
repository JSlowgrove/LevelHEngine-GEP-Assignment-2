#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include "C_Logging.h"
#include "C_Window.h"
#include "../Maths/M_Vec2.h"
#include "../States/S_StateManager.h"
#include "../States/S_Splash.h"

/**
@brief Contains details and functions for the application.
@author Jamie Slowgrove
*/
class C_Application
{
public:
	C_Application();
	~C_Application();
	void init(int argc, char *argv[]);
	void run();
	void destroy();
	
private:
	// An initialisation function, mainly for GLEW
	// This will also print to console the version of OpenGL we are using
	bool initGL();

	C_Window* windowDetails;
	SDL_Renderer* renderer;
	S_StateManager * stateManager;
	SDL_Window *window;
	SDL_GLContext glcontext;
};