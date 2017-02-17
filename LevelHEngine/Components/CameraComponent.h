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
	
};