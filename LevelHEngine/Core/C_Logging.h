#pragma once

#include <string>
#include <SDL.h>
#include "../Maths/M_Vec2.h"

/**
@brief Contains core logging functions for use within the code.
@author Jamie Slowgrove
*/
namespace C_Logging
{
	/**
	@brief Logs the information message.
	@param message The message.
	*/
	void logI(std::string message);

	/**
	@brief Logs the error message.
	@param message The message.
	*/
	void logE(std::string message);
}