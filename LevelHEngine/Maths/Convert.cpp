#include "Convert.h"

#include "MathsDefs.h"
#include "../Core/WindowFrame.h"
#include "../Core/Application.h"
#include "../Components/CameraComponent.h"

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

	Vec2 convertToOpenGLCoords(Vec2 inVec)
	{
		//get the screen dimensions
		Vec2 screenDim = WindowFrame::getWindowRes();

		/*opengl coordinates
		-1.0,1.0  -> 1.0, 1.0
		|					|
		-1.0,-1.0 -> 1.0,-1.0*/

		//convert the position to a number between 0 and 1
		float newX = Convert::normaliseFloat(inVec.x, screenDim.x, 0.0f);
		//double to get the range between 0 and 2
		newX *= 2.0f;
		//minus 1 to get the number between -1 and 1
		newX -= 1.0f;

		//convert the position to a number between 0 and 1
		float newY = Convert::normaliseFloat(inVec.y, screenDim.y, 0.0f);
		//double to get the range between 0 and 2
		newY *= 2.0f;
		//minus 1 to get the number between -1 and 1
		newY -= 1.0f;
		//invert the x coordinate to work with opengl coords
		newY = -newY;

		return Vec2(newX, newY);
	}

	Vec2 scaleToOpenGLCoords(Vec2 inVec)
	{
		//get the screen dimensions
		Vec2 screenDim = WindowFrame::getWindowRes();

		/*opengl coordinates
		-1.0,1.0  -> 1.0, 1.0
		|					|
		-1.0,-1.0 -> 1.0,-1.0*/

		//convert the position to a number between 0 and 1
		float newX = Convert::normaliseFloat(inVec.x, screenDim.x, 0.0f);
		//double to get the range between 0 and 2
		newX *= 2.0f;

		//convert the position to a number between 0 and 1
		float newY = Convert::normaliseFloat(inVec.y, screenDim.y, 0.0f);
		//double to get the range between 0 and 2
		newY *= 2.0f;

		return Vec2(newX, newY);
	}

	Vec3 scaleToOpenGLCoords(Vec3 inVec)
	{
		//get the screen dimensions
		Vec2 screenDim = WindowFrame::getWindowRes();
		auto camera = Application::getCamera();
		float zDepth = camera->getComponent<CameraComponent>().lock()->getZDepth();

		/*opengl coordinates
		-1.0,1.0  -> 1.0, 1.0
		|					|
		-1.0,-1.0 -> 1.0,-1.0*/

		//convert the position to a number between 0 and 1
		float newX = Convert::normaliseFloat(inVec.x, screenDim.x, 0.0f);
		//double to get the range between 0 and 2
		newX *= 2.0f;

		//convert the position to a number between 0 and 1
		float newY = Convert::normaliseFloat(inVec.y, screenDim.y, 0.0f);
		//double to get the range between 0 and 2
		newY *= 2.0f;

		//convert the position to a number between 0 and 1
		float newZ = Convert::normaliseFloat(inVec.z, zDepth, 0.0f);
		//double to get the range between 0 and 2
		newZ *= 2.0f;

		return Vec3(newX, newY, newZ);
	}

}