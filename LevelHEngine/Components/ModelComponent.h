#pragma once

#include "../ResourceManagement/Primitives.h"
#include "Component.h"

/**
@brief A class that handles the model component.
*/
class ModelComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~ModelComponent();

	/**
	@brief A function for the model render.
	*/
	void onRender();

	void initaliseHeightmap(std::string fileName);

	void initalisePrimitive(Primitives::PrimativeType primType);

	void initaliseHeightmap(std::string fileName, std::string textureFileName);

	/**
	@brief A function to initalise a mesh without a texture.
	@param objFileName The obj file for the mesh.
	*/
	void initaliseMesh(std::string objFileName);

	/**
	@brief A function to initalise a mesh with a texture.
	@param objFileName The obj file for the mesh.
	@param textureFileName The name of the texture file.
	*/
	void initaliseMesh(std::string objFileName, std::string textureFileName);

	/**
	@brief A function to initalise the shaders to use with the mesh.
	@param vertexShaderFileName The vertex shader to use.
	@param fragmentShaderFileName The fragment shader to use.
	*/
	void initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	/**
	@brief A function to get the mesh ID.
	@returns The ID of the mesh.
	*/
	std::string getMeshID() { return meshID; }

	/**
	@brief A virtual function for the componets awake.
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy.
	*/
	virtual void onDestroy();

private:
	///The Shader for the Model
	std::string shaderID;
	///The mesh for the Model
	std::string meshID;
	///A boolean for if textured
	bool textured;

	void bindTextures();
	void drawWithVerticies();
	void drawWithPoints();
	void drawWithIndices();
};