#include "ResourceManager.h"

#include <SDL.h>
#include <vector>
#include "../Core/Logging.h"

std::unordered_map<std::string, Mesh*> ResourceManager::meshes;
std::unordered_map<std::string, Shader*> ResourceManager::shaders;
std::unordered_map<std::string, Audio*> ResourceManager::audio;
std::unordered_map<std::string, Music*> ResourceManager::music;

void ResourceManager::deleteResources()
{
	deleteAllMeshes();
	deleteAllShaders();
	deleteAllAudio();
	deleteAllMusic();
}

void ResourceManager::deleteAllMeshes()
{
	for (auto i = meshes.begin(); i != meshes.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceManager::deleteAllShaders()
{
	for (auto i = shaders.begin(); i != shaders.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceManager::deleteAllAudio()
{
	for (auto i = audio.begin(); i != audio.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceManager::deleteAllMusic()
{
	for (auto i = music.begin(); i != music.end(); ++i)
	{
		delete i->second;
	}
}

std::string ResourceManager::initialisePrimitive(Primitives::PrimativeType primType)
{
	std::string primName = "type " + std::to_string(primType) + "primitive";

	//test if the mesh has already been loaded
	if (meshes.count(primName) == 0)
	{
		//load the mesh
		meshes[primName] = new Mesh(primType);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(primName + " already loaded.");
	}
	//return the ID
	return primName;
}

std::string ResourceManager::initialiseHeightmap(std::string heightmapFileName)
{
	//test if the mesh has already been loaded
	if (meshes.count(heightmapFileName) == 0)
	{
		//load the mesh
		meshes[heightmapFileName] = new Mesh(heightmapFileName, true);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(heightmapFileName + " heightmap already loaded.");
	}
	//return the ID
	return heightmapFileName;
}

std::string ResourceManager::initialiseHeightmap(std::string heightmapFileName, std::string materialFileName)
{
	//a string for the name of the linked mesh
	std::string linkedMeshName = heightmapFileName + "/" + materialFileName;

	//test if the object has already been loaded
	if (meshes.count(linkedMeshName) == 0)
	{
		//load the object
		meshes[linkedMeshName] = new Mesh(heightmapFileName, materialFileName, true);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(linkedMeshName + " mesh already loaded.");
	}
	//return the ID
	return linkedMeshName;
}

std::string ResourceManager::initialiseMesh(std::string objFileName)
{
	//test if the mesh has already been loaded
	if (meshes.count(objFileName) == 0)
	{
		//load the mesh
		meshes[objFileName] = new Mesh(objFileName);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(objFileName + " mesh already loaded.");
	}
	//return the ID
	return objFileName;
}

std::string ResourceManager::initialiseMesh(std::string objFileName, std::string materialFileName)
{
	//a string for the name of the linked mesh
	std::string linkedMeshName = objFileName + "/" + materialFileName;

	//test if the object has already been loaded
	if (meshes.count(linkedMeshName) == 0)
	{
		//load the object
		meshes[linkedMeshName] = new Mesh(objFileName, materialFileName);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(linkedMeshName + " mesh already loaded.");
	}
	//return the ID
	return linkedMeshName;
}

std::string ResourceManager::initialiseShader(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	//a string for the name of the linked shader
	std::string linkedShaderName = vertexShaderFileName + "/" + fragmentShaderFileName;

	//test if the shader has already been loaded
	if (shaders.count(linkedShaderName) == 0)
	{
		//load the shader
		shaders[linkedShaderName] = new Shader(vertexShaderFileName, fragmentShaderFileName);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(linkedShaderName + " shader already loaded.");
	}
	//return the ID
	return linkedShaderName;
}

std::string ResourceManager::initialiseAudio(std::string audioFileName)
{
	//test if the audio has already been loaded
	if (audio.count(audioFileName) == 0)
	{
		//load the audio
		audio[audioFileName] = new Audio(audioFileName);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(audioFileName + " audio already loaded.");
	}
	//return the ID
	return audioFileName;
}

std::string ResourceManager::initialiseMusic(std::string musicFileName)
{
	//test if the music has already been loaded
	if (music.count(musicFileName) == 0)
	{
		//load the music
		music[musicFileName] = new Music(musicFileName);
	}
	else
	{
		//print out that it is already loaded
		Logging::logI(musicFileName + " music already loaded.");
	}
	//return the ID
	return musicFileName;
}