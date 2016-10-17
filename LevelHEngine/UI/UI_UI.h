#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>
#include "../ResourceManagement/RM_Shader.h"
#include "UI_UIObject.h"

/**
@brief A class for the 2D user interfaces.
@author Jamie Slowgrove
*/
class UI_UI
{
protected:
	/**The shader for the UI*/
	RM_Shader * shader;

	/**
	Initialise the shaders.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	void initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, RM_Shader*> &shaders);

public:
	/**
	Constructs the UI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	UI_UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, RM_Shader*> &shaders);

	/**
	Constructs the UI object.
	@param shaders A reference to the loaded Shader files
	*/
	UI_UI(std::unordered_map<std::string, RM_Shader*> &shaders);

	/**
	Destructs the UI object.
	*/
	~UI_UI();

	/**
	A pure virtual function to update the UI.
	@param dt The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	A pure virtual function to draw to the screen.
	*/
	virtual void draw() = 0;
};