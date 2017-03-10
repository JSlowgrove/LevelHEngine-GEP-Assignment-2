#include "Sprite.h"

#include <SDL_image.h>
#include "../Maths/Convert.h"
#include "../Core/Logging.h"
#include "../Core/WindowFrame.h"
#include "../ResourceManagement/Shader.h"
#include "../ResourceManagement/ResourceManager.h"

Sprite::Sprite(int r, int g, int b)
{
	//Creates the surface
	surfaceData = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surfaceData, NULL, SDL_MapRGB(surfaceData->format, (Uint8)r, (Uint8)g, (Uint8)b));

	//initalise shader;
	shaderID = ResourceManager::initialiseShader("2d.texture", "2d.texture");
}

Sprite::Sprite(SDL_Surface* inSurfaceData) : surfaceData(inSurfaceData)
{
	//store the size of the sprite
	dimensions = Vec2(surfaceData->w, surfaceData->h);

	//initalise shader;
	shaderID = ResourceManager::initialiseShader("2d.texture", "2d.texture");
}

Sprite::Sprite(SDL_Colour colour)
{
	//Creates the surface
	surfaceData = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surfaceData, NULL, SDL_MapRGB(surfaceData->format, colour.r, colour.g, colour.b));

	//initalise shader;
	shaderID = ResourceManager::initialiseShader("2d.texture", "2d.texture");
}

Sprite::Sprite(std::string fileLocation)
{
	//Loads the image as a surface
	surfaceData = IMG_Load(fileLocation.c_str());

	//Image load check
	if (!surfaceData)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Logging::logE(message);
		return;
	}
	else
	{
		Logging::logI("Image loaded from: " + fileLocation);
	}

	//store the size of the sprite
	dimensions = Vec2(surfaceData->w, surfaceData->h);

	//initalise shader;
	shaderID = ResourceManager::initialiseShader("2d.texture", "2d.texture");
}

Sprite::Sprite(std::string fileLocation, bool magentaAlpha)
{
	//Loads the image as a surface
	surfaceData = SDL_LoadBMP(fileLocation.c_str());

	//Image load check
	if (!surfaceData)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Logging::logE(message);
		return;
	}
	else
	{
		Logging::logI("Image loaded from: " + fileLocation);
	}

	//Check if the images magenta is to be used as the alpha
	if (magentaAlpha)
	{
		//Replaces magenta with alpha
		SDL_SetColorKey(surfaceData, SDL_TRUE, SDL_MapRGB(surfaceData->format, 255, 0, 255));
	}

	//store the size of the texture
	dimensions = Vec2(surfaceData->w, surfaceData->h);

	//initalise shader;
	shaderID = ResourceManager::initialiseShader("2d.texture", "2d.texture");
}

Sprite::~Sprite()
{
	//delete the surface from memory
	SDL_FreeSurface(surfaceData);
	//delete data
	glDeleteVertexArrays(1, &obj);
	glDeleteTextures(1, &textureID);
}

SDL_Surface* Sprite::getSurface()
{
	return surfaceData;
}

Vec2 Sprite::getDimensions()
{
	return dimensions;
}

void Sprite::pushToScreen(Vec2 pos)
{
	//Convert to openGL coords
	pos = convertToOpenGLCoords(pos);
	Vec2 scale = scaleToOpenGLCoords(dimensions);

	//initalise VBO
	initaliseVBO(pos, scale);

	//render the image
	draw();
}

void Sprite::pushToScreen(Vec2 pos, Vec2 scale)
{
	//Convert to openGL coords
	pos = convertToOpenGLCoords(pos);
	scale = scaleToOpenGLCoords(scale);

	//initalise VBO
	initaliseVBO(pos, scale);

	//render the image
	draw();
}

