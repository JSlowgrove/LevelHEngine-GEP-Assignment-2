#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include "Maths/M_Vec2.h"
#include "Core/C_Logging.h"
#include "States/S_StateManager.h"
#include "States/S_Splash.h"

///Forces the game to run on the NIVDIA GPU, if one is available.
///http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// An initialisation function, mainly for GLEW
// This will also print to console the version of OpenGL we are using
bool InitGL()
{
	// GLEW has a problem with loading core OpenGL
	// See here: https://www.opengl.org/wiki/OpenGL_Loading_Library
	// The temporary workaround is to enable its 'experimental' features
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong. 
		std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

int main(int argc, char *argv[])
{
	//Set the window title
	std::string title = "Level H Engine";

	//Set the window and target resolutions
	C_Vec2 targetRes = C_Vec2(1280, 720);
	C_Vec2 windowRes = C_Vec2(1280, 720);

	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Failed initialisation
		C_Logging::logE("SDL failed to initialise: " + std::string(SDL_GetError()));
		return -1;
	}

	//Initialise SDL_ttf
	if (TTF_Init() < 0)
	{
		//Failed initialisation
		C_Logging::logE("SDL_ttf failed to initialise: " + std::string(TTF_GetError()));
		return -1;
	}

	//Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		C_Logging::logE("SDL_mixer failed to initialise: " + std::string(Mix_GetError()));
		return -1;
	}

	// Set the OpenGL context profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Time Check
	unsigned int lastTime = SDL_GetTicks();


#if !defined(_DEBUG)

	//Create Window
	C_Vec2 windowPos = C_Vec2(0, 0);
	SDL_Window *window = SDL_CreateWindow(title.c_str(),
		(int)windowPos.x, (int)windowPos.y,
		(int)windowRes.x, (int)windowRes.y,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

#else

	//Create Window
	C_Vec2 windowPos = C_Vec2(40, 40);
	SDL_Window *window = SDL_CreateWindow(title.c_str(),
		(int)windowPos.x, (int)windowPos.y,
		(int)windowRes.x, (int)windowRes.y,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

#endif	

	//Create Renderer from the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Set the renderer to work out the render at this resolution and then scale it up the 
	//closest resolution it can to the windows resolution (adds bars of the render colour)
	SDL_RenderSetLogicalSize(renderer, (int)targetRes.x, (int)targetRes.y);

	// Create an OpenGL context for the renderer
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	// Initialise GLEW
	if (!InitGL())
	{
		return -1;
	}

	// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);
	
	//Setup state manager and initial state
	S_StateManager * stateManager = new S_StateManager();
	stateManager->addState(new S_Splash(stateManager, renderer, targetRes));

	//Start Game Loop
	bool go = true;
	while (go)
	{
		//Time Check
		unsigned int current = SDL_GetTicks();
		float deltaTime = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		//Handle the current state inputs
		go = stateManager->input();

		//Update the current state
		stateManager->update(deltaTime);

		//set draw colour to black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

		//Clear the entire screen to the set colour
		SDL_RenderClear(renderer);

		//Draw the states
		stateManager->draw();

		//display renderer
		SDL_RenderPresent(renderer);

		//Time Limiter
		if (deltaTime < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTime)*1000.0f));
		}
	}
	//destroy data
	delete stateManager;
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}