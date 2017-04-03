#pragma once

#include "GL/glew.h"
#include <string>
#include "Primitives.h"
#include "../Maths/Vec3.h"

/**
@brief Creates an object from an text file, this can then be used with OpenGL.
*/
class Mesh
{	
public:

	/**
	@brief Creates a vertex array object using a obj file location and OpenGL.
	@param objFileName The name of the obj file.
	*/
	Mesh(std::string objFileName);

	/**
	@brief Creates a vertex array object using a primitive type.
	@param primType The primitive type.
	*/
	Mesh(Primitives::PrimativeType primType);

	/**
	@brief Creates a vertex array object using a file location and OpenGL.
	@param fileName The name of the file.
	@param heightmap A boolean stating if it is a heightmap.
	*/
	Mesh(std::string fileName, bool heightmap);

	/**
	@brief Creates a vertex array object using a obj file location and OpenGL.
	@param objFileName The name of the obj file.
	@param textureFileName The name of the texture file.
	*/
	Mesh(std::string objFileName, std::string textureFileName);

	/**
	@brief Creates a vertex array object using a file location and OpenGL.
	@param fileName The name of the file.
	@param textureFileName The name of the texture file.
	@param heightmap A boolean stating if it is a heightmap.
	*/
	Mesh(std::string fileName, std::string textureFileName, bool heightmap);

	/**
	@brief Destructs an Object.
	*/
	~Mesh();
	
	/**
	@brief Returns the vertex array object.
	@returns The vertex array object.
	*/
	GLuint getVAO();

	/**
	@brief Returns the Texture ID.
	@returns The texture ID.
	*/
	GLuint getTextureID();

	/**
	@brief Returns the number of vertices.
	@returns The number of vertices.
	*/
	unsigned int getNumberOfVertices();

	/**
	@brief Returns the max vertices.
	@returns The max vertices.
	*/
	Vec3 getMaxVert() { return maxVert; }

	/**
	@brief Returns the min vertices.
	@returns The min vertices.
	*/
	Vec3 getMinVert() { return minVert; }

	/**
	@brief Returns the number of indices.
	@returns The number of indices.
	*/
	unsigned int getNumIndices() { 
		return numberOfIndices; 
	};

	/**
	@brief Checks if it is heightmap.
	@returns The heightmap bool.
	*/
	bool checkHeightmap() { return heightmap; }

	/**
	@brief Checks if it is primative.
	@returns The primative bool.
	*/
	bool checkPrimitive() { return primative; }

private:
	///The Vertex Array Object for use with OpenGL
	GLuint vertexArrayObject;
	///The index buffer
	GLuint indexBuffer;
	///The texture buffer
	GLuint textureBuffer;

	///Number of vertices in the model
	unsigned int numberOfVertices;
	unsigned int numberOfIndices;
	///The name of the texture file
	std::string textureFileName;
	///The Texture
	GLuint textureID;
	///The Max Verticies
	Vec3 maxVert;
	///The Min Verticies
	Vec3 minVert;
	///If the mesh if is a heightmap
	bool heightmap;
	///If the mesh is a primitive
	bool primative;

	/**
	@brief Initialise the texture.
	@param vertexTextures The vertex textures vector.
	*/
	void initialiseTexture(std::vector<float> vertexTextures);

	/**
	@brief Initialise the vertex array object.
	@param fileName The name of the file.
	*/
	void initialiseVAO(std::string fileName);

	/**
	@brief Initialise indices.
	@param inIndices A reference to the indices vector.
	@returns The indices.
	*/
	GLuint initaliseIndicies(std::vector<unsigned int> &inIndices);

	/**
	@brief Initialise a vertex array object.
	@param vecNum The vector num.
	@param inVBOData A refrence to the VBO data vector.
	@param linkNum The link number.
	@returns The vertex array object.
	*/
	GLuint initaliseVBO(unsigned int vecNum, std::vector<float> &inVBOData, int linkNum);

	/**
	@brief Calculated the maximum and minimum indices.
	@param vertices A reference to the vertices vector.
	*/
	void calculateMaxAndMinVerticies(std::vector<float> &vertices);
};