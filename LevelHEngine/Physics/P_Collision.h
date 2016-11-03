#pragma once

#include <string>
#include <SDL.h>
#include "../Maths/M_Vec2.h"

/**
@brief Contains Physics collision detection functions for use within the code.
@author Jamie Slowgrove
*/
namespace P_Collision
{
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