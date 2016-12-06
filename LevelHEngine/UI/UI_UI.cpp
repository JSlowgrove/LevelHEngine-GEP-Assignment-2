//DISCLAMER - This is a modified version of code from one of my other assignments.

#include "UI_UI.h"

UI::UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, ResourceManagment::Shader*> &shaders)
{
	//initialise the shaders for the UI
	initialiseShaders(vertexShaderFileName, fragmentShaderFileName, shaders);
}

UI::UI(std::unordered_map<std::string, ResourceManagment::Shader*> &shaders)
{
	//initialise the shaders for the UI
	initialiseShaders("2d.texture", "2d.texture", shaders);
}

void UI::initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, ResourceManagment::Shader*> &shaders)
{
	//a string for the name of the linked shader
	std::string linkedShaderName = vertexShaderFileName + "/" + fragmentShaderFileName;

	//test if the shader has already been loaded
	if (shaders.count(linkedShaderName) == 0)
	{
		//load the shader
		shaders[linkedShaderName] = new ResourceManagment::Shader(vertexShaderFileName, fragmentShaderFileName);
	}
	else
	{
		//print out that it is already loaded
		Core::Logging::logE(linkedShaderName + " shader already loaded.");
	}
	//initialise the object
	shader = shaders[linkedShaderName];
}

UI::~UI()
{
}
