#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include <time.h>
#include <string.h>
#include <unordered_map>
#include "gl/glew.h"
#include "../ParticleSystem/PS_Particle3D.h"

/**A definition for the max number of particles*/
#define MAX_NUMBER_OF_PARTICLES 100

/**
@brief Creates a ParticleEffect object that handles Particle objects.
@author Jamie Slowgrove
*/
class PS_ParticleEffect3D
{
private:
	/**A vector of Particle objects*/
	std::vector<PS_Particle3D*> particles;
	/**The loaded Object files*/
	std::unordered_map<std::string, RM_Object*> objects;
	/*The loaded Shader files*/
	std::unordered_map<std::string, RM_Shader*> shaders;
	/**The name of the object for the model*/
	std::string objectName;
	/**The name of the vertex shader*/
	std::string vertexShaderName;
	/**The name of the fragment shader*/
	std::string fragmentShaderName;
	/**The move speed of the particles*/
	float moveSpeed;
	/**The position of the Particle emitter*/
	glm::vec3 emitter;
	/**A boolean for if the ParticleEffect should emit*/
	bool emit;

public:
	/**
	Constructs a ParticleEffect Object.
	@param objectName The file name of the model that the Particle will use.
	@param objects A reference to the loaded Object files
	@param shaders A reference to the loaded Shader files
	@param vertexShaderName The name of the vertex shader.
	@param fragmentShaderName The name of the fragment shader.
	@param emitter The position that the particle effect emits from.
	@param emit The new value of the emit boolean.
	*/
	PS_ParticleEffect3D(std::string fileName, std::unordered_map<std::string, RM_Object*> &objects,
		std::unordered_map<std::string, RM_Shader*> &shaders, std::string vertexShaderName, 
		std::string fragmentShaderName, glm::vec3 emitter, bool emit);

	/**
	Destructs a ParticleEffect Object.
	Destructs the ParticleEffect Object deleting the Particle Object from memory.
	*/
	~PS_ParticleEffect3D();

	/**
	A function that updates the ParticleEffect
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	Draws the ParticleEffect.
	@param viewMatrix A reference to the camera view matrix.
	@param projMatrix A reference to the camera projection matrix.
	*/
	void draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	/**
	Creates the new Particle objects.
	@param objects A reference to the loaded Object files
	@param shaders A reference to the loaded Shader files
	*/
	void makeNewParticles(std::unordered_map<std::string, RM_Object*> &objects,
		std::unordered_map<std::string, RM_Shader*> &shaders);

	/**
	Setter # The position of the emitter.
	@param emitter The new position of the emitter.
	*/
	void setEmitter(glm::vec3 emitter);

	/**
	Setter # The value of the emit boolean.
	@param emit The new value of the emit boolean.
	*/
	void setEmitting(bool emit);
};
