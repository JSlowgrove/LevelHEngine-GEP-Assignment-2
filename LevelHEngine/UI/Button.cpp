#include "Button.h"

#include "../Core/InputManager.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Core/Logging.h"

Button::Button(std::string buttonImage, std::string buttonHeldImage, Vec2 inPos, Vec2 inDim): pos(inPos), dim(inDim), pressed(false)
{
	//initalise the button sprites
	buttonSprite = ResourceManager::initialiseSprite(buttonImage);
	ResourceManager::getSprite(buttonSprite)->scaleSprite(dim);
	buttonHeldSprite = ResourceManager::initialiseSprite(buttonHeldImage);
	ResourceManager::getSprite(buttonHeldSprite)->scaleSprite(dim);
}

Button::Button(std::string buttonImage, std::string buttonHeldImage, Vec2 inPos) : pos(inPos), pressed(false)
{
	//initalise the button sprites
	buttonSprite = ResourceManager::initialiseSprite(buttonImage);
	buttonHeldSprite = ResourceManager::initialiseSprite(buttonHeldImage);
	dim = ResourceManager::getSprite(buttonHeldSprite)->getDimensions();
}

Button::~Button()
{
}

bool Button::input()
{
	Vec2 mousePos = InputManager::getMousePos();

	if (mousePos.x < pos.x + dim.x && mousePos.x > pos.x
		&& mousePos.y < pos.y + dim.y && mousePos.y > pos.y)
	{
		pressed = true; 
		if (InputManager::isMouseButtonReleased(MOUSE_LEFT))
		{
			pressed = false;
			return true;
		}
	}
	else
	{
		pressed = false;
	}

	return false;
}

void Button::draw()
{
	if (!pressed)
	{
		ResourceManager::getSprite(buttonSprite)->pushToScreen(pos);
	}
	else
	{
		ResourceManager::getSprite(buttonHeldSprite)->pushToScreen(pos);
	}
}