#include "OpenGLRendering.h"

#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"

void OpenGLRendering::activateShaderProgram(std::string shaderID)
{
	glUseProgram(ResourceManager::getShaders(shaderID)->getShaderProgram());
}

void OpenGLRendering::activateMeshVAO(std::string meshID)
{
	glBindVertexArray(ResourceManager::getMesh(meshID)->getVAO());
}

void OpenGLRendering::activateMat4Uniform(std::string shaderID, std::string uniformID, float* matPointer)
{
	glUniformMatrix4fv(ResourceManager::getShaders(shaderID)->getUniform(uniformID), 1, GL_TRUE, matPointer);
}

void OpenGLRendering::activateVec3Uniform(std::string shaderID, std::string uniformID, Vec3 vec)
{
	glUniform3f(ResourceManager::getShaders(shaderID)->getUniform(uniformID), vec.x, vec.y, vec.z);
}

void OpenGLRendering::activateVec2Uniform(std::string shaderID, std::string uniformID, Vec2 vec)
{
	glUniform2f(ResourceManager::getShaders(shaderID)->getUniform(uniformID), vec.x, vec.y);
}


void OpenGLRendering::unbindVAO()
{
	glBindVertexArray(0);
}

void OpenGLRendering::disableShaderProgram()
{
	glUseProgram(0);
}

void OpenGLRendering::bindTextures(std::string meshID, std::string shaderID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getMesh(meshID)->getTextureID());
	glUniform1i(ResourceManager::getShaders(shaderID)->getUniform("textureSampler"), 0);
}

void OpenGLRendering::drawWithVerticies(std::string meshID)
{
	//Draw the model to the screen, using the type of geometry and the number of vertices's
	glDrawArrays(GL_TRIANGLES, 0, ResourceManager::getMesh(meshID)->getNumberOfVertices());
}

void OpenGLRendering::drawWithPoints(std::string meshID)
{
	//Draw the model to the screen, using the type of geometry and the number of vertices's*/
	glDrawArrays(GL_POINTS, 0, ResourceManager::getMesh(meshID)->getNumberOfVertices());
}

void OpenGLRendering::drawWithIndices(std::string meshID)
{
	glDrawElements(GL_TRIANGLES, ResourceManager::getMesh(meshID)->getNumIndices(), GL_UNSIGNED_INT, (void*)0);
}