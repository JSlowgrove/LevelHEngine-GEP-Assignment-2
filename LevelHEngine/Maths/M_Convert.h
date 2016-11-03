#pragma once

#include "M_Defs.h"

/**
@brief Contains maths convertion functions for use within the code.
@author Jamie Slowgrove
*/
namespace M_Convert
{
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