#pragma once

#include <string>
#include "Logging.h"
#include "../Maths/Vec2.h"


/**
@brief Contains details and functions for use with the window.
*/
class WindowFrame
{
public:
	/**
	@brief A static function to set a Window.
	@param title The tile.
	@param windowPos The window position.
	@param windowRes The window resolution.
	@param fullscreen The boolean for fullscreen.
	@param frameRate The frame rate for the window.
	*/
	static void setWindow(std::string title, Vec2 windowPos, Vec2 windowRes, bool fullscreen, float frameRate);

	/**
	@brief A static function to set the title of the window.
	@param title The tile.
	*/
	static void setTitle(std::string title);

	/**
	@brief A static function to set the position of the window.
	@param windowPos The window position.
	*/
	static void setWindowPos(Vec2 windowPos);

	/**
	@brief A static function to set the resolution of the window.
	@param windowRes The window size.
	*/
	static void setWindowRes(Vec2 windowRes);

	/**
	@brief A static function to set if the window should be fullscreen.
	@param fullscreen The boolean for fullscreen.
	*/
	static void setFullscreen(bool fullscreen);

	/**
	@brief A static function to set the frame rate of the window.
	@param frameRate The frame rate for the window.
	*/
	static void setFrameRate(float frameRate);

	/**
	@brief A static function to get the title of the window.
	@returns The tile.
	*/
	static std::string getTitle();
		
	/**
	@brief A static function to get the position of the window.
	@returns The window position.
	*/
	static Vec2 getWindowPos();

	/**
	@brief A static function to get the size of the window.
	@returns The window resolution.
	*/
	static Vec2 getWindowRes();

	/**
	@brief A static function to get if the window should be fullscreen.
	@returns The boolean for fullscreen.
	*/
	static bool getFullscreen();

	/**
	@brief A static function to get the frame rate of the window.
	@returns The frame rate for the window.
	*/
	static float getFrameRate();

	/**
	@brief A static function to get the aspect of the window.
	@returns The aspect of the window.
	*/
	static float getAspect();

private:
	///The window title.
	static std::string title;
	///The position of the window.
	static Vec2 windowPos;
	///The resolution of the window.
	static Vec2 windowRes;
	///A boolean for if the window should be fullscreen.
	static bool fullscreen;
	///The wanted frame rate of the window.
	static float frameRate;
};
