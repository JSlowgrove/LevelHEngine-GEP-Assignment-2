#pragma once

#include "math.h"

/**
@brief Contains the Vec3 structure with functions and overloaded operators.
*/
struct Vec3
{
	///Position variables
	float x, y, z;

	/**
	@brief Constructs the Vec3 setting the values to 0,0,0.
	*/
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

	/**
	@brief Constructs the Vec3 setting the values to the input coordinates.
	@param x The inputed x position.
	@param y The inputed y position.
	@param z The inputed z position.
	*/
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	/**
	@brief Constructs the Vec3 setting the values to the input coordinates.
	@param x The inputed x position.
	@param y The inputed y position.
	@param z The inputed z position.
	*/
	Vec3(int x, int y, int z) : x((float)x), y((float)y), z((float)z) {}

	/**
	@brief Overloads the += operator.
	@param vecIn The input Vec3.
	@returns The new vector.
	*/
	Vec3* operator += (Vec3 vecIn)
	{
		x += vecIn.x;
		y += vecIn.y;
		z += vecIn.y;
		return this;
	}

	/**
	@brief Overloads the -= operator.
	@param vecIn The input Vec3.
	@returns The new vector.
	*/
	Vec3* operator -= (Vec3 vecIn)
	{
		x -= vecIn.x;
		y -= vecIn.y;
		z -= vecIn.z;
		return this;
	}

	/**
	@brief Returns the length of the Vec3.
	@returns The length of the Vec3.
	*/
	float getLength()
	{
		return float(sqrt((x*x) + (y*y) + (z*z)));
	}

	/**
	@brief Returns a normalised version of the Vec3.
	@returns The normalised Vec3.
	*/
	Vec3 getNormalised()
	{
		float magnitude = getLength();
		Vec3 normalised = Vec3(x / magnitude, y / magnitude, z / magnitude);
		return normalised;
	}
};

/**
@brief Overloads the - operator allowing a Vec3 to be inverted.
@param vecIn The input Vec3.
@returns The new vector.
*/
inline Vec3 operator - (Vec3 vecIn)
{
	Vec3 vecOut;
	vecOut.x = -vecIn.x;
	vecOut.y = -vecIn.y;
	vecOut.z = -vecIn.z;
	return vecOut;
}

/**
@brief Overloads the - operator allowing Vec3's to be subtracted from each other.
@param vecInA One of the input Vec3's.
@param vecInB One of the input Vec3's.
@returns The new vector.
*/
inline Vec3 operator - (Vec3 vecInA, Vec3 vecInB)
{
	Vec3 vecOut;
	vecOut.x = vecInA.x - vecInB.x;
	vecOut.y = vecInA.y - vecInB.y;
	vecOut.z = vecInA.z - vecInB.z;
	return vecOut;
}

/**
@brief Overloads the + operator.
@param vecInA One of the input Vec3's.
@param vecInB One of the input Vec3's.
@returns The new vector.
*/
inline Vec3 operator + (Vec3 vecInA, Vec3 vecInB)
{
	Vec3 vecOut;
	vecOut.x = vecInA.x + vecInB.x;
	vecOut.y = vecInA.y + vecInB.y;
	vecOut.z = vecInA.z + vecInB.z;
	return vecOut;
}

/**
@brief Overloads the / operator allowing a Vec3 to be divided by a scalar.
@param vecInA One of the input Vec3's.
@param scalar The scalar to divide by.
@returns The new vector.
*/
inline Vec3 operator / (Vec3 vecInA, float scalar)
{
	Vec3 vecOut;
	vecOut.x = vecInA.x / scalar;
	vecOut.y = vecInA.y / scalar;
	vecOut.z = vecInA.z / scalar;
	return vecOut;
}

/**
@brief Overloads the * operator allowing a Vec3 to be multiplied by a scalar.
@param vecInA One of the input Vec3's.
@param scalar The scalar to multiply by.
@returns The new vector.
*/
inline Vec3 operator * (Vec3 vecInA, float scalar)
{
	Vec3 vecOut;
	vecOut.x = vecInA.x * scalar;
	vecOut.y = vecInA.y * scalar;
	vecOut.z = vecInA.z * scalar;
	return vecOut;
}

/**
@brief Overloads the * operator allowing a Vec2 to be multiplied by another Vec3.
@param vecInA One of the input Vec3's.
@param vecInB One of the input Vec3's.
@returns The new vector.
*/
inline Vec3 operator * (Vec3 vecInA, Vec3 vecInB)
{
	Vec3 vecOut;
	vecOut.x = vecInA.x * vecInB.x;
	vecOut.y = vecInA.y * vecInB.y;
	vecOut.z = vecInA.z * vecInB.z;
	return vecOut;
}