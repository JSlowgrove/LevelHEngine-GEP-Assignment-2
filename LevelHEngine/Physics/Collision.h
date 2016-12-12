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
	@param posBoxA The position of the first rectangle.
	@param dimBoxA The dimensions of the first rectangle.
	@param posBoxB The position of the second rectangle.
	@param dimBoxB The dimensions of the second rectangle.
	@returns If the rectangles intersect.
	*/
	bool rectRectIntersect(Vec2 posBoxA, Vec2 dimBoxA, Vec2 posBoxB, Vec2 dimBoxB);

	/**
	@brief Checks to see if two cubes intersect (position is the center of the cube)
	@param posBoxA The position of the first cube.
	@param dimBoxA The dimensions of the first cube.
	@param posBoxB The position of the second cube.
	@param dimBoxB The dimensions of the second cube.
	@returns If the cubes intersect.
	*/
	bool cubeCubeIntersect(Vec3 posBoxA, Vec3 dimBoxA, Vec3 posBoxB, Vec3 dimBoxB);

	/**
	@brief Checks to see if two cubes intersect (position is the center of the cube)
	@param posBoxA The position of the first cube.
	@param dimBoxA The dimensions of the first cube.
	@param posBoxB The position of the second cube.
	@param dimBoxB The dimensions of the second cube.
	@param collisionSides A reference to the sides of the cubes that collides, eg. x = -1 then left, x = 0 then none, x = 1 then right
	@returns If the cubes intersect.
	*/
	bool cubeCubeIntersect(Vec3 posBoxA, Vec3 dimBoxA, Vec3 posBoxB, Vec3 dimBoxB, Vec3 &collisionSides);

	/**
	@brief Checks to see if a cube and sphere intersects (position is the center of the cube)
	@param posBox The position of the cube.
	@param dimBox The dimensions of the cube.
	@param posSphere The position of the sphere.
	@param radSphere The radius of the sphere.
	@returns If the cubes intersect.
	*/
	bool sphereCubeIntersect(Vec3 posBox, Vec3 dimBox, Vec3 posSphere, float radSphere);

	/**
	@brief Checks to see if a cube and sphere intersects (position is the center of the cube)
	@param posBox The position of the cube.
	@param dimBox The dimensions of the cube.
	@param posSphere The position of the sphere.
	@param radSphere The radius of the sphere.
	@param collisionSides A reference to the sides of the cubes that collides, eg. x = -1 then left, x = 0 then none, x = 1 then right
	@returns If the cubes intersect.
	*/
	bool sphereCubeIntersect(Vec3 posBox, Vec3 dimBox, Vec3 posSphere, float radSphere, Vec3 &collisionSides);

	/**
	@brief Takes in two circle positions, radius's to detect if the circles collide.
	@param circle1Pos The first circle position's to be used in the collision check.
	@param circle2Pos The second circle position's to be used in the collision check.
	@param circle1Rad The first circle radius's to be used in the collision check.
	@param circle2Rad The second circle radius's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool circleCircleIntersect(Vec2 circle1Pos, Vec2 circle2Pos, float circle1Rad, float circle2Rad);

	/**
	@brief Takes in two sphere positions and radius's and uses this to detect if the sphere's collide.
	@param sphere1Pos The first sphere position's to be used in the collision check.
	@param sphere2Pos The second sphere position's to be used in the collision check.
	@param sphere1Rad The first sphere radius's to be used in the collision check.
	@param sphere2Rad The second sphere radius's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool sphereSphereIntersect(Vec3 sphere1Pos, Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad);

	/**
	@brief Takes in a circle position and radius and a box position and dimensions to detect for collision.
	@param circlePos The circle's position to be used in the collision check.
	@param boxPos The box's position to be used in the collision check.
	@param circleRad The sphere's radius to be used in the collision check.
	@param boxDim The box's dimension's to be used in the collision check.
	@return If the collision occurs.
	*/
	bool circleRectIntersect(Vec2 circlePos, Vec2 boxPos, float circleRad, Vec2 boxDim);

}