#include "ModelComponent.h"

#include "TransformComponent.h"
#include "CameraComponent.h"

ModelComponent::~ModelComponent()
{
}

void ModelComponent::onAwake()
{		
}

void ModelComponent::onDestroy()
{
}

void ModelComponent::onRender()
{
	auto camera = Application::camera;
	Mat4 view = camera->getComponent<TransformComponent>().lock()->getTransformMat4();
	Mat4 projection = camera->getComponent<CameraComponent>().lock()->getProjection();

	Mat4 model = getGameObject().lock()->getComponent<TransformComponent>().lock()->getTransformMat4();

	/*Activate the shader program*/
	glUseProgram(ResourceManager::getShaders(shaderID)->getShaderProgram());

	/*Activate the vertex array object*/
	glBindVertexArray(ResourceManager::getMesh(meshID)->getVAO());

	/*Send the matrices to the shader as uniforms locations*/
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getModelMatrixLocation(), 1, GL_TRUE, model.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getViewMatrixLocation(), 1, GL_TRUE, view.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getShaderProjectionMatrixLocation(), 1, GL_TRUE, projection.getMatrixArray());

	/*if the model uses a texture*/
	if (textured)
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