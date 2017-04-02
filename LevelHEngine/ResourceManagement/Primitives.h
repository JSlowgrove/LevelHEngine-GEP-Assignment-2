#pragma once

#include <vector>
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"

namespace Primitives
{
	enum PrimativeType
	{
		TOURUS
	};

	std::vector<float> generateTourus();

	Vec3 torus(float u, float v);

	void drawLineBox(Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4);
};