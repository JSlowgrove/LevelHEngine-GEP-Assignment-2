//DISCLAMER - This is a modified version of code from one of my other assignments.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>
#include "../ResourceManagement/Shader.h"
#include "UI_UIObject.h"

/**
@brief A class for the 2D user interfaces.
*/
class UI
{
public:
	/**
	@brief Constructs the UI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, ResourceManagment::Shader*> &shaders);

	/**
	@brief Constructs the UI object.
	@param shaders A reference to the loaded Shader files
	*/
	UI(std::unordered_map<std::string, ResourceManagment::Shader*> &shaders);

	/**
	@brief Destructs the UI object.
	*/
	~UI();

	/**
	@brief A pure virtual function to update the UI.
	@param dt The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	@brief A pure virtual function to draw to the screen.
	*/
	virtual void draw() = 0;

protected:
	///The shader for the UI
	ResourceManagment::Shader * shader;

	/**
	@brief Initialise the shaders.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	void initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, ResourceManagment::Shader*> &shaders);
};