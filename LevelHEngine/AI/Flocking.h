#pragma once

#include <vector>
#include "Boid.h"
#include "../Maths/Vec2.h"

/**
@brief Creates a Flocking object.
NOTE - This is a HEAVILY modifed version of code from a previous assignment (It was not built for 3D initaliy)
*/
class Flocking
{
public:
	/**
	@brief Constructs the 2D Flocking object.
	@param inNmberOfBoids The number of boids.
	@param inSpriteID The ID of the sprite.
	@param inXBoundary The rough x boundary of the boids.
	@param inYBoundary The rough y boundary of the boids.
	@param inMaxVel The maximum velocity of the boids.
	*/
	Flocking(int inNumberOfBoids, std::string inSpriteID, int inXBoundary, int inYBoundary, float inMaxVel);

	/**
	@brief Constructs the 3D Flocking object.
	@param inNmberOfBoids The number of boids.
	@param meshID The path of the mesh for the boids
	@param meshID The path of the texture for the boids.
	@param meshID The path of the vertex shader for the boids.
	@param meshID The path of the fragment shader for the boids.
	@param inXBoundary The rough x boundary of the boids.
	@param inYBoundary The rough y boundary of the boids.
	@param inZBoundary The rough z boundary of the boids.
	@param inMaxVel The maximum velocity of the boids.
	*/
	Flocking(int inNumberOfBoids, std::string inMesh, std::string inBoidTexture, std::string inBoidVertexShader, 
		std::string inBoidFragmentShader, int inXBoundary, int inYBoundary, int inZBoundary, float inMaxVel);

	/**
	@brief Constructs the 3D Flocking object.
	@param inNmberOfBoids The number of boids.
	@param meshID The path of the mesh for the boids
	@param meshID The path of the vertex shader for the boids.
	@param meshID The path of the fragment shader for the boids.
	@param inXBoundary The rough x boundary of the boids.
	@param inYBoundary The rough y boundary of the boids.
	@param inYBoundary The rough z boundary of the boids.
	@param inMaxVel The maximum velocity of the boids.
	*/
	Flocking(int inNumberOfBoids, std::string inMesh, std::string inBoidVertexShader,
		std::string inBoidFragmentShader, int inXBoundary, int inYBoundary, int inZBoundary, float inMaxVel);

	/**
	@brief Destructs the Flocking object.
	*/
	~Flocking();

	/**
	@brief A function that updates the Flocking.
	*/
	void update2D();

	/**
	@brief A function that updates the Flocking.
	*/
	void update3D();

	/**
	@brief Draws the 2D Flocking.
	@param renderer A pointer to the renderer.
	*/
	void draw2D();

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
	///The ID of the 2D boid sprite.
	std::string spriteID;
	///A vector of Particle boids.
	std::vector<Boid*> boids;
	///What to do with the rule. (1 == possitve, 0 = neutral, -1 == negative)
	int applyRule1, applyRule2, applyRule3;
	///The boundaries of the boids.
	int xBoundary, yBoundary, zBoundary;
	///The max velocity.
	float maxVel;

	/**
	@brief Applies Boid Rule 1.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule1(int index);

	/**
	@brief Applies Boid Rule 1.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec3 ruleOne3D(int index);

	/**
	@brief Applies Boid Rule 2.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule2(int index);

	/**
	@brief Applies Boid Rule 2.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec3 ruleTwo3D(int index);

	/**
	@brief Applies Boid Rule 3.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec2 rule3(int index);

	/**
	@brief Applies Boid Rule 3.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the rule.
	*/
	Vec3 ruleThree3D(int index);

	/**
	@brief Applies Boid rough boundaries.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the boundary.
	*/
	Vec2 roughBoundaries(int index);

	/**
	@brief Applies Boid rough boundaries.
	@param index The index of the Boid to test.
	@returns The resultant velocity of the boundary.
	*/
	Vec3 roughBoundaries3D(int index);

	/**
	@brief Limits the Boid velocity.
	@param index The index of the Boid to test.
	*/
	void limitVelocity(int index);

	/**
	@brief Limits the Boid velocity.
	@param index The index of the Boid to test.
	*/
	void limitVelocity3D(int index);
};