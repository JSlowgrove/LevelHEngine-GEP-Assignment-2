#pragma once

#include <vector>
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"

/**
@brief A namespace for generating primitves.
*/
namespace Primitives
{
	//The avaliable primitive types
	enum PrimativeType
	{
		TOURUS
	};

	/**
	@brief A function to generate a tourus.
	@returns A vector of floats.
	*/
	std::vector<float> generateTourus();

	/**
	@brief A function to generate a point of a tourus.
	@param u The u value.
	@param v The v value.
	@returns A pooint of the tourus.
	*/
	Vec3 torus(float u, float v);
};