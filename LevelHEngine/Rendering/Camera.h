#pragma once

#include <SDL.h>
#include <iostream>
#include "GL/glew.h"
#include "../Maths/Vec3.h"
#include "../Maths/Mat4.h"
#include "../Core/WindowFrame.h"

/**
@brief Creates a Camera object.
*/
class Camera
{
public:
	/**
	@brief Constructs a Camera object.
	*/
	Camera();

	/**
	@brief Destructs an Camera object.
	*/
	~Camera();

	/**
	@brief Updates the view matrix to look at targetPos.
	@param targetPos Target position.
	*/
	//void lookAt(Maths::Vec3 targetPos);
	//look at http://stackoverflow.com/questions/21830340/understanding-glmlookat to do
	
	/**
	@brief Moves the Camera using the translation.
	@param translation The translation.
	*/
	void moveCamera(Maths::Vec3 translation);

	/**
	@brief Moves the Camera along the X axis.
	@param translateX The translation along the X axis.
	*/
	void moveCameraAlongX(float translateX);

	/**
	@brief Moves the Camera along the Y axis.
	@param translateY The translation along the Y axis.
	*/
	void moveCameraAlongY(float translateY);

	/**
	@brief Moves the Camera along the Z axis.
	@param translateZ The translation along the Z axis.
	*/
	void moveCameraAlongZ(float translateZ);

	/**
	@brief Rotates the Camera using the rotation.
	@param rotation The rotation.
	*/
	void rotateCamera(Maths::Vec3 rotation);

	/**
	@brief Rotate the Camera along the X axis.
	@param rotationX The rotation along the X axis.
	*/
	void rotateCameraAlongX(float rotationX);

	/**
	@brief Rotate the Camera along the Y axis.
	@param rotationY The rotation along the Y axis.
	*/
	void rotateCameraAlongY(float rotationY);

	/**
	@brief Rotate the Camera along the Z axis.
	@param rotationZ The rotation along the Z axis.
	*/
	void rotateCameraAlongZ(float rotationZ);

	/**
	@brief Returns the Camera view matrix.
	@returns The Camera view matrix.
	*/
	Maths::Mat4 getView();

	/**
	@brief Returns the Camera projection matrix.
	@returns The Camera projection matrix.
	*/
	Maths::Mat4 getProjection();

	/**
	@brief Returns the Camera orientation.
	@returns The Camera orientation.
	*/
	Maths::Vec3 getOrientation();

	/**
	@brief Sets the position of the Camera.
	@param position The new position.
	*/
	void setPosition(Maths::Vec3 position);

private:
	///Create a viewing matrix for the Camera (Camera orientation)
	Maths::Mat4 view;
	///Construct a projection matrix for the Camera (Camera lense)
	Maths::Mat4 projection;
	///The Orientation of the Camera
	Maths::Vec3 orientation;
};