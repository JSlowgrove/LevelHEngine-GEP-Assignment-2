#include "Convert.h"

#include "MathsDefs.h"
#include "../Core/WindowFrame.h"

namespace Convert
{
	float normaliseFloat(float numToNormalise, float maxNum, float minNum)
	{
		return (numToNormalise - minNum) / (maxNum - minNum);
	}

	float convertDegreeToRadian(float angle)
	{
		return (angle * PI / 180.0f);
	}

	float convertRadianToDegree(float angle)
	{
		return (angle * 180.0f / PI);
	}

	Vec2 convertToOpenGLCoordinate(Vec2 coordinates)
	{
		//convert to openGL coordinates
		coordinates.x *= 0.01f;
		coordinates.y *= 0.01f;
		coordinates.x = coordinates.x - 1;
		coordinates.y = coordinates.y - 1;

		//flip the object along the y
		coordinates.y *= -1;

		//return the new coordinates
		return coordinates;
	}

}