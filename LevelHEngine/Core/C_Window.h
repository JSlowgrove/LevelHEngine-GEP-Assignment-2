#pragma once

#include <string>
#include "../Maths/M_Vec2.h"

/**
@brief Contains details and functions for use with the window.
@author Jamie Slowgrove
*/
class C_Window
{
public:
	/**
	@brief Constructs the C_Window.
	@param title The tile.
	@param targetRes The target resolution of the window.
	@param windowPos The window position.
	@param windowSize The window size.
	@param fullscreen The boolean for fullscreen.
	*/
	C_Window(std::string title, M_Vec2 targetRes, M_Vec2 windowPos, M_Vec2 windowSize, bool fullscreen);

	/**
	@brief Destructs C_Window.
	*/
	~C_Window();
	
	/**
	@brief Sets the window details.
	@param title The tile.
	@param targetRes The target resolution of the window.
	@param windowPos The window position.
	@param windowSize The window size.
	@param fullscreen The boolean for fullscreen.
	*/
	void setWindow(std::string title, M_Vec2 targetRes, M_Vec2 windowPos, M_Vec2 windowSize, bool fullscreen);
	
	/**
	@brief Sets the title of the window.
	@param title The tile.
	*/
	void setTitle(std::string title);

	/**
	@brief Sets the target resolution of the window.
	@param targetRes The target resolution of the window.
	*/
	void setTargetResoultion(M_Vec2 targetRes);

	/**
	@brief Sets the position of the window.
	@param windowPos The window position.
	*/
	void setWindowPos(M_Vec2 windowPos);

	/**
	@brief Sets the size of the window.
	@param windowSize The window size.
	*/
	void setWindowSize(M_Vec2 windowSize);

	/**
	@brief Sets if the window should be fullscreen.
	@param fullscreen The boolean for fullscreen.
	*/
	void setFullscreen(bool fullscreen);

	/**
	@brief Gets the title of the window.
	@returns The tile.
	*/
	std::string getTitle();

	/**
	@brief Gets the target resolution of the window.
	@returns The target resolution of the window.
	*/
	M_Vec2 getTargetResoultion();


	/**
	@brief Gets the position of the window.
	@returns The window position.
	*/
	M_Vec2 getWindowPos();

	/**
	@brief Gets the size of the window.
	@returns The window size.
	*/
	M_Vec2 getWindowSize();

	/**
	@brief Gets if the window should be fullscreen.
	@returns The boolean for fullscreen.
	*/
	bool getFullscreen();

private:
	///The window title.
	std::string title;
	///The target resolution of the window.
	M_Vec2 targetRes;
	///The position of the window.
	M_Vec2 windowPos;
	///The dimensions of the window.
	M_Vec2 windowSize;
	///A boolean for if the window should be fullscreen.
	bool fullscreen;
};