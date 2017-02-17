#pragma once

#include "math.h"

/**
@brief Contains the Vec4 structure with functions and overloaded operators.
*/
struct Vec4
{
	///Position variables
	float x, y, z, w;

	/**
	@brief Constructs the Vec4 setting the values to 0,0,0,0.
	*/
	Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	/**
	@brief Constructs the Vec4 setting the values to the input coordinates.
	@param x The inputed x position.
	@param y The inputed y position.
	@param z The inputed z position.
	@param w The inputed w position.
	*/
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	/**
	@brief Constructs the Vec4 setting the values to the input coordinates.
	@param x The inputed x position.
	@param y The inputed y position.
	@param z The inputed z position.
	@param w The inputed w position.
	*/
	Vec4(int x, int y, int z, int w) : x((float)x), y((float)y), z((float)z), w((float)w) {}

	/**
	@brief Overloads the += operator.
	@param vecIn The input Vec4.
	@returns The new vector.
	*/
	Vec4* operator += (Vec4 vecIn)
	{
		x += vecIn.x;
		y += vecIn.y;
		z += vecIn.y;
		w += vecIn.w;
		return this;
	}

	/**
	@brief Overloads the -= operator.
	@param vecIn The input Vec3.
	@returns The new vector.
	*/
	Vec4* operator -= (Vec4 vecIn)
	{
		x -= vecIn.x;
		y -= vecIn.y;
		z -= vecIn.z;
		w -= vecIn.w;
		return this;
	}

	/**
	@brief Returns the length of the Vec4.
	@returns The length of the Vec4.
	*/
	float getLength()
	{
		return float(sqrt((w*w) + (x*x) + (y*y) + (z*z)));
	}
};

/**
@brief Overloads the - operator allowing a Vec4 to be inverted.
@param vecIn The input Vec4.
@returns The new vector.
*/
inline Vec4 operator - (Vec4 vecIn)
{
	Vec4 vecOut;
	vecOut.x = -vecIn.x;
	vecOut.y = -vecIn.y;
	vecOut.z = -vecIn.z;
	vecOut.w = -vecIn.w;
	return vecOut;
}

/**
@brief Overloads the - operator allowing Vec4's to be subtracted from each other.
@param vecInA One of the input Vec4's.
@param vecInB One of the input Vec4's.
@returns The new vector.
*/
inline Vec4 operator - (Vec4 vecInA, Vec4 vecInB)
{
	Vec4 vecOut;
	vecOut.x = vecInA.x - vecInB.x;
	vecOut.y = vecInA.y - vecInB.y;
	vecOut.z = vecInA.z - vecInB.z;
	vecOut.w = vecInA.w - vecInB.w;
	return vecOut;
}

/**
@brief Overloads the + operator.
@param vecInA One of the input Vec4's.
@param vecInB One of the input Vec4's.
@returns The new vector.
*/
inline Vec4 operator + (Vec4 vecInA, Vec4 vecInB)
{
	Vec4 vecOut;
	vecOut.x = vecInA.x + vecInB.x;
	vecOut.y = vecInA.y + vecInB.y;
	vecOut.z = vecInA.z + vecInB.z;
	vecOut.w = vecInA.w + vecInB.w;
	return vecOut;
}

/**
@brief Overloads the / operator allowing a Vec4 to be divided by a scalar.
@param vecInA One of the input Vec4's.
@param scalar The scalar to divide by.
@returns The new vector.
*/
inline Vec4 operator / (Vec4 vecInA, float scalar)
{
	Vec4 vecOut;
	vecOut.x = vecInA.x / scalar;
	vecOut.y = vecInA.y / scalar;
	vecOut.z = vecInA.z / scalar;
	vecOut.w = vecInA.w / scalar;
	return vecOut;
}

/**
@brief Overloads the * operator allowing a Vec4 to be multiplied by a scalar.
@param vecInA One of the input Vec4's.
@param scalar The scalar to multiply by.
@returns The new vector.
*/
inline Vec4 operator * (Vec4 vecInA, float scalar)
{
	Vec4 vecOut;
	vecOut.x = vecInA.x * scalar;
	vecOut.y = vecInA.y * scalar;
	vecOut.z = vecInA.z * scalar;
	vecOut.w = vecInA.w * scalar;
	return vecOut;
}

/**
@brief Overloads the * operator allowing a Vec4 to be multiplied by another Vec4.
@param vecInA One of the input Vec4's.
@param vecInB One of the input Vec4's.
@returns The new vector.
*/
inline Vec4 operator * (Vec4 vecInA, Vec4 vecInB)
{
	Vec4 vecOut;
	vecOut.x = vecInA.x * vecInB.x;
	vecOut.y = vecInA.y * vecInB.y;
	vecOut.z = vecInA.z * vecInB.z;
	vecOut.w = vecInA.w * vecInB.w;
	return vecOut;
}