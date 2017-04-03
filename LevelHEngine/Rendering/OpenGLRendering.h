#pragma once

#include <string>
#include "GL/glew.h"
#include "../Maths/Vec3.h"
#include "../Maths/Vec2.h"

/**
@brief A namespace for handeling the openGLFunctions.
*/
namespace OpenGLRendering
{
	/**
	@brief A function to generate vertex arrays.
	@param numOfArrays The number of array to generate.
	@param VAO A pointer to the vertex array object.
	*/
	void generateVertexArrays(GLsizei numOfArrays, GLuint* VAO);

	/**
	@brief A function to activate a shader program.
	@param shaderID The shader to activate.
	*/
	void activateShaderProgram(std::string shaderID);

	/**
	@brief A function to activate a mesh vertex array object.
	@param meshId The mesh to activate.
	*/
	void activateMeshVAO(std::string meshID);

	/**
	@brief Activate a matrix 4 uniform.
	@param shaderID The shader.
	@param uniformID The uniform.
	@param matPointer A pointer to the matrix.
	*/
	void activateMat4Uniform(std::string shaderID, std::string uniformID, float* matPointer);

	/**
	@brief Activate a Vec 3 uniform.
	@param shaderID The shader.
	@param uniformID The uniform.
	@param Vec3 The vector to activate.
	*/
	void activateVec3Uniform(std::string shaderID, std::string uniformID, Vec3 vec);

	/**
	@brief Activate a Vec 2 uniform.
	@param shaderID The shader.
	@param uniformID The uniform.
	@param Vec3 The vector to activate.
	*/
	void activateVec2Uniform(std::string shaderID, std::string uniformID, Vec2 vec);

	/**
	@brief Unbond a vertex array object.
	*/
	void unbindVAO();

	/**
	@brief Disable a shader program.
	*/
	void disableShaderProgram();

	/**
	@brief A function to bind textures.
	@param uniformID The uniform.
	@param shaderID The shader.
	*/
	void bindTextures(std::string meshID, std::string shaderID);

	/**
	@brief A function to bind a vertex array.
	@param VAO A pointer to the vertex array object.
	*/
	void bindVertexArray(GLuint VAO);

	/**
	@brief A function to draw a mesh with verticies.
	@param meshId The mesh to activate.
	*/
	void drawWithVerticies(std::string meshID);

	/**
	@brief A function to draw a mesh with points.
	@param meshId The mesh to activate.
	*/
	void drawWithPoints(std::string meshID);

	/**
	@brief A function to draw a mesh with lines.
	@param meshId The mesh to activate.
	*/
	void drawWithLines(std::string meshID);

	/**
	@brief A function to draw a mesh with indicies.
	@param meshId The mesh to activate.
	*/
	void drawWithIndices(std::string meshID);
}