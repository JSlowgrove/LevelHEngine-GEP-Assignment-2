#include "Music.h"

namespace Core
{

	Music::Music(std::string file)
	{
		//Load music from file
		music = Mix_LoadMUS(file.c_str());
		if (music == NULL)
		{
			//Failed loading file
			Core::Logging::logE("Failed to load " + file + ", Error is: " + std::string(Mix_GetError()));
		}
	}

	Music::~Music()
	{
		//Free the audio
		Mix_FreeMusic(music);
		music = NULL;
		//Delete the pointers
		delete music;
	}

	void Music::startMusic()
	{
		//If there is no music playing
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(music, -1);
		}
	}

	void Music::stopMusic()
	{
		//Stops the music
		Mix_HaltMusic();
	}

	void Music::muteMusic()
	{
		//Mutes the music
		Mix_VolumeMusic(0);
	}

	void Music::unmuteMusic()
	{
		//Un-mutes the music
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	}

}// End of Core namespace