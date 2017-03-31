#include "Boid.h"

#include "../ResourceManagement/ResourceManager.h"
#include "../Core/Application.h"

Boid::Boid(std::string inSpriteID, Vec2 inDirection, float inMoveSpeed, Vec2 inPosition)
{
	//initialise the variables
	spriteID = inSpriteID;
	direction = inDirection;
	moveSpeed =  inMoveSpeed;
	position = inPosition;
}

Boid::~Boid()
{
}

void Boid::update()
{
	//update the position of the particle
	move(direction * moveSpeed * Application::getDT());
}

void Boid::draw()
{
	//draw the texture to the screen
	ResourceManager::getSprite(spriteID)->pushToScreen(position);
}

void Boid::setPosition(Vec2 inPosition)
{
	//set the position
	position = inPosition;
}

void Boid::setPosition(float inX, float inY)
{
	//set the x position
	position.x = inX;
	//set the y position
	position.y = inY;
}

void Boid::move(Vec2 movement)
{
	//update the position
	position += movement;
}

void Boid::moveX(float movement)
{
	//update the position
	position.x += movement;
}

void Boid::moveY(float movement)
{
	//update the position
	position.y += movement;
}

void Boid::setMoveSpeed(float inMoveSpeed)
{
	//set the move speed
	moveSpeed = inMoveSpeed;
}

void Boid::setDirection(Vec2 inDirection)
{
	//update the direction
	direction = inDirection;
}

float Boid::getMoveSpeed()
{
	//return the move speed
	return moveSpeed;
}

Vec2 Boid::getPosition()
{
	//return the position
	return position;
}

Vec2 Boid::getDirection()
{
	//return the direction
	return direction;
}