#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "FileLoader.h"

/**
@brief The namespace for all resource management code.
*/
namespace ResourceManagment
{

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
		@brief Creates a vertex array object using a obj file location and OpenGL.
		@param objFileName The name of the obj file.
		@param textureFileName The name of the texture file.
		*/
		Mesh(std::string objFileName, std::string textureFileName);

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

	private:
		///The Vertex Array Object for use with OpenGL
		GLuint vertexArrayObject;
		///Number of vertices in the model
		unsigned int numberOfVertices;
		///The name of the texture file
		std::string textureFileName;
		///The Texture
		GLuint textureID;

		/**
		@brief Initialise the texture.
		@param vertexTextures The vertex textures vector.
		*/
		void initialiseTexture(std::vector<float> vertexTextures);

		/**
		@brief Initialise the vertex array object.
		@param objFileName The name of the obj file.
		*/
		void InitialiseVAO(std::string objFileName);
	};

}// End of resource management namespace