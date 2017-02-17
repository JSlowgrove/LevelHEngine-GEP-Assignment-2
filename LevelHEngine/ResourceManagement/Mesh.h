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

	Mesh(Primitives::PrimativeType primType);

	Mesh(std::string fileName, bool heightmap);

	/**
	@brief Creates a vertex array object using a obj file location and OpenGL.
	@param objFileName The name of the obj file.
	@param textureFileName The name of the texture file.
	*/
	Mesh(std::string objFileName, std::string textureFileName);

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

	Vec3 getMaxVert() { return maxVert; }
	Vec3 getMinVert() { return minVert; }
	unsigned int getNumIndices() { 
		return numberOfIndices; 
	};
	bool checkHeightmap() { return heightmap; }
	bool checkPrimitive() { return primative; }

private:
	///The Vertex Array Object for use with OpenGL
	GLuint vertexArrayObject;
	GLuint indexBuffer;
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

	GLuint initaliseIndicies(std::vector<unsigned int> &inIndices);

	GLuint initaliseVBO(unsigned int vecNum, std::vector<float> &inVBOData, int linkNum);

	void calculateMaxAndMinVerticies(std::vector<float> &vertices);
};