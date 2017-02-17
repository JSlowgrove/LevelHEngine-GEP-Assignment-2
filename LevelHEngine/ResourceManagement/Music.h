#pragma once

#include <string>
#include <SDL_mixer.h>

/**
@brief Handles music using SDL_Mixer.
*/
class Music
{
public:
	/**
	@brief Constructs the Music object.
	@param file The file to be loaded.
	*/
	Music(std::string file);

	/**
	@brief Destructs the Music object.
	*/
	~Music();

	/**
	@brief Starts the Music playing, also checks if not playing and starts again.
	*/
	void startMusic();

	/**
	@brief Stops the Music playing.
	*/
	void stopMusic();

	/**
	@brief Mute the Music.
	*/
	void muteMusic();

	/**
	@brief Un-mute the Music.
	*/
	void unmuteMusic();

private:
	///Variable for the music.
	Mix_Music* music;
};