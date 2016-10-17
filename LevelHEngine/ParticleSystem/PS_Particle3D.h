#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "gl/glew.h"
#include "../Core/C_Utilities.h"
#include "../Enitites/Base/EB_Entity3D.h"

/**
@brief Creates a Particle object that inherits Entity.
@author Jamie Slowgrove
*/
class PS_Particle3D : public EB_Entity3D
{
private:
	/**The direction of the Particle*/
	glm::vec3 direction;

public:
	/**
	Constructs a Particle Object.
	Creates a Particle Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A pointer to the model.
	@param scaleValue The scale of the Model.
	@param direction The direction of the Particle
	@param moveSpeed The move speed of the particle
	*/
	PS_Particle3D(RM_Model* model, float scaleValue, glm::vec3 direction, float moveSpeed);

	/**
	Destructs a Particle Object.
	Destructs the Particle Object deleting the Particle Object from memory.
	*/
	~PS_Particle3D();

	/**
	A function that updates the Particle
	@param dt The delta time.
	*/
	void update(float dt);
};
