#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "Sprite.h"
#include "../../Maths/Vec2.h"

/**
@brief Creates a Text sprite for use with using the Text formating.
*/
class Text
{
public:
	/**
	@brief Constructs the Text Texture. Font size and colour will be default (size 10 and black).
	@param text The text to display.
	@param fontLocation The location of the font file.
	*/
	Text(std::string text, std::string fontLocation);

	/**
	@brief Constructs the Text Texture. Font colour will be default (black).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	*/
	Text(std::string text, std::string fontLocation, int fontSize);

	/**
	@brief Constructs the Text Texture. Font size will be default (size 10).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	Text(std::string text, std::string fontLocation, int r, int g, int b);

	/**
	@brief Constructs the Text Texture. Font size will be default (size 10).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontColour The colour of the font.
	*/
	Text(std::string text, std::string fontLocation, SDL_Colour fontColour);

	/**
	@brief Constructs the Text Texture.
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	Text(std::string text, std::string fontLocation, int fontSize, int r, int g, int b);

	/**
	@brief Constructs the Text Texture.
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	@param fontColour The colour of the font.
	*/
	Text(std::string text, std::string fontLocation, int fontSize, SDL_Colour fontColour);

	/**
	@brief Destructs the Text Texture.
	*/
	~Text();

	/**
	@brief Pushes the Text Texture to the screen to the XY Coordinates.
	@param pos The position to push the Text Texture to.
	*/
	void pushToScreen(Vec2 pos);

	/**
	@brief Sets the colour of the text.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	void setColour(int r, int g, int b);

	/**
	@brief Sets the colour of the text.
	@param colour The colour of the font.
	*/
	void setColour(SDL_Colour colour);

	/**
	@brief Sets the font size of the text.
	@param fontSize The font size of the text.
	*/
	void setFontSize(int fontSize);

	/**
	@brief Sets the font of the text.
	@param fontLocation The location of the font file.
	*/
	void setFont(std::string fontLocation);

	/**
	@brief Sets the text.
	@param text The text to display.
	*/
	void setText(std::string text);

	/**
	@brief Gets the dimensions of the Text Texture.
	@returns The dimensions of the Text Texture.
	*/
	Vec2 getDimensions();

private:
	///Font
	TTF_Font* font;
	///Font colour
	SDL_Colour fontColour;
	///The surface sprite
	Sprite* surfaceData;
	///Font size
	int fontSize;
	///The text and font location
	std::string text, fontLocation;
	///The Texture dimensions
	Vec2 dimensions;

	/**
	@brief Creates a Text Texture using the Text data.
	*/
	void createTextTexture();
};