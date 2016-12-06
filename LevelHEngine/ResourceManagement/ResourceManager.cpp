#include "ResourceManager.h"

namespace ResourceManagment
{

	std::unordered_map<std::string, Object*> ResourceManager::objects;
	std::unordered_map<std::string, Shader*> ResourceManager::shaders;
	std::unordered_map<std::string, Audio*> ResourceManager::audio;
	std::unordered_map<std::string, Music*> ResourceManager::music;

	void ResourceManager::deleteResources()
	{
		deleteAllObjects();
		deleteAllShaders();
		deleteAllAudio();
		deleteAllMusic();
	}

	void ResourceManager::deleteAllObjects()
	{
		for (auto i = objects.begin(); i != objects.end(); ++i)
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

	std::string ResourceManager::initialiseObject(std::string objFileName)
	{
		//test if the object has already been loaded
		if (objects.count(objFileName) == 0)
		{
			//load the object
			objects[objFileName] = new Object(objFileName);
		}
		else
		{
			//print out that it is already loaded
			Core::Logging::logI(objFileName + " object already loaded.");
		}
		//return the ID
		return objFileName;
	}

	std::string ResourceManager::initialiseObject(std::string objFileName, std::string materialFileName)
	{
		//a string for the name of the linked object
		std::string linkedObjName = objFileName + "/" + materialFileName;

		//test if the object has already been loaded
		if (objects.count(linkedObjName) == 0)
		{
			//load the object
			objects[linkedObjName] = new Object(objFileName, materialFileName);
		}
		else
		{
			//print out that it is already loaded
			Core::Logging::logI(linkedObjName + " object already loaded.");
		}
		//return the ID
		return linkedObjName;
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
			Core::Logging::logI(linkedShaderName + " shader already loaded.");
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
			Core::Logging::logI(audioFileName + " audio already loaded.");
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
			Core::Logging::logI(musicFileName + " music already loaded.");
		}
		//return the ID
		return musicFileName;
	}

}// End of resource management namespace