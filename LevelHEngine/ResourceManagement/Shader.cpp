#include "Shader.h"

#include "FileLoader.h"
#include "../Core/Logging.h"

Shader::Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	//initialise the shader program
	shaderProgram = glCreateProgram();

	//initialise the vertex shader
	initaliseShader(vertexShaderFileName, 'v');

	//initialise the fragment shader
	initaliseShader(fragmentShaderFileName, 'f');

	//link the shaders together in the shader program
	glLinkProgram(shaderProgram);

	//Create a variable for testing the linking of the shaders
	GLint linked;
	//initialise the test variable
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

	//Check that the link was successful
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(shaderProgram, len, &len, log);
		Logging::logE("ERROR: Shader linking failed: " + std::string(log));
		delete[] log;

		//quit the function
		return;
	}

	//Get the location of the uniforms in the shaders
	shaderModelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMat");
	shaderViewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMat");
	shaderProjectionMatrixLocation = glGetUniformLocation(shaderProgram, "projMat");

	//if the shader is a texture shader then get the texture
	if (vertexShaderFileName == "2d.texture" || vertexShaderFileName == "texture")
	{
		textureSamplerLocation = glGetUniformLocation(shaderProgram, "textureSampler");
	}
}

Shader::~Shader()
{
}

void Shader::initaliseShader(std::string shaderFileName, char shaderType)
{
	//create a shader
	GLuint shader = 0;

	//Create the shader using the shader type
	switch (shaderType)
	{
	case 'v':
		//initialise the shader as a vertex shader
		shader = glCreateShader(GL_VERTEX_SHADER);
		//set the type of the shader to vs.
		shaderFileName = "vs." + shaderFileName;
		break;

	case 'f':
		//initialise the shader as a fragment shader
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		//set the type of the shader to fs.
		shaderFileName = "fs." + shaderFileName;
		break;
	}

	//load in the shader file
	std::string shaderFile = FileLoader::loadShaderFile(shaderFileName);
	//set the vertex shader code
	const GLchar *shaderCode = shaderFile.c_str();
	
	//Give OpenGL the source code for it
	glShaderSource(shader, 1, &shaderCode, NULL);
	//Compile the shader
	glCompileShader(shader);

	//Check if the shader compiled
	if (!CheckShaderCompiled(shader))
	{
		//output the shader that failed to compile
		Logging::logE(shaderFileName + " Failed to compile.");
		//quit the function
		return;
	}

	//link the shader to the shader Program
	glAttachShader(shaderProgram, shader);
}

bool Shader::CheckShaderCompiled(GLint shader)
{
	//Create a variable for testing the if the shader complied
	GLint compiled;
	//initialise the test variable
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	//Check if the shader compiled
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		//OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		Logging::logE("ERROR: Shader compilation failed: " + std::string(log));
		delete[] log;

		//the shader did not compile
		return false;
	}

	//the shader compiled
	return true;
}

GLuint Shader::getShaderProgram()
{
	//return the shader program
	return shaderProgram;
}

GLint Shader::getModelMatrixLocation()
{
	//return the shader model matrix location
	return shaderModelMatrixLocation;
}

GLint Shader::getViewMatrixLocation()
{
	//return the shader view matrix location
	return shaderViewMatrixLocation;
}

GLint Shader::getShaderProjectionMatrixLocation()
{
	//return the shader projection matrix location
	return shaderProjectionMatrixLocation;
}

GLint Shader::getTextureSamplerLocation()
{
	//return the texture sampler location
	return textureSamplerLocation;
}