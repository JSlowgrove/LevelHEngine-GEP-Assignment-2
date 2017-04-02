#pragma once

#include <SDL.h>
#include <string>
#include "GL/glew.h"
#include "../Maths/Vec2.h"

/**
@brief Creates a Sprite for use with 2D.
*/
class Sprite
{
public:
	/**
	@brief Constructs the Sprite using an RGB value. This will create a 1x1 rectangle of that colour that can be scaled.
	@param r The red value.
	@param g The green value.
	@param b The blue value.
	*/
	Sprite(int r, int g, int b);

	/**
	@brief Constructs the Sprite using a surface.
	*/
	Sprite(SDL_Surface* inSurfaceData);

	/**
	@brief Constructs the Sprite using an RGB value. This will create a 1x1 rectangle of that colour that can be scaled.
	@param colour The colour value.
	*/
	Sprite(SDL_Colour colour);

	/**
	@brief Constructs the Sprite using an image location and a renderer. This is for use with SDL image.
	@param fileLocation The location of the image file.
	*/
	Sprite(std::string fileLocation);

	/**
	@brief Constructs the Sprite using an image location and a renderer. The magenta pixels of this image can represent alpha if needed.
	@param fileLocation The location of the image file.
	@param magentaAlpha If true any magenta pixels in the image will be converted to alpha.
	*/
	Sprite(std::string fileLocation, bool magentaAlpha);

	/**
	@brief Destructs Sprite.
	*/
	~Sprite();

	/**
	@brief Gets a pointer to the Sprite surface.
	@returns A pointer to the Sprite surface.
	*/
	SDL_Surface* getSurface();

	/**
	@brief Gets the Sprite dimensions.
	@returns The Sprite dimensions.
	*/
	Vec2 getDimensions();

	/**
	@brief Pushes the image to the Renderer at the XY Coordinates.
	@param pos The position of the image.
	*/
	void pushToScreen(Vec2 pos);

	/**
	@brief Scale the image to the dimensions inputed.
	@param pos The position of the image.
	@param scale The dimensions of the image.
	*/
	void scaleSprite(Vec2 scale);

private:
	///The Surface data
	SDL_Surface* surfaceData;
	///The Texture dimensions.
	Vec2 dimensions;
	///The VBO for the rectangle
	GLuint obj;
	///The Texture
	GLuint textureID;
	///The Shader ID
	std::string shaderID;

	void initaliseVBO(Vec2 pos, Vec2 scale);
	void initialiseTexture();
	void draw(Vec2 pos);
};