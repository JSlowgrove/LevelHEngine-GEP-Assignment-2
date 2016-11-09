#include "P_Collision.h"

namespace P_Collision
{

	bool rectRectIntersect(Maths::Vec2 PosBoxA, Maths::Vec2 DimBoxA, Maths::Vec2 PosBoxB, Maths::Vec2 DimBoxB)
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
}