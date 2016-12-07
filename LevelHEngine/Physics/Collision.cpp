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