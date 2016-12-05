#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"

/**
@brief Contains physics functions for use within the code.
*/
namespace Physics
{

	/**
	@brief Contains physics mechanics functions for use within the code.
	*/
	namespace Mechanics
	{

		/**
		@brief Takes in two positions and works out the distance between them.
		@param point1Pos One of the positions.
		@param point2Pos One of the position.
		@return The distance between two points.
		*/
		float distanceBetweenTwoPoints(Maths::Vec3 point1Pos, Maths::Vec3 point2Pos);

		/**
		@brief Takes in two positions and works out the distance between them.
		@param point1Pos One of the positions.
		@param point2Pos One of the position.
		@return The distance between two points.
		*/
		float distanceBetweenTwoPoints(Maths::Vec2 point1Pos, Maths::Vec2 point2Pos);

		/**
		@brief Calculates velocity from the distance and time.
		@param distance The distance.
		@param time The time.
		@returns The calculated velocity.
		*/
		float calculateVelocity(float distance, float time);

	}// End of mechanics namespace

}//End of physics namespace