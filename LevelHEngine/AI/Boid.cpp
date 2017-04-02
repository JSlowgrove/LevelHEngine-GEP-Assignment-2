#include "Boid.h"

#include "../ResourceManagement/ResourceManager.h"
#include "../Core/Application.h"
#include "../Core/GameObject.h"
#include "../Components/TransformComponent.h"
#include "../Components/ModelComponent.h"

Boid::Boid(std::string inSpriteID, Vec2 inDirection, float inMoveSpeed, Vec2 inPosition)
{
	//initialise the variables
	spriteID = inSpriteID;
	direction2D = inDirection;
	moveSpeed =  inMoveSpeed;
	position2D = inPosition;
}

Boid::Boid(int boidIndex, std::string inMesh, std::string inBoidTexture, std::string inBoidVertexShader, std::string inBoidFragmentShader, Vec3 inDirection, float inMoveSpeed, Vec3 inPosition)
{
	//initialise the variables
	direction3D = inDirection;
	moveSpeed = inMoveSpeed;
	position3D = inPosition;

	//initalise a game object for the boid
	object = GameObject::create("boid-" + std::to_string(boidIndex)).lock();
	object->addComponent<TransformComponent>();
	object->addComponent<ModelComponent>();

	object->awake();

	object->getComponent<TransformComponent>().lock()->setPos(inPosition);
	object->getComponent<ModelComponent>().lock()->initaliseMesh(inMesh, inBoidTexture);
	object->getComponent<ModelComponent>().lock()->initaliseShaders(inBoidVertexShader, inBoidFragmentShader);
}

Boid::Boid(int boidIndex, std::string inMesh, std::string inBoidVertexShader, std::string inBoidFragmentShader, Vec3 inDirection, float inMoveSpeed, Vec3 inPosition)
{
	//initialise the variables
	direction3D = inDirection;
	moveSpeed = inMoveSpeed;
	position3D = inPosition;

	//initalise a game object for the boid
	object = GameObject::create("boid-" + std::to_string(boidIndex)).lock();
	object->addComponent<TransformComponent>();
	object->addComponent<ModelComponent>();

	object->awake();

	object->getComponent<TransformComponent>().lock()->setPos(inPosition);
	object->getComponent<ModelComponent>().lock()->initaliseMesh(inMesh);
	object->getComponent<ModelComponent>().lock()->initaliseDefaultColourShaders(inBoidVertexShader, inBoidFragmentShader);
}

Boid::~Boid()
{
}

void Boid::update2D()
{
	//update the position of the particle
	move2D(direction2D * moveSpeed * Application::getDT());
}

void Boid::update3D()
{
	//update the position of the particle
	move3D(direction3D * moveSpeed * Application::getDT());
}

void Boid::draw2D()
{
	//draw the texture to the screen
	ResourceManager::getSprite(spriteID)->pushToScreen(position2D);
}

void Boid::setPosition2D(Vec2 inPosition)
{
	//set the position
	position2D = inPosition;
}

void Boid::setPosition2D(float inX, float inY)
{
	//set the x position
	position2D.x = inX;
	//set the y position
	position2D.y = inY;
}

void Boid::setPosition3D(Vec3 inPosition)
{
	position3D = inPosition;
}

void Boid::setPosition3D(float inX, float inY, float inZ)
{
	position3D.x = inX;
	position3D.y = inY;
	position3D.z = inZ;
}

void Boid::move2D(Vec2 movement)
{
	//update the position
	position2D += movement;
}

void Boid::move3D(Vec3 movement)
{
	position3D += movement;
}

void Boid::move2DX(float movement)
{
	//update the position
	position2D.x += movement;
}

void Boid::move2DY(float movement)
{
	//update the position
	position2D.y += movement;
}

void Boid::move3DX(float movement)
{
	position3D.x += movement;
}

void Boid::move3DY(float movement)
{
	position3D.y += movement;
}

void Boid::move3DZ(float movement)
{
	position3D.z += movement;
}

void Boid::setMoveSpeed(float inMoveSpeed)
{
	//set the move speed
	moveSpeed = inMoveSpeed;
}

void Boid::setDirection2D(Vec2 inDirection)
{
	//update the direction
	direction2D = inDirection;
}

void Boid::setDirection3D(Vec3 inDirection)
{
	direction3D = inDirection;
}

float Boid::getMoveSpeed()
{
	//return the move speed
	return moveSpeed;
}

Vec2 Boid::getPosition2D()
{
	//return the position
	return position2D;
}

Vec3 Boid::getPosition3D()
{
	return position3D;
}

Vec2 Boid::getDirection2D()
{
	//return the direction
	return direction2D;
}

Vec3 Boid::getDirection3D()
{
	return direction3D;
}

std::shared_ptr<GameObject> Boid::getObject()
{
	return object;
}
