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

	std::string getMeshID() { return meshID; }

	virtual void onAwake();
	virtual void onDestroy();
private:
	///The Shader for the Model
	std::string shaderID;
	///The mesh for the Model
	std::string meshID;
	///A boolean for if textured
	bool textured;

	
};