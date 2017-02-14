#pragma once

#include "MathsDefs.h"
#include "Vec2.h"

/**
@brief A namespace to contain maths functions to scale.
*/
namespace Scaling
{
	/**
	@brief Scale a vec2 using a number.
	@param vector The original vector.
	@param scale The number to scale by.
	@returns The scaled vector.
	*/
	Vec2 scaleVec2(Vec2 vector, int scale);

	/**
	@brief Scale the number using a number.
	@param number The original number.
	@param scale The number to scale by.
	@returns The scaled number.
	*/
	float scaleNumber(float number, int scale);
}