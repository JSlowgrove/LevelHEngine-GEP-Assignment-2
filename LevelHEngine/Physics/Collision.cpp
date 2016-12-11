#include "Collision.h"

namespace Collision
{

	bool rectRectIntersect(Vec2 posBoxA, Vec2 dimBoxA, Vec2 posBoxB, Vec2 dimBoxB)
	{
		if (posBoxA.x <= (posBoxB.x + dimBoxB.x)
			&& posBoxA.y <= (posBoxB.y + dimBoxB.y)
			&& posBoxB.x <= (posBoxA.x + dimBoxA.x)
			&& posBoxB.y <= (posBoxA.y + dimBoxA.y))
		{
			return true;
		}
		return false;
	}

	bool cubeCubeIntersect(Vec3 posBoxA, Vec3 dimBoxA, Vec3 posBoxB, Vec3 dimBoxB)
	{
		//Half dimensions for center
		Vec3 halfDimA = dimBoxA * 0.5f;
		Vec3 halfDimB = dimBoxB * 0.5f;

		//calculate max/min coords for box a
		float minAX = posBoxA.x - halfDimA.x;
		float maxAX = posBoxA.x + halfDimA.x;
		float minAY = posBoxA.y - halfDimA.y;
		float maxAY = posBoxA.y + halfDimA.y;
		float minAZ = posBoxA.z - halfDimA.z;
		float maxAZ = posBoxA.z + halfDimA.z;

		//calculate max/min coords for box b
		float minBX = posBoxB.x - halfDimB.x;
		float maxBX = posBoxB.x + halfDimB.x;
		float minBY = posBoxB.y - halfDimB.y;
		float maxBY = posBoxB.y + halfDimB.y;
		float minBZ = posBoxB.z - halfDimB.z;
		float maxBZ = posBoxB.z + halfDimB.z;

		bool collisionX = false;
		bool collisionY = false;
		bool collisionZ = false;

		if (minAX < minBX)
		{
			if (maxAX >= minBX)
				collisionX = true;
		}
		else if (maxBX >= minAX)
		{
			collisionX = true;
		}

		if (minAY < minBY)
		{
			if (maxAY >= minBY)
				collisionY = true;
		}
		else if (maxBY >= minAY)
		{
			collisionY = true;
		}

		if (minAZ < minBZ)
		{
			if (maxAZ >= minBZ)
				collisionZ = true;
		}
		else if (maxBZ >= minAZ)
		{
			collisionZ = true;
		}

		//check for intersection
		return (collisionX && collisionY && collisionZ);
	}

	bool circleCircleIntersect(Vec2 circle1Pos, Vec2 circle2Pos, float circle1Rad, float circle2Rad)
	{
		// gets the combination of the 2 circles radius
		float radSum = circle1Rad + circle2Rad;
		//work out the distance between the circles
		float distance = Mechanics::distanceBetweenTwoPoints(circle1Pos, circle2Pos);
		//if the distance between the two circles is less than the sum of the radius's then there will be a collision
		if (distance < radSum)
		{
			return true;
		}
		return false;
	}

	bool sphereSphereIntersect(Vec3 sphere1Pos, Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad)
	{
		// gets the combination of the 2 sphere's radius
		float radSum = sphere1Rad + sphere2Rad;
		//work out the distance between the spheres
		float distance = Mechanics::distanceBetweenTwoPoints(sphere1Pos, sphere2Pos);

		//if the distance between the two spheres is less than the sum of the radius's then there will be a collision
		if (distance < radSum)
		{
			return true;
		}
		return false;
	}

	bool circleRectIntersect(Vec2 circlePos, Vec2 boxPos, float circleRad, Vec2 boxDim)
	{
		//check if the the circle is inside the box
		if (circlePos.x + circleRad < boxPos.x + boxDim.x && circlePos.x + circleRad > boxPos.x - boxDim.x
			&& circlePos.y + circleRad < boxPos.y + boxDim.y && circlePos.y + circleRad > boxPos.y - boxDim.y
			|| circlePos.x - circleRad < boxPos.x + boxDim.x && circlePos.x - circleRad > boxPos.x - boxDim.x
			&& circlePos.y - circleRad < boxPos.y + boxDim.y && circlePos.y - circleRad > boxPos.y - boxDim.y)
		{
			return true;
		}
		return false;
	}

}