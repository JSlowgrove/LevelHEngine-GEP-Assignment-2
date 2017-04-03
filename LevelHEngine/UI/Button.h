#pragma once

#include <string>
#include "../Maths/Vec2.h"

/**
@brief A State for a button.
*/
class Button
{
public:
	/**
	@brief Constructs the Button object.
	@param buttonImage A path to the image of the button.
	@param buttonHeldSprite A path to the held image of the button.
	@param pos The position.
	@param dim The dimensions.
	*/
	Button(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos, Vec2 inDim);

	/**
	@brief Constructs the Button object.
	@param buttonImage A path to the image of the button.
	@param buttonHeldSprite A path to the held image of the button.
	@param pos The position.
	*/
	Button(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos);

	/**
	@brief Destructs the Button object.
	*/
	~Button();

	/**
	@brief Handles the Button input.
	@returns If the button is released.
	*/
	bool input();

	/**
	@brief Draws the button.
	*/
	void draw();

private:
	///The menu sprite
	std::string buttonSprite, buttonHeldSprite;
	///A boolean for if the button is pressed
	bool pressed;
	///The button position and dimensions
	Vec2 pos, dim;
};