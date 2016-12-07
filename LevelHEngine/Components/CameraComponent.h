#pragma once

#include <SDL.h>
#include <iostream>
#include "GL/glew.h"
#include "../Maths/Vec3.h"
#include "../Maths/Mat4.h"
#include "../Core/WindowFrame.h"
#include "Component.h"

/**
@brief Creates a Camera component.
*/
class CameraComponent : public Component
{
public:
	virtual ~CameraComponent();

	/**
	@brief Returns the Camera projection matrix.
	@returns The Camera projection matrix.
	*/
	Mat4 getProjection();

private:
	///Construct a projection matrix for the Camera (Camera lense)
	Mat4 projection;

	virtual void onAwake();
	virtual void onDestroy();
};