#include "Scaling.h"

#include "MathsDefs.h"

Vec2 Scaling::scaleVec2(Vec2 vector, int scale)
{
	//A variable for the new Vector
	Vec2 newVector;

	//A variable for the percentage difference
	float percentageDifference = (float)scale - 480.0f;
	percentageDifference = (percentageDifference / 480.0f) * 100.0f;

	//A variable for one percent of the original size of the width
	float onePercent = vector.x / 100.0f;

	//get the difference
	float difference = onePercent * percentageDifference;

	//get the new x value of the vector
	newVector.x = vector.x + difference;

	//A variable for one percent of the original size of the height
	onePercent = vector.y / 100.0f;

	//get the difference
	difference = onePercent * percentageDifference;

	//get the new y value of the vector
	newVector.y = vector.y + difference;

	//return the new vector
	return newVector;
}

float Scaling::scaleNumber(float number, int screenHeight)
{
	//A variable for the new number
	float newNumber;

	//A variable for the percentage difference
	float percentageDifference = (float)screenHeight - 480.0f;
	percentageDifference = (percentageDifference / 480.0f) * 100.0f;

	//A variable for one percent of the original size
	float onePercent = number / 100.0f;

	//get the difference
	float difference = onePercent * percentageDifference;

	//get the new value of the number
	newNumber = number + difference;

	//return the new number
	return newNumber;
}