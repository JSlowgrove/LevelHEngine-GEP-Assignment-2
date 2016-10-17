#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>
#include "GL/glew.h"
#include "RM_Shader.h"
#include "RM_Object.h"

/**
@brief Creates a Model from an object and a shader.
@author Jamie Slowgrove
*/
class RM_Model
{
private:
	/**The Shader for the Model*/
	RM_Shader* shader;
	/**The object for the Model*/
	RM_Object* obj;
	/**The Position of the Model*/
	glm::vec3 position;
	/**The matrix for the Model*/
	glm::mat4 matrix;
	/**The material name*/
	std::string material;

	/**
	Initialise the object for the Model.
	@param objFileName The name of the obj file.
	@param objects A reference to the loaded Object files
	*/
	void initialiseVAO(std::string objFileName, std::unordered_map<std::string, RM_Object*> &objects);

	/**
	Initialise the shaders.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	void initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName, 
		std::unordered_map<std::string, RM_Shader*> &shaders);

public:
	/**
	Constructs a Model Object.
	Creates a Model Object using the shader file locations, the obj file location and OpenGL.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param objFileName The name of the obj file.
	@param objects A reference to the loaded Object files
	@param shaders A reference to the loaded Shader files
	*/
	RM_Model(std::string vertexShaderFileName, std::string fragmentShaderFileName, std::string objFileName,
		std::unordered_map<std::string, RM_Object*> &objects, std::unordered_map<std::string, RM_Shader*> &shaders);

	/**
	Constructs a Model Object.
	Creates a Model Object using the shader file locations, the obj file location and OpenGL.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param objFileName The name of the obj file.
	@param objects A reference to the loaded Object files
	@param shaders A reference to the loaded Shader files
	@param material The name of the material to texture with.
	*/
	RM_Model(std::string vertexShaderFileName, std::string fragmentShaderFileName, std::string objFileName,
		std::unordered_map<std::string, RM_Object*> &objects, std::unordered_map<std::string, RM_Shader*> &shaders,
		std::string material);

	/**
	Destructs a Model Object.
	Destructs the Model Object deleting the Model Object from memory.
	*/
	~RM_Model();

	/**
	Draw the Model to the screen.
	@param viewMatrix A reference to the camera view matrix.
	@param projMatrix A reference to the camera projection matrix.
	*/
	void draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	/**
	Setter # Sets the position of the Model.
	@param position The new position.
	*/
	void setPosition(glm::vec3 position);

	/**
	Setter # Sets the position of the Model.
	@param x The X position.
	@param z The Y position.
	@param y The Z position.
	*/
	void setPosition(float x, float y, float z);

	/**
	Rotate the Model.
	@param rotation The rotation angles (Euler angles [Radians]).
	*/
	void rotate(glm::vec3 rotation);

	/**
	Rotate the Model along the X axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateX(float angle);
	
	/**
	Rotate the Model along the Y axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateY(float angle);

	/**
	Rotate the Model along the Z axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateZ(float angle);

	/**
	Scale the Model.
	@param scaleVector The new scale of the Model.
	*/
	void scale(glm::vec3 scaleVector);
};
