#include "Collision.h"

namespace Collision
{

	bool rectRectIntersect(Vec2 PosBoxA, Vec2 DimBoxA, Vec2 PosBoxB, Vec2 DimBoxB)
	{
		if (PosBoxA.x <= (PosBoxB.x + DimBoxB.x)
			&& PosBoxA.y <= (PosBoxB.y + DimBoxB.y)
			&& PosBoxB.x <= (PosBoxA.x + DimBoxA.x)
			&& PosBoxB.y <= (PosBoxA.y + DimBoxA.y))
		{
			return true;
		}
		return false;
	}

	bool cubeCubeIntersect(Vec3 PosBoxA, Vec3 DimBoxA, Vec3 PosBoxB, Vec3 DimBoxB)
	{
		//Half dimensions for center
		Vec3 halfDimA = DimBoxA * 0.5f;
		Vec3 halfDimB = DimBoxB * 0.5f;

		//calculate max/min coords for box a
		float minAX = PosBoxA.x - halfDimA.x;
		float maxAX = PosBoxA.x + halfDimA.x;
		float minAY = PosBoxA.y - halfDimA.y;
		float maxAY = PosBoxA.y + halfDimA.y;
		float minAZ = PosBoxA.z - halfDimA.z;
		float maxAZ = PosBoxA.z + halfDimA.z;

		//calculate max/min coords for box b
		float minBX = PosBoxB.x - halfDimB.x;
		float maxBX = PosBoxB.x + halfDimB.x;
		float minBY = PosBoxB.y - halfDimB.y;
		float maxBY = PosBoxB.y + halfDimB.y;
		float minBZ = PosBoxB.z - halfDimB.z;
		float maxBZ = PosBoxB.z + halfDimB.z;

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

	bool collisionCheckCircleCircle(Vec2 circle1Pos, Vec2 circle2Pos, float circle1Rad, float circle2Rad)
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

	bool collisionCheckSphereSphere(Vec3 sphere1Pos, Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad)
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

	bool collisionCheckCircleBox(Vec2 circlePos, Vec2 boxPos, float circleRad, Vec2 boxDim)
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