#include "EP_Player.h"

EP_Player::EP_Player(C_Texture* sprite, C_Vec2 pos, C_Vec2 dimensions, C_Vec2 screenDimensions, float* universalSpeed)
	: EB_Animated(sprite, pos, dimensions, 2, C_Vec2(1.0f, 1.0f), 0.5f, "EP_Player", universalSpeed),
	screenDimensions(screenDimensions), pressed(false), health(3), maxHealth(3)
{
}

EP_Player::~EP_Player()
{
}

void EP_Player::update(float dt)
{
	//Update the animation
	animate(dt);

	//Make sure that the player is on the screen
	if (pos.x + dimensions.x > screenDimensions.x)
	{
		pos.x = screenDimensions.x - dimensions.x;
	}
	if (pos.x < 0.0f)
	{
		pos.x = 0.0f;
	}
	if (pos.y + dimensions.y > screenDimensions.y)
	{
		pos.y = screenDimensions.y - dimensions.y;
	}
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}
}

void EP_Player::input(SDL_Event& incomingEvent, C_Vec2 mousePos)
{
	switch (incomingEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN: //If a mouse button is pressed

		//Left Mouse Button
		if (incomingEvent.button.button == SDL_BUTTON_LEFT)
		{
			//Test if the mouse is over the player
			if (mousePos.x >= pos.x && mousePos.x < pos.x + dimensions.x
				&& mousePos.y >= pos.y && mousePos.y < pos.y + dimensions.x)
			{
				pressed = true;
				//set the offset for making the player be attached to where the player was pressed
				offset = mousePos - pos;
			}	
			else
			{
				pressed = false;
			}
		}
		break;

	case SDL_MOUSEBUTTONUP: //If a mouse button is released

		//Left Mouse Button
		if (incomingEvent.button.button == SDL_BUTTON_LEFT)
		{
				pressed = false;
		}
		break;
	}

	if (pressed)
	{
		//set the player position to the mouse pos using the pressed offset for the mouse position on the player
		pos = mousePos - offset;
	}	
}

void EP_Player::draw(SDL_Renderer* renderer)
{
	//Draw the player
	sprite->pushSpriteToScreen(renderer, pos, dimensions, spriteIndex * spriteDimensions, spriteDimensions);
}

void EP_Player::increaseHealth()
{
	//increase health if lower than the max health
	if (health < maxHealth)
	{
		health++;
	}
}

void EP_Player::decreaseHealth()
{
	if (health > 0)//decrease health if higher than 0
	{
		//decrease health
		health--;
	}
}

int EP_Player::getHealth()
{
	return health;
}

bool EP_Player::entityCollisionTest(C_Vec2 entityPos, C_Vec2 entityDimensions)
{
	//Collision check between the player and the entity
	if (C_Utilities::rectRectIntersect(pos, dimensions, entityPos, entityDimensions))
	{
		return true;
	}
	return false;
}