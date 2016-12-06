#pragma once

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Audio.h"
#include "Music.h"
#include "Shader.h"
#include "Object.h"

/**
@brief The namespace for all resource management code.
*/
namespace ResourceManagment
{

	/**
	@brief Contains static variables and functions for use with resource manager.
	*/
	class ResourceManager
	{
	public:

		/**
		@brief A static function to delete all the resources
		*/
		static void deleteResources();

		/**
		@brief A static function to delete all the objects
		*/
		static void deleteAllObjects();

		/**
		@brief A static function to delete all the shaders
		*/
		static void deleteAllShaders();

		/**
		@brief A static function to delete all the audio
		*/
		static void deleteAllAudio();

		/**
		@brief A static function to delete all the music
		*/
		static void deleteAllMusic();

		/**
		@brief A static function to delete the object
		@param id The ID of the file.
		*/
		static void deleteObject(std::string id) { objects.erase(id); }

		/**
		@brief A static function to delete the shader
		@param id The ID of the file.
		*/
		static void deleteShader(std::string id) { shaders.erase(id); }

		/**
		@brief A static function to delete the music
		@param id The ID of the file.
		*/
		static void deleteMusic(std::string id) { music.erase(id); }

		/**
		@brief A static function to delete the audio
		@param id The ID of the file.
		*/
		static void deleteAudio(std::string id) { audio.erase(id); }

		/**
		@brief A static function to initialise a vertex array object without a material.
		@param objFileName The name of the obj file.
		@returns The ID of the loaded file.
		*/
		static std::string initialiseObject(std::string objFileName);

		/**
		@brief Initialise a vertex array object.
		@param objFileName The name of the obj file.
		@returns The ID of the loaded file.
		*/
		static std::string initialiseObject(std::string objFileName, std::string materialFileName);

		/**
		@brief Initialise a shader.
		@param vertexShaderFileName The name of the vertex shader file.
		@param fragmentShaderFileName The name of the fragment shader file.
		@returns The ID of the loaded file.
		*/
		static std::string initialiseShader(std::string vertexShaderFileName, std::string fragmentShaderFileName);

		/**
		@brief A static function to initialise an audio file.
		@param objFileName The name of the audio file.
		@returns The ID of the loaded file.
		*/
		static std::string initialiseAudio(std::string audioFileName);

		/**
		@brief A static function to initialise a music file.
		@param objFileName The name of the music file.
		@returns The ID of the loaded file.
		*/
		static std::string initialiseMusic(std::string musicFileName);

		/**
		@brief A static function to get an object.
		@param id The ID of the file.
		*/
		static Object* getObject(std::string id) { return objects[id]; }

		/**
		@brief A static function to get an shaders.
		@param id The ID of the file.
		*/
		static Shader* getShaders(std::string id) { return shaders[id]; }

		/**
		@brief A static function to get an audio.
		@param id The ID of the file.
		*/
		static Audio* getAudio(std::string id) { return audio[id]; }

		/**
		@brief A static function to get an music.
		@param id The ID of the file.
		*/
		static Music* getMusic(std::string id) { return music[id]; }

		
	private:
		///The loaded Object files
		static std::unordered_map<std::string, Object*> objects;
		///The loaded Shader files
		static std::unordered_map<std::string, Shader*> shaders;
		///The loaded Audio files
		static std::unordered_map<std::string, Audio*> audio;
		///The loaded Music files
		static std::unordered_map<std::string, Music*> music;
	};

}// End of resource management namespace