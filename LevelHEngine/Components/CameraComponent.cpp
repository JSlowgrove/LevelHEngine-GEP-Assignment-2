#include "CameraComponent.h"

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