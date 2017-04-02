#pragma once

#include <unordered_map>
#include "../ResourceManagement/ResourceManager.h"
#include "Button.h"

/**
@brief Contains static variables and functions for use with UI manager.
*/
class UIManager
{
public:

	/**
	@brief A static function to delete all the UI
	*/
	static void deleteAllUI();

	/**
	@brief A static function to delete all the buttons
	*/
	static void deleteAllButtons();

	/**
	@brief A static function to delete the button
	@param id The ID of the file.
	*/
	static void deleteButton(std::string id) { buttons.erase(id); }

	/**
	@brief A static function to initialise a button and scale it.
	@param buttonImage A path to the image of the button.
	@param buttonHeldSprite A path to the held image of the button.
	@param pos The position.
	@param dim The dimensions.
	@returns The ID of the loaded file.
	*/
	static std::string initialiseButton(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos, Vec2 inDim);

	/**
	@brief A static function to initialise a button.
	@param buttonHeldSprite A path to the held image of the button.
	@param pos The position.
	@returns The ID of the loaded file.
	*/
	static std::string initialiseButton(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos);

	/**
	@brief A static function to get a button.
	@param id The ID of the file.
	*/
	static Button* getButton(std::string id) { return buttons[id]; }
		
private:
	///The loaded buttons
	static std::unordered_map<std::string, Button*> buttons;
};