#pragma once

#include "math.h"

/**
@brief The namespace for all maths code.
*/
namespace Maths
{

	/**
	@brief Contains the Quaternion structure with functions and overloaded operators.
	*/
	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;

		/**
		@brief Returns the length of the Vec4.
		@returns The length of the Vec4.
		*/
		float getLength()
		{
			return sqrt((w*w) + (x*x) + (y*y) + (z*z));
		}

		Quaternion getNormalised()
		{
			Quaternion normalised;
			float length = getLength();
			normalised.w = w / length;
			normalised.x = x / length;
			normalised.y = y / length;
			normalised.z = z / length;
			return normalised;
		}
	};

	/**
	@brief Overloads the * operator allowing a Quaternion to be multiplied by another Quaternion.
	IMPORTANT: (Quaternion1 * Quaternion2) != (Quaternion2 * Quaternion1)
	@param q1 One of the input Quaternion's.
	@param q2 One of the input Quaternion's.
	@returns The new Quaternion.
	*/
	inline Quaternion operator * (Quaternion q1, Quaternion q2)
	{
		Quaternion q3;
		q3.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
		q3.x = (q1.w * q2.x) - (q1.x * q2.w) - (q1.y * q2.z) - (q1.z * q2.y);
		q3.y = (q1.w * q2.y) - (q1.x * q2.z) - (q1.y * q2.w) - (q1.z * q2.x);
		q3.z = (q1.w * q2.z) - (q1.x * q2.y) - (q1.y * q2.x) - (q1.z * q2.w);
		return q3;
	}

}// End of Maths namespace