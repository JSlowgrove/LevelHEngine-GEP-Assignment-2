#pragma once

#include <string>
#include <SDL.h>
#include "../Maths/M_Vec2.h"

/**
@brief Contains core utility functions for use within the code.
@author Jamie Slowgrove
*/
namespace C_Utilities
{
	/**
	@brief Logs the information message.
	@param message The message.
	*/
	void logI(std::string message);

	/**
	@brief Logs the error message.
	@param message The message.
	*/
	void logE(std::string message);

	/**
	@brief Checks to see if two rectangles intersect
	@param PosBoxA The position of the first rectangle.
	@param DimBoxA The dimensions of the first rectangle.
	@param PosBoxB The position of the second rectangle.
	@param DimBoxB The dimensions of the second rectangle.
	@returns True if the rectangles intersect
	*/
	bool rectRectIntersect(C_Vec2 PosBoxA, C_Vec2 DimBoxA, C_Vec2 PosBoxB, C_Vec2 DimBoxB);
}