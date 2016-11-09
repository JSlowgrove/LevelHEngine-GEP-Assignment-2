#include "Logging.h"

namespace Core
{

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

		void logI(std::string message, bool printToLog)
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
			if (printToLog)
			{
				printToLogFile("INFO: " + message);
			}
		}

		void logE(std::string message, bool printToLog)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
			if (printToLog)
			{
				printToLogFile("ERROR: " + message);
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

	}//End of Logging namespace

}//End of Core namespace