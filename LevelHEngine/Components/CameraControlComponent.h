#pragma once

#include "../Maths/Vec3.h"
#include "Component.h"

/**
@brief Creates a Camera Control component.
*/
class CameraControlComponent : public Component
{
public:

	/**
	@brief A virtual destructor.
	*/
	virtual ~CameraControlComponent();

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

	/**
	@brief A function to handle the input for the camera
	*/
	void handleInput();

	/**
	@brief A function to update the camera
	*/
	void updateCamera(float dt);

	/**
	@brief A function to set the speed of the camera
	*/
	void setSpeed(float inSpeed);

	/**
	@brief A function to set the rotation speed of the camera
	*/
	void setRotateSpeed(float inRotateSpeed);

private:
	///The movment speed
	float speed;
	///The rotation speed
	float rotateSpeed;
	///The velocities for the movment of the camera
	Vec3 movementVel;
	Vec3 rotationVel;
};