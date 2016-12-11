#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "Mechanics.h"


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
	bool rectRectIntersect(Vec2 PosBoxA, Vec2 DimBoxA, Vec2 PosBoxB, Vec2 DimBoxB);

	/**
	@brief Checks to see if two cubes intersect (position is the center of the cube)
	@param PosBoxA The position of the first cube.
	@param DimBoxA The dimensions of the first cube.
	@param PosBoxB The position of the second cube.
	@param DimBoxB The dimensions of the second cube.
	@returns True if the cube intersect
	*/
	bool cubeCubeIntersect(Vec3 PosBoxA, Vec3 DimBoxA, Vec3 PosBoxB, Vec3 DimBoxB);

	/**
	@brief Takes in two circle positions, radius's to detect if the circles collide.
	@param circle1Pos The first circle position's to be used in the collision check.
	@param circle2Pos The second circle position's to be used in the collision check.
	@param circle1Rad The first circle radius's to be used in the collision check.
	@param circle2Rad The second circle radius's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool collisionCheckCircleCircle(Vec2 circle1Pos, Vec2 circle2Pos, float circle1Rad, float circle2Rad);

	/**
	@brief Takes in two sphere positions and radius's and uses this to detect if the sphere's collide.
	@param sphere1Pos The first sphere position's to be used in the collision check.
	@param sphere2Pos The second sphere position's to be used in the collision check.
	@param sphere1Rad The first sphere radius's to be used in the collision check.
	@param sphere2Rad The second sphere radius's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool collisionCheckSphereSphere(Vec3 sphere1Pos, Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad);

	/**
	@brief Takes in a circle position and radius and a box position and dimensions to detect for collision.
	@param circlePos The circle's position to be used in the collision check.
	@param boxPos The box's position to be used in the collision check.
	@param circleRad The sphere's radius to be used in the collision check.
	@param boxDim The box's dimension's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool collisionCheckCircleBox(Vec2 circlePos, Vec2 boxPos, float circleRad, Vec2 boxDim);

}