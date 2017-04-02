#include "UIManager.h"

#include <SDL.h>
#include <vector>
#include "../Core/Logging.h"

std::unordered_map<std::string, Button*> UIManager::buttons;

void UIManager::deleteAllUI()
{
	deleteAllButtons();
}

void UIManager::deleteAllButtons()
{
	for (auto button = buttons.begin(); button != buttons.end(); ++button)
	{
		delete button->second;
	}
	buttons.clear();
}

std::string UIManager::initialiseButton(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos, Vec2 inDim)
{
	//a string for the name of the linked button
	std::string linkedButtonName = buttonImage + "/" + buttonHeldSprite;

	//test if the object has already been loaded
	if (buttons.count(linkedButtonName) == 0)
	{
		//load the object
		buttons[linkedButtonName] = new Button(buttonImage, buttonHeldSprite, inPos, inDim);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(linkedButtonName + " button already loaded.");
	}
	//return the ID
	return linkedButtonName;
}

std::string UIManager::initialiseButton(std::string buttonImage, std::string buttonHeldSprite, Vec2 inPos)
{
	//a string for the name of the linked button
	std::string linkedButtonName = buttonImage + "/" + buttonHeldSprite;

	//test if the object has already been loaded
	if (buttons.count(linkedButtonName) == 0)
	{
		//load the object
		buttons[linkedButtonName] = new Button(buttonImage, buttonHeldSprite, inPos);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(linkedButtonName + " button already loaded.");
	}
	//return the ID
	return linkedButtonName;
}