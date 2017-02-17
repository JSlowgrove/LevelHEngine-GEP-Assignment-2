#pragma once

#include <string>
#include "GL/glew.h"

/**
@brief Creates a Shader from an text file, this can then be used with OpenGL.
*/
class Shader
{
public:
	/**
	@brief Creates a Shader Object using an shader file location and OpenGL.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	*/
	Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	/**
	@brief Destructs the Shader Object deleting the Shader Object from memory.
	*/
	~Shader();

	/**
	@brief Returns the shader program.
	@returns The shader program.
	*/
	GLuint getShaderProgram();

	/**
	@brief Returns the shader model matrix location.
	@returns The shader model matrix location.
	*/
	GLint getModelMatrixLocation();

	/**
	@brief Returns the shader view matrix location.
	@returns The shader view matrix location.
	*/
	GLint getViewMatrixLocation();

	/**
	@brief Returns the shader projection matrix location.
	@returns The shader projection matrix location.
	*/
	GLint getShaderProjectionMatrixLocation();

	/**
	@brief Returns the texture sampler location.
	@returns The texture sampler location.
	*/
	GLint getTextureSamplerLocation();

private:
	///The Shader program of the Shader Object
	GLuint shaderProgram;
	///The Uniform locations for the shader program
	GLint shaderModelMatrixLocation, shaderViewMatrixLocation, shaderProjectionMatrixLocation, textureSamplerLocation;

	/**
	@brief A function to test if the shader compiled successfully.
	@param shader The shader to test.
	@returns If the shader compiled successfully.
	*/
	bool Shader::CheckShaderCompiled(GLint shader);

	/**
	@brief Initialise a shader.
	@param shaderFileName The name of the shader file.
	@param shaderType The type of the shader.
	*/
	void initaliseShader(std::string shaderFileName, char shaderType);
};