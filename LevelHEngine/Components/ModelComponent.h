#pragma once

#include <iostream>
#include <unordered_map>
#include "GL/glew.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Maths/Mat4.h"
#include "Component.h"

/**
@brief A class that handles the model component.
*/
class ModelComponent : public Component
{
public:
	virtual ~ModelComponent();

	void onRender();
	void initaliseMesh(std::string objFileName);
	void initaliseMesh(std::string objFileName, std::string textureFileName);
	void initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	void setRenderMats(Mat4 viewMatrix, Mat4 projMatrix, Mat4 matrix)
	{
		this->viewMatrix = viewMatrix;
		this->projMatrix = projMatrix;
		this->matrix = matrix;
	}

	virtual void onAwake();
	virtual void onDestroy();
private:
	///The Shader for the Model
	std::string shaderID;
	///The mesh for the Model
	std::string meshID;
	///A boolean for if textured
	bool textured;
	///The projection matrix to render with
	Mat4 projMatrix;
	///The view matrix to render with
	Mat4 viewMatrix;
	///The object matrix to render with
	Mat4 matrix;

	
};