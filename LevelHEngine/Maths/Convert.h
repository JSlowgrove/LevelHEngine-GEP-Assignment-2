#pragma once

#include "Vec2.h"

/**
@brief Contains maths conversion functions for use within the code.
*/
namespace Convert
{
	float normaliseFloat(float numToNormalise, float maxNum, float minNum);

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

	/**
	@brief Converts the coordinates to work with OpenGL with top left being 0,0 and bottom right being 200,200.
	It takes the coordinates and converts them to a number between 0 and 2.
	It then takes this and -1 from each, setting it to the bottom left position.
	It then flips the coordinate along the y axis to get the top left position.
	@param coordinates The coordinates to convert.
	@returns The converted coordinates.
	*/
	Vec2 convertToOpenGLCoordinate(Vec2 coordinates);

}