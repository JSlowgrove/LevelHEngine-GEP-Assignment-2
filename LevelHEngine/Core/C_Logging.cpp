#include "C_Logging.h"

namespace C_Logging
{
	void logI(std::string message)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
	}

	void logE(std::string message)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
	}
}