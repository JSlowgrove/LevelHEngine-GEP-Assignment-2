#pragma once

#include <SDL.h>
#include <iostream>
#include "GL/glew.h"
#include "../Maths/Vec3.h"
#include "../Maths/Mat4.h"
#include "../Core/Component.h"
#include "../Core/WindowFrame.h"

/**
@brief The namespace for all rendering code.
*/
namespace Rendering
{

	/**
	@brief Creates a Camera component.
	*/
	class CameraComponent : public Core::Component
	{
	public:
		virtual ~CameraComponent();

		/**
		@brief Returns the Camera projection matrix.
		@returns The Camera projection matrix.
		*/
		Maths::Mat4 getProjection();

	private:
		///Construct a projection matrix for the Camera (Camera lense)
		Maths::Mat4 projection;

		virtual void onAwake();
		virtual void onDestroy();
	};

}//End of rendering namespace