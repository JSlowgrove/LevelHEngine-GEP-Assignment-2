#include "M_Convert.h"

namespace M_Convert
{
	float convertDegreeToRadian(float angle)
	{
		return (angle * M_PI / 180.0f);
	}

	float convertRadianToDegree(float angle)
	{
		return (angle * 180.0f / M_PI);
	}
}