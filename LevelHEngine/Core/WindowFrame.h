#pragma once

#include <string>
#include "Logging.h"
#include "../Maths/Vec2.h"

/**
@brief The namespace for all core code.
*/
namespace Core
{
	/**
	@brief Contains details and functions for use with the window.
	@author Jamie Slowgrove
	*/
	class WindowFrame
	{
	public:
		/**
		@brief Constructs WindowFrame.
		@param title The tile.
		@param windowPos The window position.
		@param windowRes The window resolution.
		@param fullscreen The boolean for fullscreen.
		@param frameRate The frame rate for the window.
		*/
		WindowFrame(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate);

		/**
		@brief Destructs WindowFrame.
		*/
		~WindowFrame();

		/**
		@brief Sets the window details.
		@param title The tile.
		@param windowPos The window position.
		@param windowRes The window resolution.
		@param fullscreen The boolean for fullscreen.
		@param frameRate The frame rate for the window.
		*/
		void setWindow(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate);

		/**
		@brief Sets the title of the window.
		@param title The tile.
		*/
		void setTitle(std::string title);

		/**
		@brief Sets the position of the window.
		@param windowPos The window position.
		*/
		void setWindowPos(Maths::Vec2 windowPos);

		/**
		@brief Sets the resolution of the window.
		@param windowRes The window size.
		*/
		void setWindowRes(Maths::Vec2 windowRes);

		/**
		@brief Sets if the window should be fullscreen.
		@param fullscreen The boolean for fullscreen.
		*/
		void setFullscreen(bool fullscreen);

		/**
		@brief Sets the frame rate of the window.
		@param frameRate The frame rate for the window.
		*/
		void setFrameRate(float frameRate);

		/**
		@brief Gets the title of the window.
		@returns The tile.
		*/
		std::string getTitle();
		
		/**
		@brief Gets the position of the window.
		@returns The window position.
		*/
		Maths::Vec2 getWindowPos();

		/**
		@brief Gets the size of the window.
		@returns The window resolution.
		*/
		Maths::Vec2 getWindowRes();

		/**
		@brief Gets if the window should be fullscreen.
		@returns The boolean for fullscreen.
		*/
		bool getFullscreen();

		/**
		@brief Gets the frame rate of the window.
		@returns The frame rate for the window.
		*/
		float getFrameRate();

	private:
		///The window title.
		std::string title;
		///The position of the window.
		Maths::Vec2 windowPos;
		///The resolution of the window.
		Maths::Vec2 windowRes;
		///A boolean for if the window should be fullscreen.
		bool fullscreen;
		///The wanted frame rate of the window.
		float frameRate;
	};

}// End of Core namespace