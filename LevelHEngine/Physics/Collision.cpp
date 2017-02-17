#include "Collision.h"

#include "Mechanics.h"

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
		Vec3 collisionSides = Vec3(0.0f, 0.0f, 0.0f);
		return cubeCubeIntersect(posBoxA, dimBoxA, posBoxB, dimBoxB, collisionSides);
	}

	bool cubeCubeIntersect(Vec3 posBoxA, Vec3 dimBoxA, Vec3 posBoxB, Vec3 dimBoxB, Vec3 &collisionSides)
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
			{
				collisionX = true;
				collisionSides.x = 1.0f;
			}
		}
		else if (maxBX >= minAX)
		{
			collisionX = true;
			collisionSides.x = -1.0f;
		}

		if (minAY < minBY)
		{
			if (maxAY >= minBY)
			{
				collisionY = true;
				collisionSides.y = 1.0f;
			}
		}
		else if (maxBY >= minAY)
		{
			collisionY = true;
			collisionSides.y = -1.0f;
		}

		if (minAZ < minBZ)
		{
			if (maxAZ >= minBZ)
			{
				collisionZ = true;
				collisionSides.z = 1.0f;
			}
		}
		else if (maxBZ >= minAZ)
		{
			collisionZ = true;
			collisionSides.z = -1.0f;
		}

		//check for intersection
		return (collisionX && collisionY && collisionZ);
	}

	bool sphereCubeIntersect(Vec3 posBox, Vec3 dimBox, Vec3 posSphere, float radSphere)
	{
		Vec3 collisionSides = Vec3(0.0f, 0.0f, 0.0f);
		return sphereCubeIntersect(posBox, dimBox, posSphere, radSphere, collisionSides);
	}

	bool sphereCubeIntersect(Vec3 posBox, Vec3 dimBox, Vec3 posSphere, float radSphere, Vec3 &collisionSides)
	{
		//Half dimensions for center
		Vec3 halfDim = dimBox * 0.5f;

		//calculate max/min coords for box a
		float minBoxX = posBox.x - halfDim.x;
		float maxBoxX = posBox.x + halfDim.x;
		float minBoxY = posBox.y - halfDim.y;
		float maxBoxY = posBox.y + halfDim.y;
		float minBoxZ = posBox.z - halfDim.z;
		float maxBoxZ = posBox.z + halfDim.z;

		//calculate max/min coords for sphere
		float minSphereX = posSphere.x - radSphere;
		float maxSphereX = posSphere.x + radSphere;
		float minSphereY = posSphere.y - radSphere;
		float maxSphereY = posSphere.y + radSphere;
		float minSphereZ = posSphere.z - radSphere;
		float maxSphereZ = posSphere.z + radSphere;

		bool collisionX = false;
		bool collisionY = false;
		bool collisionZ = false;

		if (minBoxX < minSphereX)
		{
			if (maxBoxX >= minSphereX)
			{
				collisionX = true;
				collisionSides.x = 1.0f;
			}
		}
		else if (maxSphereX >= minBoxX)
		{
			collisionX = true;
			collisionSides.x = -1.0f;
		}

		if (minBoxY < minSphereY)
		{
			if (maxBoxY >= minSphereY)
			{
				collisionY = true;
				collisionSides.y = 1.0f;
			}
		}
		else if (maxSphereY >= minBoxY)
		{
			collisionY = true;
			collisionSides.y = -1.0f;
		}

		if (minBoxZ < minSphereZ)
		{
			if (maxBoxZ >= minSphereZ)
			{
				collisionZ = true;
				collisionSides.z = 1.0f;
			}
		}
		else if (maxSphereZ >= minBoxZ)
		{
			collisionZ = true;
			collisionSides.z = -1.0f;
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
		Vec3 vel1 = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 vel2 = Vec3(0.0f, 0.0f, 0.0f);
		return sphereSphereIntersect(sphere1Pos, sphere2Pos, sphere1Rad, sphere2Rad, vel1, vel2);
	}

	bool sphereSphereIntersect(Vec3 sphere1Pos, Vec3 sphere2Pos, float sphere1Rad, float sphere2Rad, Vec3 &vel1, Vec3 &vel2)
	{
		// gets the combination of the 2 sphere's radius
		float radSum = sphere1Rad + sphere2Rad;
		//work out the distance between the spheres
		float distance = Mechanics::distanceBetweenTwoPoints(sphere1Pos, sphere2Pos);

		//if the distance between the two spheres is less than the sum of the radius's then there will be a collision
		if (distance < radSum)
		{
			if (vel1.x != 0.0f)
			{
				vel1.x = 0.0f;
			}
			if (vel1.y != 0.0f && vel1.y != -9.81f)
			{
				vel1.y = 0.0f;
			}
			if (vel1.z != 0.0f)
			{
				vel1.z = 0.0f;
			}
			if (vel2.x != 0.0f)
			{
				vel2.x = 0.0f;
			}
			if (vel2.y != 0.0f && vel2.y != -9.81f)
			{
				vel2.y = 0.0f;
			}
			if (vel2.z != 0.0f)
			{
				vel2.z = 0.0f;
			}
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