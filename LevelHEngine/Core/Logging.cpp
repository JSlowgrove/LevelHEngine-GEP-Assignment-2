#include "Logging.h"

#include <SDL.h>
#include <fstream>
#include <time.h>

namespace Logging
{

	void logI(std::string message)
	{
		logI(message, true);
	}

	void logE(std::string message)
	{
		logE(message, true);
	}

	void logMat4(Mat4 testMat)
	{
		logMat4(testMat, true);
	}

	void logI(std::string message, bool printToLog)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
		if (printToLog)
		{
			printToLogFile("INFO: " + message);
		}
	}

	void logE(std::string message, bool printToLog)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
		if (printToLog)
		{
			printToLogFile("ERROR: " + message);
		}
	}

	void logMat4(Mat4 testMat, bool printToLog)
	{
		std::string outString = "MAT4:\n";
		outString += std::to_string(testMat.m[0]) + " ";
		for (int i = 1; i < 16; i++)
		{
			outString += std::to_string(testMat.m[i]) + " ";
			if (i == 3 || i == 7 || i == 11)
			{
				outString += "\n";
			}
		}

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", outString.c_str());
		if (printToLog)
		{
			printToLogFile("INFO: " + outString);
		}
	}

	void printToLogFile(std::string message)
	{
		//Open the file to have text appended to it
		std::ofstream file;
		file.open("log.txt", std::ios_base::app);

		if (file.is_open())
		{
			//Write the message to the file with a new line
			file << message;
			file << "\n";

			//Close the file
			file.close();
		}
		else
		{
			logE("Unable to open scores file", false);
		}
	}

	std::string getCurrentDateAndTime()
	{
		//Get date/time based on current system
 		time_t currentDateTime = time(NULL);
 
 		//Convert to C-String
 		char str[26];
 		ctime_s(str, sizeof str, &currentDateTime);
 
 		return std::string(str);
	}

	std::string boolToString(bool booleanIn)
	{
		return booleanIn ? "True" : "False";
	}

}