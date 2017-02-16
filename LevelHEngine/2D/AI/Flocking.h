#pragma once

#include <SDL.h>
#include <time.h>
#include <vector>
#include "../ResourceManagement/Sprite.h"
#include "Boid.h"
#include "../../Maths/Vec2.h"
#include "../../Maths/Scaling.h"

/**
@brief Creates a Flocking object.
*/
class Flocking
{
public:
	/**
	@brief Constructs the Flocking object.
	@param numberOfBoids The number of boids.
	@param sprite A pointer to the sprite for the boids.
	@param xBoundary The rough x boundary of the boids.
	@param yBoundary The rough y boundary of the boids.
	@param maxVel The maximum velocity of the boids.
	@param screenHeight The screen height.
	*/
	Flocking(int inNmberOfBoids, Sprite* inSprite, int inXBoundary, int inYBoundary, float inMaxVel, int inScreenHeight);

	/**
	@brief Destructs the Flocking object.
	*/
	~Flocking();

	/**
	@brief A function that updates the Flocking.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Draws the Flocking.
	@param renderer A pointer to the renderer.
	*/
	void draw();

	/**
	@brief Set applyRule1.
	@param applyRule1 What to do with the rule. (1 == possitve, 0 = neutral, -1 == negative)
	*/
	void setRule1(int inApplyRule1);

	/**
	@brief Set applyRule2.
	@param applyRule2 What to do with the rule. (1 == possitve, 0 = neutral, -1 == negative)
	*/
	void setRule2(int inApplyRule2);

	/**
	@brief Set applyRule3.
	@param applyRule3 What to do with the rule. (1 == possitve, 0 = neutral, -1 == negative)
	*/
	void setRule3(int inApplyRule3);

private:
	///A texture of a white square.
	Sprite* sprite;
	///A vector of Particle boids.
	std::vector<Boid*> boids;
	///What to do with the rule. (1 == possitve, 0 = neutral, -1 == negative)
	int applyRule1, applyRule2, applyRule3;
	///The boundaries of the boids.
	int xBoundary, yBoundary;
	///The max velocity.
	float maxVel;
	///The screen height.
	int screenHeight;

	/**
	@brief Applies Boid Rule 1.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule1(int index);

	/**
	@brief Applies Boid Rule 2.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule2(int index);

	/**
	@brief Applies Boid Rule 3.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule3(int index);

	/**
	@brief Applies Boid rough boundaries.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the boundary.
	*/
	Vec2 roughBoundaries(int index);

	/**
	@brief Limits the Boid velocity.
	@param index The index of the Boid to test.
	*/
	void limitVelocity(int index);
};