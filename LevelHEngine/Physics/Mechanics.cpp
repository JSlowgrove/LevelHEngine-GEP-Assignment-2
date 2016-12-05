#include "Mechanics.h"

namespace Physics
{

	namespace Mechanics
	{

		float distanceBetweenTwoPoints(Maths::Vec3 point1Pos, Maths::Vec3 point2Pos)
		{
			// work out the difference in the coordinates of the 2 points
			float deltaX = point1Pos.x - point2Pos.x;
			float deltaY = point1Pos.y - point2Pos.y;
			float deltaZ = point1Pos.z - point2Pos.z;
			// sqrt (dX^2 + dY^2 + dZ^2)
			float distance = sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
			return distance;
		}

		float distanceBetweenTwoPoints(Maths::Vec2 point1Pos, Maths::Vec2 point2Pos)
		{
			// work out the difference in the coordinates of the 2 points
			float deltaX = point1Pos.x - point2Pos.x;
			float deltaY = point1Pos.y - point2Pos.y;
			// sqrt (dX^2 + dY^2)
			float distance = sqrtf((deltaX * deltaX) + (deltaY * deltaY));
			return distance;
		}

		float calculateVelocity(float distance, float time)
		{
			//velocity = change in distance/ change in time
			float velocity = distance / time;
			return velocity;
		}

	}// End of mechanics namespace

}// End of physics namespace