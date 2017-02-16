#pragma once

#include <SDL.h>
#include "../../Maths/Vec2.h"
#include "../ResourceManagement//Sprite.h"

/**
@brief Creates a Boid object.
*/
class Boid
{
public:
	/**
	@brief Constructs the Boid Object.
	@param sprite A pointer to the Sprite.
	@param scaleValue The scale of the Sprite.
	@param direction The direction of the Sprite.
	@param moveSpeed The move speed of the Sprite.
	@param position The position of the Sprite.
	*/
	Boid(Sprite* inSprite, float inScaleValue, Vec2 inDirection, float inMoveSpeed, Vec2 inPosition);

	/**
	@brief Destructs the Boid Object deleting the Boid Object from memory.
	*/
	~Boid();

	/**
	@brief A function that updates the Boid.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Draw the Boid to the screen.
	*/
	void draw();

	/**
	@brief Sets the position of the Boid.
	@param position The new position.
	*/
	void setPosition(Vec2 inPosition);

	/**
	@brief Sets the position of the Boid.
	@param x The X position.
	@param y The Y position.
	*/
	void setPosition(float inX, float inY);

	/**
	@brief Sets the scale of the Boid.
	@param scaleValue The new scale.
	*/
	void setScale(float inScaleValue);

	/**
	@brief Move the Boid.
	@param movement The amount to move by.
	*/
	void move(Vec2 movement);

	/**
	@brief Move the Boid along the X axis.
	@param movement The amount to move by.
	*/
	void moveX(float movement);

	/**
	@brief Move the Boid along the Y axis.
	@param movement The amount to move by.
	*/
	void moveY(float movement);

	/**
	@brief Sets the moveSpeed of the Boid.
	@param moveSpeed The new moveSpeed.
	*/
	void setMoveSpeed(float inMoveSpeed);

	/**
	@brief Sets the direction of the Boid.
	@param direction The new direction.
	*/
	void setDirection(Vec2 inDirection);

	/**
	@brief Gets the moveSpeed of the Boid.
	@returns The moveSpeed.
	*/
	float getMoveSpeed();

	/**
	@brief Gets the position of the Boid.
	@returns The position of the Boid.
	*/
	Vec2 getPosition();

	/**
	@brief Gets the direction of the Boid.
	@returns The direction of the Boid.
	*/
	Vec2 getDirection();

	/**
	@brief Gets the scale of the Boid.
	@returns The scale of the Boid.
	*/
	float getScale();

private:
	///A pointer to the sprite.
	Sprite* sprite;
	///The direction of the Particle.
	Vec2 direction;
	///The Position of the Particle.
	Vec2 position;
	///The scale of the Particle.
	float scaleValue;
	///The movement speed of the Particle.
	float moveSpeed;
};
