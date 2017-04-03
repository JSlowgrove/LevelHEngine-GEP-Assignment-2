#pragma once

#include "Vec2.h"
#include "Vec3.h"

/**
@brief Contains maths conversion functions for use within the code.
*/
namespace Convert
{
	/**
	@brief Normailises a float.
	@param numToNormalise The number to normalise.
	@param maxNum The maximum value.
	@param minNum The minimum value.
	@returns The normailised float.
	*/
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
 	@brief Converts the coordinates to work with OpenGL
 	@param inVec The coordinates to convert.
 	@returns The converted coordinates.
 	*/
	Vec2 convertToOpenGLCoords(Vec2 inVec);

	/**
	@brief Scales the coordinates to work with OpenGL
	@param inVec The coordinates to scale.
	@returns The scaled coordinates.
	*/
	Vec2 scaleToOpenGLCoords(Vec2 inVec);

	/**
	@brief Scales the coordinates to work with OpenGL
	@param inVec The coordinates to scale.
	@returns The scaled coordinates.
	*/
	Vec3 scaleToOpenGLCoords(Vec3 inVec);
}