#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "Mechanics.h"

/**
@brief Contains physics functions for use within the code.
*/
namespace Physics
{

	/**
	@brief Contains Collision detection functions for use within the code.
	*/
	namespace Collision
	{

		/**
		@brief Checks to see if two rectangles intersect
		@param PosBoxA The position of the first rectangle.
		@param DimBoxA The dimensions of the first rectangle.
		@param PosBoxB The position of the second rectangle.
		@param DimBoxB The dimensions of the second rectangle.
		@returns True if the rectangles intersect
		*/
		bool rectRectIntersect(Maths::Vec2 PosBoxA, Maths::Vec2 DimBoxA, Maths::Vec2 PosBoxB, Maths::Vec2 DimBoxB);

		/**
		@brief Takes in two circle positions, radius's to detect if the circles collide.
		@param circle1Pos The first circle position's to be used in the collision check.
		@param circle2Pos The second circle position's to be used in the collision check.
		@param circle1Rad The first circle radius's to be used in the collision check.
		@param circle2Rad The second circle radius's to be used in the collision check.
		@return If the collision occurs.
		*/
		bool collisionCheckCircleCircle(Maths::Vec2 circle1Pos, Maths::Vec2 circle2Pos, float circle1Rad, float circle2Rad);

		/**
		@brief Takes in two sphere positions and radius's and uses this to detect if the sphere's collide.
		@param sphere1Pos The first sphere position's to be used in the collision check.
		@param sphere2Pos The second sphere position's to be used in the collision check.
		@param sphere1Rad The first sphere radius's to be used in the collision check.
		@param sphere2Rad The second sphere radius's to be used in the collision check.
		@return If the collision occurs.
		*/
		bool collisionCheckSphereSphere(Maths::Vec3 sphere1Pos, Maths::Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad);

		/**
		@brief Takes in a circle position and radius and a box position and dimensions to detect for collision.
		@param circlePos The circle's position to be used in the collision check.
		@param boxPos The box's position to be used in the collision check.
		@param circleRad The sphere's radius to be used in the collision check.
		@param boxDim The box's dimension's to be used in the collision check.
		@return If the collision occurs.
		*/
		bool collisionCheckCircleBox(Maths::Vec2 circlePos, Maths::Vec2 boxPos, float circleRad, Maths::Vec2 boxDim);

	}// End of collision detection namespace

}// End of physics namespace