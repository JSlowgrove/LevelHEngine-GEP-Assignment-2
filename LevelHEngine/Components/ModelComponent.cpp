#include "ModelComponent.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Mat4.h"
#include "../Core/Logging.h"

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
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getUniform("modelMat"), 1, GL_TRUE, model.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getUniform("viewMat"), 1, GL_TRUE, view.getMatrixArray());
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getUniform("projMat"), 1, GL_TRUE, projection.getMatrixArray());

	/*if the model uses a texture*/
	if (textured)
	{
		bindTextures();
	}

	if (colour)
	{
		glUniform3f(ResourceManager::getShaders(shaderID)->getUniform("diffuseColour"), diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(ResourceManager::getShaders(shaderID)->getUniform("ambientColour"), ambient.x, ambient.y, ambient.z);
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
	colour = textured = false;
	diffuse = ambient = Vec3(0.0f, 0.0f, 0.0f);
}

void ModelComponent::initalisePrimitive(Primitives::PrimativeType primType)
{
	meshID = ResourceManager::initialisePrimitive(primType);
	colour = textured = false;
	diffuse = ambient = Vec3(0.0f, 0.0f, 0.0f);
}

void ModelComponent::initaliseHeightmap(std::string fileName, std::string textureFileName)
{
	meshID = ResourceManager::initialiseHeightmap(fileName, textureFileName);
	textured = true;
	colour = false;
	diffuse = ambient = Vec3(0.0f, 0.0f, 0.0f);
}

void ModelComponent::initaliseMesh(std::string objFileName)
{
	meshID = ResourceManager::initialiseMesh(objFileName);
	colour = textured = false;
	diffuse = ambient = Vec3(0.0f, 0.0f, 0.0f);
}

void ModelComponent::initaliseMesh(std::string objFileName, std::string textureFileName)
{
	meshID = ResourceManager::initialiseMesh(objFileName, textureFileName);
	textured = true;
	colour = false;
	diffuse = ambient = Vec3(0.0f, 0.0f, 0.0f);
}

void ModelComponent::initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	shaderID = ResourceManager::initialiseShader(vertexShaderFileName, fragmentShaderFileName);
	
	if (meshID == "")
	{
		Logging::logE("Model Mesh MUST be initalised BEFORE the Shaders!!!");
	}

	//initalise uniforms
	initaliseUniforms();
}

void ModelComponent::initaliseShaders(std::string vertexShaderFileName, float inR, float inG, float inB)
{
	colour = true;
	shaderID = ResourceManager::initialiseShader(vertexShaderFileName, "colour");

	if (meshID == "")
	{
		Logging::logE("Model Mesh MUST be initalised BEFORE the Shaders!!!");
	}

	diffuse.x = inR;
	diffuse.y = inG;
	diffuse.z = inB;

	ambient = Vec3(0.0f, 0.0f, 0.0f);

	//initalise uniforms
	initaliseUniforms();
}

void ModelComponent::initaliseShaders(std::string vertexShaderFileName, Vec3 inDiffuse, Vec3 inAmbient)
{
	colour = true;
	shaderID = ResourceManager::initialiseShader(vertexShaderFileName, "colour");

	if (meshID == "")
	{
		Logging::logE("Model Mesh MUST be initalised BEFORE the Shaders!!!");
	}

	diffuse = inDiffuse;

	ambient = inAmbient;

	//initalise uniforms
	initaliseUniforms();
}

void ModelComponent::initaliseDefaultColourShaders(std::string vertexShaderFileName, std::string inColour)
{
	colour = true;
	shaderID = ResourceManager::initialiseShader(vertexShaderFileName, "colour");

	if (meshID == "")
	{
		Logging::logE("Model Mesh MUST be initalised BEFORE the Shaders!!!");
	}

	if (inColour == "default")
	{
		ambient = Vec3(0.1f, 0.1f, 0.2f);
		diffuse = Vec3(0.8f, 0.1f, 0.1f);
	}
	if (inColour == "black")
	{
		ambient = Vec3(0.0f, 0.0f, 0.0f);
		diffuse = Vec3(1.0f, 1.0f, 1.0f);
	}
	if (inColour == "blue")
	{
		ambient = Vec3(0.1f, 0.1f, 0.2f);
		diffuse = Vec3(0.0f, 0.1f, 0.8f);
	}
	if (inColour == "cyan")
	{
		ambient = Vec3(0.1f, 0.2f, 0.2f);
		diffuse = Vec3(0.0f, 0.8f, 0.8f);
	}
	if (inColour == "green")
	{
		ambient = Vec3(0.1f, 0.1f, 0.1f);
		diffuse = Vec3(0.0f, 0.8f, 0.1f);
	}
	if (inColour == "lightgrey")
	{
		ambient = Vec3(0.2f, 0.2f, 0.2f);
		diffuse = Vec3(0.7f, 0.7f, 0.7f);
	}
	if (inColour == "magenta")
	{
		ambient = Vec3(0.2f, 0.1f, 0.2f);
		diffuse = Vec3(0.8f, 0.1f, 0.8f);
	}
	if (inColour == "red")
	{
		ambient = Vec3(1.0f, 0.0f, 0.0f);
		diffuse = Vec3(1.0f, 0.0f, 0.0f);
	}
	if (inColour == "white")
	{
		ambient = Vec3(0.2f, 0.2f, 0.2f);
		diffuse = Vec3(1.0f, 1.0f, 1.0f);
	}
	if (inColour == "yellow")
	{
		ambient = Vec3(0.2f, 0.2f, 0.0f);
		diffuse = Vec3(0.8f, 0.8f, 0.0f);
	}

	//initalise uniforms
	initaliseUniforms();
}

void ModelComponent::addUniform(std::string uniformID)
{
	ResourceManager::getShaders(shaderID)->initaliseUniform(uniformID);
}

void ModelComponent::initaliseUniforms()
{
	ResourceManager::getShaders(shaderID)->initaliseUniform("modelMat");
	ResourceManager::getShaders(shaderID)->initaliseUniform("viewMat");
	ResourceManager::getShaders(shaderID)->initaliseUniform("projMat");

	if (textured)
	{
		ResourceManager::getShaders(shaderID)->initaliseUniform("textureSampler");
	}
	if (colour)
	{
		ResourceManager::getShaders(shaderID)->initaliseUniform("diffuseColour");
		ResourceManager::getShaders(shaderID)->initaliseUniform("ambientColour");
	}
}

void ModelComponent::bindTextures()
{
	/*texturing*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getMesh(meshID)->getTextureID());
	glUniform1i(ResourceManager::getShaders(shaderID)->getUniform("textureSampler"), 0);
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