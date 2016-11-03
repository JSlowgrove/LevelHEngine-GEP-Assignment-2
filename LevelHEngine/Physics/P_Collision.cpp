#include "P_Collision.h"

namespace P_Collision
{

	bool rectRectIntersect(C_Vec2 PosBoxA, C_Vec2 DimBoxA, C_Vec2 PosBoxB, C_Vec2 DimBoxB)
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