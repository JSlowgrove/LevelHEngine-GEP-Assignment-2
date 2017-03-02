#include "ModelComponent.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Mat4.h"
#include "../Core/Logging.h"
#include "../Rendering/OpenGLRendering.h"

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

	//Activate the shader program
	OpenGLRendering::activateShaderProgram(shaderID);

	//Activate the vertex array object
	OpenGLRendering::activateMeshVAO(meshID);

	//Send the matrices to the shader as uniforms locations
	OpenGLRendering::activateMat4Uniform(shaderID, "modelMat", model.getMatrixArray());
	OpenGLRendering::activateMat4Uniform(shaderID, "viewMat", view.getMatrixArray());
	OpenGLRendering::activateMat4Uniform(shaderID, "projMat", projection.getMatrixArray());

	//loop through the mat4 uniforms
	for (auto i = mat4Uniforms.begin(); i != mat4Uniforms.end(); ++i)
	{
		OpenGLRendering::activateMat4Uniform(shaderID, i->first, i->second);
	}

	//loop through the vec3 uniforms
	for (auto i = vec3Uniforms.begin(); i != vec3Uniforms.end(); ++i)
	{
		OpenGLRendering::activateVec3Uniform(shaderID, i->first, i->second);
	}

	//if the model uses a texture
	if (textured)
	{
		OpenGLRendering::bindTextures(meshID, shaderID);
	}

	if (colour)
	{
		OpenGLRendering::activateVec3Uniform(shaderID, "diffuseColour", diffuse);
		OpenGLRendering::activateVec3Uniform(shaderID, "ambientColour", ambient);
	}

	if (ResourceManager::getMesh(meshID)->checkHeightmap())
	{
		OpenGLRendering::drawWithIndices(meshID);
	}
	else if (ResourceManager::getMesh(meshID)->checkPrimitive())
	{
		OpenGLRendering::drawWithPoints(meshID);
	}
	else
	{
		OpenGLRendering::drawWithVerticies(meshID);
	}
	
	//Unbind the vertex array object
	OpenGLRendering::unbindVAO();

	//disable the shader program
	OpenGLRendering::disableShaderProgram();
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

void ModelComponent::addMat4Uniform(std::string uniformID, float* matPointer)
{
	ResourceManager::getShaders(shaderID)->initaliseUniform(uniformID);
	//test if the uniform has not already been added
	if (mat4Uniforms.count(uniformID) == 0)
	{
		mat4Uniforms[uniformID] = matPointer;
	}
	else
	{
		//print out that it is already initalise
		Logging::logI(uniformID + " uniform already added.");
	}
}

void ModelComponent::addVec3Uniform(std::string uniformID, Vec3 vec)
{
	ResourceManager::getShaders(shaderID)->initaliseUniform(uniformID);
	//test if the uniform has not already been added
	if (vec3Uniforms.count(uniformID) == 0)
	{
		vec3Uniforms[uniformID] = vec;
	}
	else
	{
		//print out that it is already initalise
		Logging::logI(uniformID + " uniform already added.");
	}
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
