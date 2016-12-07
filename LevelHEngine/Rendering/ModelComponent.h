#pragma once

#include <iostream>
#include <unordered_map>
#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Mat4.h"
#include "../Core/Component.h"

/**
@brief The namespace for all rendering code.
*/
namespace Rendering
{

	/**
	@brief A class that handles the model component.
	*/
	class ModelComponent : public Core::Component
	{
	public:
		virtual ~ModelComponent();

		void render();
		void initaliseMesh(std::string objFileName);
		void initaliseMesh(std::string objFileName, std::string textureFileName);
		void initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);

		void setRenderMats(Maths::Mat4 viewMatrix, Maths::Mat4 projMatrix, Maths::Mat4 matrix)
		{
			this->viewMatrix = viewMatrix;
			this->projMatrix = projMatrix;
			this->matrix = matrix;
		}

	private:
		///The Shader for the Model
		std::string shaderID;
		///The mesh for the Model
		std::string meshID;
		///A boolean for if textured
		bool textured;
		///The projection matrix to render with
		Maths::Mat4 projMatrix;
		///The view matrix to render with
		Maths::Mat4 viewMatrix;
		///The object matrix to render with
		Maths::Mat4 matrix;

		virtual void onAwake();
		virtual void onDestroy();
	};

}//End of rendering namespace