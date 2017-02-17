#pragma once

#include <vector>
#include "../Maths/Vec3.h"

namespace Primitives
{
	enum PrimativeType
	{
		TOURUS
	};

	std::vector<float> generateTourus();

	Vec3 torus(float u, float v);
};