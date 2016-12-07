#include "CameraComponent.h"

namespace Rendering
{

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::onAwake()
	{
		//initialise the projection matrix for the camera (camera lense)
		projection.setAsPerspectiveMatrix(45.0f, Core::WindowFrame::getAspect(), 0.1f, 200.0f);
	}

	void CameraComponent::onDestroy()
	{
	}

	Maths::Mat4 CameraComponent::getProjection()
	{
		//return the Camera projection matrix
		return projection;
	}

}//End of rendering namespace