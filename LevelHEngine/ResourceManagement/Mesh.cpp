#include "Mesh.h"
#include "Heightmap.h"

Mesh::Mesh(std::string objFileName) : heightmap(false)
{
	//initialise the texture
	textureFileName = "Untextured";

	//Initialise the vertex buffer object
	initialiseVAO(objFileName);
}

Mesh::Mesh(std::string fileName, bool heightmap) : heightmap(heightmap)
{
	//initialise the texture
	textureFileName = "Untextured";

	//Initialise the vertex buffer object
	initialiseVAO(fileName);
}

Mesh::Mesh(std::string objFileName, std::string materialFileName) : heightmap(false)
{
	//store the texture
	this->textureFileName = materialFileName;

	//Initialise the vertex buffer object
	initialiseVAO(objFileName);
}

Mesh::~Mesh()
{
	//delete data
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteTextures(1, &textureID);
}

void Mesh::initialiseVAO(std::string fileName)
{
	//Creates one VAO
	glGenVertexArrays(1, &vertexArrayObject);
	//initialise the code to bind to the VBO
	glBindVertexArray(vertexArrayObject);

	//load the obj file
	std::vector<float> vertices;
	std::vector<float> vertexNormals;
	std::vector<float> vertexTextures;
	std::vector<unsigned int> indices;
	if (!heightmap)
	{
		FileLoader::loadOBJFile(fileName, vertices, vertexNormals, vertexTextures);
	}
	else
	{
		Heightmap::initaliseHeightmap(fileName, vertices, vertexNormals, vertexTextures, indices);
	}

	//set the number of vertices's
	numberOfVertices = vertices.size() / 3;

	//calculate max and min verticies
	calculateMaxAndMinVerticies(vertices);

	GLuint positionBuffer = initaliseVBO(3, vertices, 0);

	GLuint normalBuffer = initaliseVBO(3, vertexNormals, 1);

	//test if the model uses a texture
	if (textureFileName != "Untextured")
	{
		//initialise the texture
		initialiseTexture(vertexTextures);
	}

	//if using the hieghtmap (indices)
	if (heightmap)
	{
		GLuint indexBuffer = initaliseIndicies(indices);
	}

	numberOfIndices = indices.size();
	
	//deactivate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//delete the VBO's
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);

	//disable the array
	glDisableVertexAttribArray(0);
}

void Mesh::initialiseTexture(std::vector<float> vertexTextures)
{
	//Loads the image as a surface
	SDL_Surface* image = IMG_Load(("Assets/img/" + textureFileName).c_str());

	//Error Check - If unable to load image then end program
	if (!image)
	{
		Logging::logE("Unable to load image from: " + textureFileName);
		Logging::logE("Image error : " + std::string(IMG_GetError()));
	}

	//check and store the file format
	GLenum format;
	if (image->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (image->format->BytesPerPixel == 4)
	{
		format = GL_RGBA;
	}

	// Create one OpenGL texture
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint textureBuffer = initaliseVBO(2, vertexTextures, 2);

	//deactivate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//delete the VBO
	glDeleteBuffers(1, &textureBuffer);

	//disable the array
	glDisableVertexAttribArray(0);

	//free the surface
	SDL_FreeSurface(image);
}

GLuint Mesh::getVAO()
{
	//returns the vertex array object
	return vertexArrayObject;
}

GLuint Mesh::getTextureID()
{
	//returns the texture ID
	return textureID;
}

unsigned int Mesh::getNumberOfVertices()
{
	//returns the vertex buffer object
	return numberOfVertices;
}

GLuint Mesh::initaliseIndicies(std::vector<unsigned int> &inIndices)
{
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * inIndices.size(), &inIndices[0], GL_STATIC_DRAW);

	return indexBuffer;
}

GLuint Mesh::initaliseVBO(unsigned int vecNum, std::vector<float> &inVBOData, int linkNum)
{
	//Variable for storing a VBO
	GLuint positionBuffer = 0;
	//Create a generic buffer
	glGenBuffers(1, &positionBuffer);
	//Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	//Send the data to OpenGL and set it to use GL_STATIC_DRAW (write it once)
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices * vecNum, &inVBOData[0], GL_STATIC_DRAW);

	//set how the VBO will link to the shader
	glVertexAttribPointer(linkNum, vecNum, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(linkNum);

	return positionBuffer;
}

void Mesh::calculateMaxAndMinVerticies(std::vector<float> &vertices)
{
	//calculate the max and min verticies
	for (unsigned int i = 0; i < vertices.size(); i += 3)
	{
		//x
		if (vertices[i] > maxVert.x)
		{
			maxVert.x = vertices[i];
		}
		else if (vertices[i] < minVert.x)
		{
			minVert.x = vertices[i];
		}
		//y
		if (vertices[i + 1] > maxVert.y)
		{
			maxVert.y = vertices[i + 1];
		}
		else if (vertices[i + 1] < minVert.y)
		{
			minVert.y = vertices[i + 1];
		}
		//z
		if (vertices[i + 2] > maxVert.z)
		{
			maxVert.z = vertices[i + 2];
		}
		else if (vertices[i + 2] < minVert.z)
		{
			minVert.z = vertices[i + 2];
		}
	}
}