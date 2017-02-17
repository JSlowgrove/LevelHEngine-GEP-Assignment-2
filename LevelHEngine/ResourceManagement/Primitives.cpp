#include "Primitives.h"

#include "../Maths/MathsDefs.h"

std::vector<float> Primitives::generateTourus()
{
	// the min/max parametric values for the surface
	float umin = 0;
	float umax = TWO_PI;
	float vmin = 0;
	float vmax = TWO_PI;

	std::vector<float> torusPoints;

	for (float u = umin; u <= umax; u += 0.05f)
	{
		for (float v = vmin; v <= vmax; v += 0.05f)
		{
			Vec3 P;
			P = torus(u, v);
			torusPoints.push_back(P.x);
			torusPoints.push_back(P.y);
			torusPoints.push_back(P.z);
		}
	}

	return torusPoints;
}

Vec3 Primitives::torus(float u, float v)
{
	float r1 = 2.0f;
	float r0 = 4.0f;
	Vec3 p;
	p.x = cos(u) * (r0 + r1 * cos(v));
	p.y = sin(u) * (r0 + r1 * cos(v));
	p.z = r1 * sin(v);
	return p;
}