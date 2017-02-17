#include "Application.h"

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <GL/glew.h>
#include "Logging.h"
#include "WindowFrame.h"
#include "../States/Splash.h"

SDL_Window* Application::window;
SDL_GLContext Application::glcontext;
StateManager* Application::stateManager;
std::vector<std::shared_ptr<GameObject> > Application::gameObjects;
std::shared_ptr<GameObject> Application::camera;
Vec3 Application::backgroundColour;
float Application::dt;

void Application::init(std::string title, Vec2 windowPos, Vec2 windowRes, bool fullscreen, float frameRate)
{
	//Initialise SDL
	initSDL();
	initTTF();
	initMixer();

	//Initialise the background colour to default
	setBackgroundColour(Vec3(0.0f, 0.0f, 0.0f));

	// Set the OpenGL context profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	WindowFrame::setWindow(title, windowPos, windowRes, fullscreen, frameRate);

	if (WindowFrame::getFullscreen())
	{
		//Create Window
		window = SDL_CreateWindow(WindowFrame::getTitle().c_str(),
			(int)WindowFrame::getWindowPos().x, (int)WindowFrame::getWindowPos().y,
			(int)WindowFrame::getWindowRes().x, (int)WindowFrame::getWindowRes().y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		//Create Window
		window = SDL_CreateWindow(WindowFrame::getTitle().c_str(),
			(int)WindowFrame::getWindowPos().x, (int)WindowFrame::getWindowPos().y,
			(int)WindowFrame::getWindowRes().x, (int)WindowFrame::getWindowRes().y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	}

	//Create an OpenGL context for the renderer
	glcontext = SDL_GL_CreateContext(window);

	//Initialise GLEW
	initGLEW();

	//Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);

	//setup state manager
	stateManager = new StateManager();
	//set the initial state
	stateManager->addState(new Splash(stateManager, window));

}
	
void Application::run(int argc, char *argv[])
{
	//Copy all arguments into a string (the first argument is the executable)
	std::vector<std::string> allArgs(argv, argv + argc);

	//Log the passed in commamds
	Logging::logI("Number of commands passed in: " + std::to_string(argc));
	Logging::logI("Passed in commands:");
	for (unsigned int i = 0; i < allArgs.size(); i++)
	{
		Logging::logI(allArgs[i]);
	}

	//Time Check
	unsigned int lastTime = SDL_GetTicks();

	//Start Game Loop
	bool go = true;
	while (go)
	{
		//Time Check
		unsigned int current = SDL_GetTicks();
		setDT((float)(current - lastTime) / 1000.0f);
		lastTime = current;

		//input
		go = stateManager->input();

		//update
		stateManager->update();

		//clear the frame-buffer to black
		glClearColor(backgroundColour.x, backgroundColour.y, backgroundColour.z, 1.0f);
		//write colour to the frame-buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw
		stateManager->draw();

		//display the window
		SDL_GL_SwapWindow(window);

		//Time Limiter
		if (getDT() < (1.0f / WindowFrame::getFrameRate()))
		{
			SDL_Delay((unsigned int)(((1.0f / WindowFrame::getFrameRate()) - getDT()) * 1000.0f));
		}
	}
}

void Application::destroy()
{
	//Destroy data
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Application::initGLEW()
{
	//Temporary workaround to fix GLEW's problem with loading core OpenGL by enabling its experimental features (Details: https://www.opengl.org/wiki/OpenGL_Loading_Library)
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Failed initialisation 
		Logging::logE("GLEW failed to initialise: " + std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
		return false;
	}

	//Log GLEW and OpenGL details
	Logging::logI("Using GLEW " + std::string(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))));
	Logging::logI("OpenGL Vendor: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR))));
	Logging::logI("OpenGL Renderer: " + std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER))));
	Logging::logI("OpenGL Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))));
	Logging::logI("OpenGL Shading Language Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION))));

	return true;
}

bool Application::initSDL()
{
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) < 0)
	{
		//Failed initialisation
		Logging::logE("SDL failed to initialise: " + std::string(SDL_GetError()));
		return false;
	}
	return true;
}

bool Application::initTTF()
{
	//Initialise SDL_ttf
	if (TTF_Init() < 0)
	{
		//Failed initialisation
		Logging::logE("SDL_ttf failed to initialise: " + std::string(TTF_GetError()));
		return false;
	}
	return true;
}

bool Application::initMixer()
{
	//Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Logging::logE("SDL_mixer failed to initialise: " + std::string(Mix_GetError()));
		return false;
	}
	return true;
}

std::vector<std::shared_ptr<GameObject> >& Application::getGameObjects()
{
	return gameObjects;
}

std::shared_ptr<GameObject>& Application::getCamera()
{
	return camera;
}

void Application::setBackgroundColour(Vec3 colour)
{
	backgroundColour = colour;
}

void Application::setDT(float inDT)
{
	dt = inDT;
}

float Application::getDT()
{
	return dt;
}