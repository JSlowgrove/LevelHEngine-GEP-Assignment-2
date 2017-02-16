#include "Text.h"

Text::Text(std::string text, std::string fontLocation)
	: text(text), fontLocation(fontLocation)
{
	//Set font size and colour to default
	fontSize = 10;
	fontColour = { (Uint8)0, (Uint8)0, (Uint8)0 };
	
	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize)
	: text(text), fontLocation(fontLocation), fontSize(fontSize)
{
	//Set font colour to default
	fontColour = { (Uint8)0, (Uint8)0, (Uint8)0 };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int r, int g, int b)
	: text(text), fontLocation(fontLocation)
{
	//Set font size to default
	fontSize = 10;

	//Set font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, SDL_Colour fontColour)
	: text(text), fontLocation(fontLocation), fontColour(fontColour)
{
	//Set font size to default
	fontSize = 10;

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize, int r, int g, int b)
	: text(text), fontLocation(fontLocation), fontSize(fontSize)
{
	//Set font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize, SDL_Colour fontColour)
	: text(text), fontLocation(fontLocation), fontSize(fontSize), fontColour(fontColour)
{
	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::~Text()
{
	//deletes the sprite
	delete surfaceData;
	//delete font
	TTF_CloseFont(font);
	font = NULL;
}

void Text::pushToScreen(Vec2 pos)
{
	//draw the text sprite
	surfaceData->pushToScreen(pos);
}

void Text::setColour(int r, int g, int b)
{
	//Set the font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Recreate the text texture
	createTextTexture();
}

void Text::setColour(SDL_Colour fontColour)
{
	//Set the font colour
	this->fontColour = fontColour;

	//Recreate the text texture
	createTextTexture();
}

void Text::setFontSize(int fontSize)
{
	//delete font
	TTF_CloseFont(font);
	font = NULL;

	//Set the font size
	this->fontSize = fontSize;

	//Set the font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Recreate the text texture
	createTextTexture();
}

void Text::setFont(std::string fontLocation)
{
	//delete font
	TTF_CloseFont(font);
	font = NULL;

	//Set the font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Recreate the text texture
	createTextTexture();
}

void Text::setText(std::string text)
{
	//Set the text
	this->text = text;

	//Recreate the text texture
	createTextTexture();
}

Vec2 Text::getDimensions()
{
	return dimensions;
}

void Text::createTextTexture()
{
	//Declare the surface
	SDL_Surface *surface;

	//Create the surface from the font
	surface = TTF_RenderText_Blended(font, text.c_str(), fontColour);

	//Create a sprite (or recreate)
	if (surfaceData)
	{
		delete surfaceData;
	}
	surfaceData = new Sprite(surface);

	//Store the dimensions of the texture
	dimensions = surfaceData->getDimensions();
}