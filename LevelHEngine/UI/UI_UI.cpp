#include "UI_UI.h"

/**************************************************************************************************************/

/*Constructs the UI object*/
UI_UI::UI_UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, RM_Shader*> &shaders)
{
	/*initialise the shaders for the UI*/
	initialiseShaders(vertexShaderFileName, fragmentShaderFileName, shaders);
}

/**************************************************************************************************************/

/*Constructs the UI object*/
UI_UI::UI_UI(std::unordered_map<std::string, RM_Shader*> &shaders)
{
	/*initialise the shaders for the UI*/
	initialiseShaders("2d.texture", "2d.texture", shaders);
}


/**************************************************************************************************************/

/*Initialise the shaders.*/
void UI_UI::initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, RM_Shader*> &shaders)
{
	/*a string for the name of the linked shader*/
	std::string linkedShaderName = vertexShaderFileName + "/" + fragmentShaderFileName;

	/*test if the shader has already been loaded*/
	if (shaders.count(linkedShaderName) == 0)
	{
		/*load the shader*/
		shaders[linkedShaderName] = new RM_Shader(vertexShaderFileName, fragmentShaderFileName);
	}
	else
	{
		/*print out that it is already loaded*/
		std::cout << linkedShaderName << " shader already loaded." << std::endl << std::endl;
	}
	/*initialise the object*/
	shader = shaders[linkedShaderName];
}

/**************************************************************************************************************/

/*Destructs the UI object*/
UI_UI::~UI_UI()
{
}
