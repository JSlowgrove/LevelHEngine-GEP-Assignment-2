#include "ModelComponent.h"

ModelComponent::~ModelComponent()
{
}

void ModelComponent::onAwake()
{		
}

void ModelComponent::onDestroy()
{
}

void ModelComponent::render()
{
	/*Activate the shader program*/
	glUseProgram(ResourceManager::getShaders(shaderID)->getShaderProgram());

	/*Activate the vertex array object*/
	glBindVertexArray(ResourceManager::getMesh(meshID)->getVAO());

	/*Send the matrices to the shader as uniforms locations*/
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getModelMatrixLocation(), 1, GL_TRUE, matrix.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getViewMatrixLocation(), 1, GL_TRUE, viewMatrix.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getShaderProjectionMatrixLocation(), 1, GL_TRUE, projMatrix.getMatrixArray());

	/*if the model uses a shader*/
	if (!textured)
	{
		/*texturing*/
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ResourceManager::getMesh(meshID)->getTextureID());
		glUniform1i(ResourceManager::getShaders(shaderID)->getTextureSamplerLocation(), 0);
	}

	/*Draw the model to the screen, using the type of geometry and the number of vertices's*/
	glDrawArrays(GL_TRIANGLES, 0, ResourceManager::getMesh(meshID)->getNumberOfVertices());

	/*Unbind the vertex array object*/
	glBindVertexArray(0);

	/*disable the shader program*/
	glUseProgram(0);
}

void ModelComponent::initaliseMesh(std::string objFileName)
{
	meshID = ResourceManager::initialiseMesh(objFileName);
	textured = false;
}
void ModelComponent::initaliseMesh(std::string objFileName, std::string textureFileName)
{
	meshID = ResourceManager::initialiseMesh(objFileName, textureFileName);
	textured = true;
}

void ModelComponent::initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	shaderID = ResourceManager::initialiseShader(vertexShaderFileName, fragmentShaderFileName);
}