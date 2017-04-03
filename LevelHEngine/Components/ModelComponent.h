#pragma once

#include "../ResourceManagement/Primitives.h"
#include "Component.h"
#include <unordered_map>

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

	/**
	@brief A function to initalise a mesh with a heightmap.
	@param fileName The image file for the heightmap.
	*/
	void initaliseHeightmap(std::string fileName);

	/**
	@brief A function to initalise a mesh using a primiative type.
	@param primType The primitive type for the mesh.
	*/
	void initalisePrimitive(Primitives::PrimativeType primType);

	/**
	@brief A function to initalise a mesh with a heightmap ad a texture.
	@param fileName The image file for the heightmap.
	@param textureFileName The name of the texture file.
	*/
	void initaliseHeightmap(std::string fileName, std::string textureFileName);

	/**
	@brief A function to add a matrix 4 uniform.
	@param uniformID The ID of the uniform.
	@param matPointer A pointer to the matrix array.
	*/
	void addMat4Uniform(std::string uniformID, float* matPointer);

	/**
	@brief A function to initlaise the uniforms.
	*/
	void addVec3Uniform(std::string uniformID, Vec3 vec);

	/**
	@brief A function to initlaise the uniforms.
	*/
	void initaliseUniforms();

	/**
	@brief A function to set the diffuse value.
	*/
	void setDiffuse(Vec3 inDif);

	/**
	@brief A function to set the ambient value.
	*/
	void setAmbient(Vec3 inAmb);

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
	MUST BE RUN AFTER MESH INITALISE!!!
	@param vertexShaderFileName The vertex shader to use.
	@param fragmentShaderFileName The fragment shader to use.
	*/
	void initaliseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	/**
	@brief A function to initalise the shaders to use a colour with the mesh.
	MUST BE RUN AFTER MESH INITALISE!!!
	@param vertexShaderFileName The vertex shader to use.
	@param inR The colour red value.
	@param inG The colour green value.
	@param inB The colour blue value.
	*/
	void initaliseShaders(std::string vertexShaderFileName, float inR, float inG, float inB);

	/**
	@brief A function to initalise the shaders to use with the mesh.
	MUST BE RUN AFTER MESH INITALISE!!!
	@param vertexShaderFileName The vertex shader to use.
	@param inDiffuse The diffuse colour value.
	@param inAmbient The ambient colour value.
	*/
	void initaliseShaders(std::string vertexShaderFileName, Vec3 inDiffuse, Vec3 inAmbient);

	/**
	@brief A function to initalise a default colour shader to use with the mesh.
	MUST BE RUN AFTER MESH INITALISE!!!
	@param vertexShaderFileName The vertex shader to use.
	@param inColour The default colour shader to use.
	*/
	void initaliseDefaultColourShaders(std::string vertexShaderFileName, std::string inColour);

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

	/**
	@brief A function to set the colour.
	*/
	void setColour();

private:
	///The Shader for the Model
	std::string shaderID;
	///The mesh for the Model
	std::string meshID;
	///A boolean for if textured
	bool textured, colour;
	///The Uniform locations for the shader program
	std::unordered_map<std::string, float*> mat4Uniforms;
	std::unordered_map<std::string, Vec3> vec3Uniforms;
	///The ambient and diffuse values
	Vec3 ambient, diffuse;
};