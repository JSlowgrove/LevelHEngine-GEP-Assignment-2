#pragma once

#include <string>
#include <SDL.h>

///Maths Definitions:
#define M_PI 3.141596f

/**
@brief Contains maths utility functions for use within the code.
@author Jamie Slowgrove
*/
namespace M_Utilities
{
	/**
	@brief Gets the value for PI.
	@returns The value for PI.
	*/
	float getPI();

	/**
	@brief Converts the degree to a radian.
	@param angle The angle to convert.
	@returns The converted radian.
	*/
	float convertDegreeToRadian(float angle);

	/**
	@brief Converts the radian to a degree.
	@param angle The angle to convert.
	@returns The converted degree.
	*/
	float convertRadianToDegree(float angle);
}