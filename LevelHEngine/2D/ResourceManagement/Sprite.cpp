#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, int r, int g, int b)
{
	//Creates the surface
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, (Uint8)r, (Uint8)g, (Uint8)b));
	
	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//delete the surface from memory
	SDL_FreeSurface(surface);
}

Sprite::Sprite(SDL_Renderer* renderer, SDL_Colour colour)
{
	//Creates the surface
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, colour.r, colour.g, colour.b));

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//delete the surface from memory
	SDL_FreeSurface(surface);
}

Sprite::Sprite(std::string fileLocation, SDL_Renderer* renderer)
{
	//Loads the image as a surface
	SDL_Surface* image = IMG_Load(fileLocation.c_str());

	//Image load check
	if (!image)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Logging::logE(message);
		return;
	}

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, image);

	//delete the surface from memory
	SDL_FreeSurface(image);

	//store the size of the texture
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);
}

Sprite::Sprite(std::string fileLocation, SDL_Renderer* renderer, bool magentaAlpha)
{
	//Loads the image as a surface
	SDL_Surface* image = SDL_LoadBMP(fileLocation.c_str());

	//Image load check
	if (!image)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Logging::logE(message);
		return;
	}

	//Check if the images magenta is to be used as the alpha
	if (magentaAlpha)
	{
		//Replaces magenta with alpha
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 0, 255));
	}

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, image);

	//delete the surface from memory
	SDL_FreeSurface(image);

	//store the size of the texture
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);
}

Sprite::~Sprite()
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);
}

SDL_Texture* Sprite::getTexture()
{
	return textureData;
}

Vec2 Sprite::getDimensions()
{
	return dimensions;
}

void Sprite::pushToScreen(SDL_Renderer* renderer, Vec2 pos)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Sprite::pushToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)scale.x;
	destRect.h = (int)scale.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Sprite::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 spritePos, Vec2 spriteDimensions)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)spriteDimensions.x;
	destRect.h = (int)spriteDimensions.y;

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);
}

void Sprite::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale, Vec2 spritePos, Vec2 spriteDimensions)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)scale.x;
	destRect.h = (int)scale.y;

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);
}

void Sprite::setColourTint(int r, int g, int b)
{
	//Tint the texture with the colour
	SDL_SetTextureColorMod(textureData, (Uint8)r, (Uint8)g, (Uint8)b);
}

void Sprite::setColourTint(SDL_Colour colour)
{
	//Tint the texture with the colour
	SDL_SetTextureColorMod(textureData, colour.r, colour.g, colour.b);
}