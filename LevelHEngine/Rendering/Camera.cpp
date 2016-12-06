#include "Camera.h"

Camera::Camera()
{
	//initialise the view matrix for the camera
	view.setAsIdentityMatrix();
	view.translate(view, Maths::Vec3(0.0f, 0.0f, 0.0f));

	//initialise the projection matrix for the camera (camera lense)
	projection.setAsPerspectiveMatrix(45.0f, Core::WindowFrame::getAspect(), 0.1f, 200.0f);

	//initialise the orientation
	orientation = Maths::Vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

// void Camera::lookAt(Maths::Vec3 targetPos)
// {
// 	Maths::Vec3 upDir(0.0f, 1.0f, 0.0f);
// 	Maths::Vec3 cameraPos = targetPos;
// 	cameraPos.z += 2.0f;
// 
// 	targetPos.z -= 2.0f;
// 
// 	view.lookAt(cameraPos, targetPos, upDir);
// }

void Camera::moveCamera(Maths::Vec3 translation)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view.translate(view, -translation);
}

void Camera::moveCameraAlongX(float translateX)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view.translate(view, Maths::Vec3(-translateX, 0.0f, 0.0f));
}

void Camera::moveCameraAlongY(float translateY)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view.translate(view, Maths::Vec3(0.0f, -translateY, 0.0f));
}

void Camera::moveCameraAlongZ(float translateZ)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view.translate(view, Maths::Vec3(0.0f, 0.0f, -translateZ));
}

void Camera::rotateCamera(Maths::Vec3 rotation)
{
	//Rotates the Camera
	view.rotateAlongX(view, rotation.x);
	view.rotateAlongY(view, rotation.y);
	view.rotateAlongZ(view, rotation.z);
	//update the stored orientation
	orientation = rotation;
}

void Camera::rotateCameraAlongX(float rotationX)
{
	//Rotates the Camera along the X axis
	view.rotateAlongX(view, rotationX);
	//update the stored orientation
	orientation.x = rotationX;
}

void Camera::rotateCameraAlongY(float rotationY)
{
	//Rotates the Camera along the Y axis
	view.rotateAlongY(view, rotationY);
	//update the stored orientation
	orientation.y = rotationY;
}

void Camera::rotateCameraAlongZ(float rotationZ)
{
	//Rotates the Camera along the Z axis
	view.rotateAlongZ(view, rotationZ);
	//update the stored orientation
	orientation.z = rotationZ;
}

Maths::Mat4 Camera::getView()
{
	//return the Camera view matrix
	return view;
}

Maths::Mat4 Camera::getProjection()
{
	//return the Camera projection matrix
	return projection;
}

Maths::Vec3 Camera::getOrientation()
{
	//return the Camera orientation
	return orientation;
}

void Camera::setPosition(Maths::Vec3 position)
{
	//set the position
	view.setPos(view, position);
}