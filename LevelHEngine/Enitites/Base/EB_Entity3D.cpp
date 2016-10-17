#include "EB_Entity3D.h"

/**************************************************************************************************************/

/*Constructs a Entity Object.*/
EB_Entity3D::EB_Entity3D(RM_Model* model, float scaleValue)
{
	/*initialise the model*/
	this->model = model;
	/*initialise the rotation*/
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	/*set the scale of the model*/
	this->scaleValue = scaleValue;
	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*Destructs a Entity Object.*/
EB_Entity3D::~EB_Entity3D()
{
}

/**************************************************************************************************************/

/*Draw the Entity to the screen.*/
void EB_Entity3D::draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	/*draw the model to the screen*/
	model->draw(viewMatrix, projMatrix);
}

/**************************************************************************************************************/

/*Sets the position of the Entity.*/
void EB_Entity3D::setPosition(glm::vec3 position)
{
	/*set the position*/
	this->position = position;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Sets the position of the Entity.*/
void EB_Entity3D::setPosition(float x, float y, float z)
{
	/*set the x position*/
	position.x = x;
	/*set the y position*/
	position.y = y;
	/*set the z position*/
	position.z = z;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Rotate the Entity along the X axis.*/
void EB_Entity3D::rotateX(float angle)
{
	/*rotate the model*/
	model->rotateX(angle);
	/*set the value of rotation*/
	rotation.x += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * C_Utilities::getPI())
	{
		rotation.x -= 2.0f * C_Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * C_Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Rotate the Entity along the Y axis.*/
void EB_Entity3D::rotateY(float angle)
{
	/*rotate the model*/
	model->rotateY(angle);
	/*set the value of rotation*/
	rotation.y += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * C_Utilities::getPI())
	{
		rotation.x -= 2.0f * C_Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * C_Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Rotate the Entity along the Z axis.*/
void EB_Entity3D::rotateZ(float angle)
{
	/*rotate the model*/
	model->rotateZ(angle);
	/*set the value of rotation*/
	rotation.z += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * C_Utilities::getPI())
	{
		rotation.x -= 2.0f * C_Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * C_Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Sets the scale of the Entity.*/
void EB_Entity3D::setScale(float scaleValue)
{
	/*set the scale*/
	this->scaleValue = scaleValue;
	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*Move the Entity.*/
void EB_Entity3D::move(glm::vec3 movement)
{
	/*update the position*/
	position += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the X axis.*/
void EB_Entity3D::moveX(float movement)
{
	/*update the position*/
	position.x += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the Y axis.*/
void EB_Entity3D::moveY(float movement)
{
	/*update the position*/
	position.y += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the Z axis.*/
void EB_Entity3D::moveZ(float movement)
{
	/*update the position*/
	position.z += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Update the movement speed to the new moveSpeed.*/
void EB_Entity3D::setMoveSpeed(float moveSpeed)
{
	/*set the move speed*/
	this->moveSpeed = moveSpeed;
}

/**************************************************************************************************************/

/*Get the position.*/
glm::vec3 EB_Entity3D::getPosition()
{
	/*return the position*/
	return position;
}

/**************************************************************************************************************/

/*Get the orientation.*/
glm::vec3 EB_Entity3D::getOrientation()
{
	/*return the rotation*/
	return rotation;
}

/**************************************************************************************************************/

/*Get the scale.*/
float EB_Entity3D::getScale()
{
	/*return the scale*/
	return scaleValue;
}