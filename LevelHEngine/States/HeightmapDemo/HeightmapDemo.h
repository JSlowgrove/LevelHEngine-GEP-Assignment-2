#pragma once

#include "../State.h"
#include "../StateManager.h"
#include "../../Maths/Vec3.h"

/**
@brief A State that contains and runs the Demo.
*/
class HeightmapDemo : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	HeightmapDemo(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~HeightmapDemo();

	/**
	@brief Handles the State input.
	@returns If false then quit the State.
	*/
	bool input();

	/**
	@brief A function to update the State.
	*/
	void update();

	/**
	@brief A function to draw the State to the screen.
	*/
	void draw();

private:
	///The background music id.
	std::string backgroundMusicID;
	///Initital loop bool
	bool initialLoop;
	///A boolean for help toggle
	bool helpToggle;
	///A boolean for camera toggle
	bool cameraToggle;
	///The default camera position
	Vec3 defaultCameraPos;
	///The default camera rotation
	Vec3 defaultCameraRotation;
	///The UI image ID
	std::string UIImageID;
	///The Help image ID
	std::string helpID;
	///The heightmap image ID
	std::string heightmapImageID;
};