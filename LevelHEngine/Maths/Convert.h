#pragma once

#include "MathsDefs.h"

/**
@brief The namespace for all maths code.
*/
namespace Maths
{

	/**
	@brief Contains maths conversion functions for use within the code.
	*/
	namespace Convert
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

	}//End of Convert namespace

}//End of Maths namespace