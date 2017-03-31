#pragma once

#include <string>
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"

/**
@brief Creates a Boid object.
NOTE - This is a modified version of a class I wrote for a previous assignment
*/
class Boid
{
public:
	/**
	@brief Constructs the 2D Boid Object.
	@param sprite The Sprite ID.
	@param direction The direction of the Sprite.
	@param moveSpeed The move speed of the Sprite.
	@param position The position of the Sprite.
	*/
	Boid(std::string inSpriteID, Vec2 inDirection, float inMoveSpeed, Vec2 inPosition);


	/**
	@brief Destructs the Boid Object deleting the Boid Object from memory.
	*/
	~Boid();

	/**
	@brief A function that updates the Boid.
	*/
	void update();

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

private:
	///A pointer to the sprite.
	std::string spriteID;
	///The direction of the Particle.
	Vec2 direction;
	///The Position of the Particle.
	Vec2 position;
	///The movement speed of the Particle.
	float moveSpeed;
};
