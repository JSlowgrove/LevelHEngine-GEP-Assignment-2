#include "PS_Particle3D.h"

/**************************************************************************************************************/

/*Constructs a Particle Object.*/
PS_Particle3D::PS_Particle3D(RM_Model* model, float scaleValue, glm::vec3 direction, float moveSpeed) 
	: EB_Entity3D(model, scaleValue)
{
	/*initialise the direction*/
	this->direction = direction;
	/*initialise the moveSpeed*/
	this->moveSpeed =  moveSpeed;
}

/**************************************************************************************************************/

/*Destructs a Particle Object.*/
PS_Particle3D::~PS_Particle3D()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the ground*/
void PS_Particle3D::update(float dt)
{
	/*update the position of the particle*/
	move(direction * moveSpeed * dt);

	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}