Vec2 Sprite::convertToOpenGLCoords(Vec2 inVec)
{
	//get the screen dimensions
	Vec2 screenDim = WindowFrame::getWindowRes();

	/*opengl coordinates
	-1.0,1.0  -> 1.0, 1.0
	|					|
	-1.0,-1.0 -> 1.0,-1.0*/

	//convert the position to a number between 0 and 1
	float newX = Convert::normaliseFloat(inVec.x, screenDim.x, 0.0f);
	//double to get the range between 0 and 2
	newX *= 2.0f;
	//minus 1 to get the number between -1 and 1
	newX -= 1.0f;

	//convert the position to a number between 0 and 1
	float newY = Convert::normaliseFloat(inVec.y, screenDim.y, 0.0f);
	//double to get the range between 0 and 2
	newY *= 2.0f;
	//minus 1 to get the number between -1 and 1
	newY -= 1.0f;
	//invert the x coordinate to work with opengl coords
	newY = -newY;

	return Vec2(newX, newY);
}

Vec2 Sprite::scaleToOpenGLCoords(Vec2 inVec)
{
	//get the screen dimensions
	Vec2 screenDim = WindowFrame::getWindowRes();

	/*opengl coordinates
	-1.0,1.0  -> 1.0, 1.0
	|					|
	-1.0,-1.0 -> 1.0,-1.0*/

	//convert the position to a number between 0 and 1
	float newX = Convert::normaliseFloat(inVec.x, screenDim.x, 0.0f);
	//double to get the range between 0 and 2
	newX *= 2.0f;

	//convert the position to a number between 0 and 1
	float newY = Convert::normaliseFloat(inVec.y, screenDim.y, 0.0f);
	//double to get the range between 0 and 2
	newY *= 2.0f;

	return Vec2(newX, newY);
}

void Sprite::initaliseVBO(Vec2 pos, Vec2 scale)
{
	//get the max coordinates using the dimensions
	float maxX = pos.x + scale.x;
	float maxY = pos.y - scale.y;

	//Create a VBO
	glGenVertexArrays(1, &obj);
	//activate the VBO
	glBindVertexArray(obj);

	//Vertices for a square from two triangles
	float vertices[] =
	{
		//triangle 1
 		pos.x,	pos.y,
 		pos.x,	maxY,
 		maxX,	maxY,

		//triangle 2
		pos.x,	pos.y,
		maxX,	pos.y,
		maxX,	maxY,
	};

	//Variable for storing a VBO
	GLuint buffer = 0;
	//Create a generic 'buffer'
	glGenBuffers(1, &buffer);
	//activate the buffer as a VBO
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//send the data to OpenGL (num of vertices will always be 12 as it is 2 triangles)
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

	//link the VBO to the shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//initialise the UI texture
	initialiseTexture();

	//deactivate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//delete the VBO
	glDeleteBuffers(1, &buffer);
}

void Sprite::initialiseTexture()
{
	//check and store the file format
	GLenum format = 0;
	if (surfaceData->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (surfaceData->format->BytesPerPixel == 4)
	{
		format = GL_RGBA;
	}

	// texture coordinates
	float textureCoordinates[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	// Create one OpenGL texture
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, surfaceData->w, surfaceData->h, 0, format, GL_UNSIGNED_BYTE, surfaceData->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Variable for storing a VBO
	GLuint textureBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &textureBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, textureCoordinates, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//deactivate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//delete the VBO
	glDeleteBuffers(1, &textureBuffer);
}

void Sprite::draw()
{
	//Get the shader program
	glUseProgram(ResourceManager::getShaders(shaderID)->getShaderProgram());

	//activate the object
	glBindVertexArray(obj);

	//turn on blending
	glEnable(GL_BLEND);

	//turn on transparency (ALPHA * incomming   +  (1 - ALPHA) * current)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//texturing
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(ResourceManager::getShaders(shaderID)->getUniform("textureSampler"), 0);

	//draw the object, the num of vertices will always be 6 as it is drawing 2 triangles for a rectangle
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//turn of blending
	glDisable(GL_BLEND);

	//deactivate the object
	glBindVertexArray(0);

	//deactivate the shader
	glUseProgram(0);
}