#include "CameraComponent.h"

#include <glm/gtc/type_ptr.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Core/WindowFrame.h"

CameraComponent::~CameraComponent()
{
}

void CameraComponent::onAwake()
{
	//initialise the projection matrix for the camera (camera lense)
	projection.setAsPerspectiveMatrix(45.0f, WindowFrame::getAspect(), 0.1f, 200.0f);
	id = "camera";
}

void CameraComponent::onDestroy()
{
}

Mat4 CameraComponent::getProjection()
{
	//return the Camera projection matrix
	return projection;
}

float* CameraComponent::getOrthoProjection()
{
	//return the Camera ortho projection matrix
	glm::mat4 projection = glm::ortho(0.0f, WindowFrame::getWindowRes().x, WindowFrame::getWindowRes().y, 0.0f, 0.0f, 1000.0f);
	return glm::value_ptr(projection);
}