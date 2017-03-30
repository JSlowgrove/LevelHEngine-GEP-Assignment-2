#pragma once

#include <string>
#include "../Maths/Vec3.h"
#include "../Maths/Vec2.h"

namespace OpenGLRendering
{
	void activateShaderProgram(std::string shaderID);
	void activateMeshVAO(std::string meshID);
	void activateMat4Uniform(std::string shaderID, std::string uniformID, float* matPointer);
	void activateVec3Uniform(std::string shaderID, std::string uniformID, Vec3 vec);
	void activateVec2Uniform(std::string shaderID, std::string uniformID, Vec2 vec);
	void unbindVAO();
	void disableShaderProgram();
	void bindTextures(std::string meshID, std::string shaderID);
	void drawWithVerticies(std::string meshID);
	void drawWithPoints(std::string meshID);
	void drawWithIndices(std::string meshID);
}