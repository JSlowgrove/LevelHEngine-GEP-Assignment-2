#pragma once

#include <string>
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Core/GameObject.h"

/**
@brief Creates a Boid object.
NOTE - This is a HEAVILY modifed version of code from a previous assignment (It was not built for 3D initaliy)
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
	@brief Constructs the 3D Boid Object.
	@param boidIndex The 3D boid index number.
	@param meshID The path of the mesh for the boid
	@param meshID The path of the texture for the boid.
	@param meshID The path of the vertex shader for the boid.
	@param meshID The path of the fragment shader for the boid.
	@param direction The direction of the Sprite.
	@param moveSpeed The move speed of the Sprite.
	@param position The position of the Sprite.
	*/
	Boid(int boidIndex, std::string inMesh, std::string inBoidTexture, std::string inBoidVertexShader,
		std::string inBoidFragmentShader, Vec3 inDirection, float inMoveSpeed, Vec3 inPosition);

	/**
	@brief Constructs the 3D Boid Object.
	@param boidIndex The 3D boid index number.
	@param meshID The path of the mesh for the boid
	@param meshID The path of the vertex shader for the boid.
	@param meshID The path of the fragment shader for the boid.
	@param direction The direction of the Sprite.
	@param moveSpeed The move speed of the Sprite.
	@param position The position of the Sprite.
	*/
	Boid(int boidIndex, std::string inMesh, std::string inBoidVertexShader, std::string inBoidFragmentShader,
		Vec3 inDirection, float inMoveSpeed, Vec3 inPosition);

	/**
	@brief Destructs the Boid Object deleting the Boid Object from memory.
	*/
	~Boid();

	/**
	@brief A function that updates the 2D Boid.
	*/
	void update2D();

	/**
	@brief A function that updates the 3D Boid.
	*/
	void update3D();

	/**
	@brief Draw the 2D Boid to the screen.
	*/
	void draw2D();

	/**
	@brief Sets the position of the 2D Boid.
	@param position The new position.
	*/
	void setPosition2D(Vec2 inPosition);

	/**
	@brief Sets the position of the 3D Boid.
	@param position The new position.
	*/
	void setPosition3D(Vec3 inPosition);

	/**
	@brief Sets the position of the 2D Boid.
	@param x The X position.
	@param y The Y position.
	*/
	void setPosition2D(float inX, float inY);

	/**
	@brief Sets the position of the 3D Boid.
	@param x The X position.
	@param y The Y position.
	@param y The Y position.
	*/
	void setPosition3D(float inX, float inY, float inZ);

	/**
	@brief Move the 2D Boid.
	@param movement The amount to move by.
	*/
	void move2D(Vec2 movement);

	/**
	@brief Move the 3D Boid.
	@param movement The amount to move by.
	*/
	void move3D(Vec3 movement);

	/**
	@brief Move the 2D Boid along the X axis.
	@param movement The amount to move by.
	*/
	void move2DX(float movement);

	/**
	@brief Move the 2D Boid along the Y axis.
	@param movement The amount to move by.
	*/
	void move2DY(float movement);

	/**
	@brief Move the 2D Boid along the X axis.
	@param movement The amount to move by.
	*/
	void move3DX(float movement);

	/**
	@brief Move the 3D Boid along the Y axis.
	@param movement The amount to move by.
	*/
	void move3DY(float movement);

	/**
	@brief Move the 3D Boid along the Z axis.
	@param movement The amount to move by.
	*/
	void move3DZ(float movement);

	/**
	@brief Sets the moveSpeed of the Boid.
	@param moveSpeed The new moveSpeed.
	*/
	void setMoveSpeed(float inMoveSpeed);

	/**
	@brief Sets the direction of the 2D Boid.
	@param direction The new direction.
	*/
	void setDirection2D(Vec2 inDirection);

	/**
	@brief Sets the direction of the 3D Boid.
	@param direction The new direction.
	*/
	void setDirection3D(Vec3 inDirection);

	/**
	@brief Gets the moveSpeed of the Boid.
	@returns The moveSpeed.
	*/
	float getMoveSpeed();

	/**
	@brief Gets the position of the 2D Boid.
	@returns The position of the Boid.
	*/
	Vec2 getPosition2D();

	/**
	@brief Gets the position of the 3D Boid.
	@returns The position of the Boid.
	*/
	Vec3 getPosition3D();

	/**
	@brief Gets the direction of the 2D Boid.
	@returns The direction of the Boid.
	*/
	Vec2 getDirection2D();

	/**
	@brief Gets the direction of the 3D Boid.
	@returns The direction of the Boid.
	*/
	Vec3 getDirection3D();

	/**
	@brief Gets the Boid 3D game object ID.
	@returns The 3D game object ID of the Boid.
	*/
	std::shared_ptr<GameObject> getObject();

private:
	///The 2D sprite ID.
	std::string spriteID;
	///A shared pointer to the 3D game object
	std::shared_ptr<GameObject>  object;
	///The 2D direction of the Particle.
	Vec2 direction2D;
	///The 3D direction of the Particle.
	Vec3 direction3D;
	///The 2D Position of the Particle.
	Vec2 position2D;
	///The 3D Position of the Particle.
	Vec3 position3D;
	///The movement speed of the Particle.
	float moveSpeed;
};
