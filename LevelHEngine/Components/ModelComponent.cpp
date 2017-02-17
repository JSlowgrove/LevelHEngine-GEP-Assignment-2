#include "ModelComponent.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Mat4.h"

ModelComponent::~ModelComponent()
{
}

void ModelComponent::onAwake()
{
	id = "model";
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
		bindTextures();
	}

	if (ResourceManager::getMesh(meshID)->checkHeightmap())
	{
		drawWithIndices();
	}
	else if (ResourceManager::getMesh(meshID)->checkPrimitive())
	{
		drawWithPoints();
	}
	else
	{
		drawWithVerticies();
	}
	
	/*Unbind the vertex array object*/
	glBindVertexArray(0);

	/*disable the shader program*/
	glUseProgram(0);
}

void ModelComponent::initaliseHeightmap(std::string fileName)
{
	meshID = ResourceManager::initialiseHeightmap(fileName);
	textured = false;
}

void ModelComponent::initalisePrimitive(Primitives::PrimativeType primType)
{
	meshID = ResourceManager::initialisePrimitive(primType);
	textured = false;
}

void ModelComponent::initaliseHeightmap(std::string fileName, std::string textureFileName)
{
	meshID = ResourceManager::initialiseHeightmap(fileName, textureFileName);
	textured = true;
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

void ModelComponent::bindTextures()
{
	/*texturing*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getMesh(meshID)->getTextureID());
	glUniform1i(ResourceManager::getShaders(shaderID)->getTextureSamplerLocation(), 0);
}

void ModelComponent::drawWithVerticies()
{
	/*Draw the model to the screen, using the type of geometry and the number of vertices's*/
	glDrawArrays(GL_TRIANGLES, 0, ResourceManager::getMesh(meshID)->getNumberOfVertices());
}

void ModelComponent::drawWithPoints()
{
	/*Draw the model to the screen, using the type of geometry and the number of vertices's*/
	glDrawArrays(GL_POINTS, 0, ResourceManager::getMesh(meshID)->getNumberOfVertices());
}

void ModelComponent::drawWithIndices()
{
	glDrawElements(GL_TRIANGLES, ResourceManager::getMesh(meshID)->getNumIndices(), GL_UNSIGNED_INT, (void*)0);
}