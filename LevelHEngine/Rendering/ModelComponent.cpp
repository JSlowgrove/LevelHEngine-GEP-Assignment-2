#include "ModelComponent.h"

namespace Rendering
{

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
		glUseProgram(ResourceManagment::ResourceManager::getShaders(shaderID)->getShaderProgram());

		/*Activate the vertex array object*/
		glBindVertexArray(ResourceManagment::ResourceManager::getMesh(meshID)->getVAO());

		/*Send the matrices to the shader as uniforms locations*/
		glUniformMatrix4fv(ResourceManagment::ResourceManager::getShaders(shaderID)->getModelMatrixLocation(), 1, GL_TRUE, matrix.getMatrixArray());
		glUniformMatrix4fv(ResourceManagment::ResourceManager::getShaders(shaderID)->getViewMatrixLocation(), 1, GL_TRUE, viewMatrix.getMatrixArray());
		glUniformMatrix4fv(ResourceManagment::ResourceManager::getShaders(shaderID)->getShaderProjectionMatrixLocation(), 1, GL_TRUE, projMatrix.getMatrixArray());

		/*if the model uses a shader*/
		if (!textured)
		{
			/*texturing*/
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ResourceManagment::ResourceManager::getMesh(meshID)->getTextureID());
			glUniform1i(ResourceManagment::ResourceManager::getShaders(shaderID)->getTextureSamplerLocation(), 0);
		}

		/*Draw the model to the screen, using the type of geometry and the number of vertices's*/
		glDrawArrays(GL_TRIANGLES, 0, ResourceManagment::ResourceManager::getMesh(meshID)->getNumberOfVertices());

		/*Unbind the vertex array object*/
		glBindVertexArray(0);

		/*disable the shader program*/
		glUseProgram(0);
	}

	void ModelComponent::initaliseMesh(std::string objFileName)
	{
		meshID = ResourceManagment::ResourceManager::initialiseMesh(objFileName);
		textured = false;
	}
	void ModelComponent::initaliseMesh(std::string objFileName, std::string textureFileName)
	{
		meshID = ResourceManagment::ResourceManager::initialiseMesh(objFileName, textureFileName);
		textured = true;
	}

	void ModelComponent::initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
	{
		shaderID = ResourceManagment::ResourceManager::initialiseShader(vertexShaderFileName, fragmentShaderFileName);
	}

}//End of rendering namespace