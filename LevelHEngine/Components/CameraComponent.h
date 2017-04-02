#pragma once

#include "../Maths/Mat4.h"
#include "Component.h"

/**
@brief Creates a Camera component.
*/
class CameraComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~CameraComponent();

	/**
	@brief Returns the Camera projection matrix.
	@returns The Camera projection matrix.
	*/
	Mat4 getProjection();

	/**
	@brief Returns the Z depth for the Camera.
	@returns The Z depth for the Camera.
	*/
	float getZDepth();

	/**
	@brief Returns the Camera orthogonal projection matrix.
	@returns The Camera orthogonal projection matrix.
	*/
	float* getOrthoProjection();

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

private:
	///Construct a projection matrix for the Camera (Camera lense)
	Mat4 projection;
	
	///The Z depth for the camera
	float zDepth;
};