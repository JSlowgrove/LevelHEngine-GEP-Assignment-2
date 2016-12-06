#include "WindowFrame.h"

namespace Core
{

	std::string WindowFrame::title;
	Maths::Vec2 WindowFrame::windowPos;
	Maths::Vec2 WindowFrame::windowRes;
	bool WindowFrame::fullscreen;
	float WindowFrame::frameRate;

	void WindowFrame::setWindow(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate)
	{
		setTitle(title);
		setWindowPos(windowPos);
		setWindowRes(windowRes);
		setFullscreen(fullscreen);
		setFrameRate(frameRate);

		//Log window details
		Logging::logI("Window title: " + title);
		Logging::logI("Window position: " + std::to_string(int(windowPos.x)) + ", " + std::to_string(int(windowPos.y)));
		Logging::logI("Window resolution: " + std::to_string(int(windowRes.x)) + ", " + std::to_string(int(windowRes.y)));
		Logging::logI("Window fullscreen: " + Logging::boolToString(fullscreen));
		Logging::logI("Window frame rate: " + std::to_string(frameRate));
	}

	void WindowFrame::setTitle(std::string title)
	{
		WindowFrame::title = title;
	}
	
	void WindowFrame::setWindowPos(Maths::Vec2 windowPos)
	{
		WindowFrame::windowPos = windowPos;
	}

	void WindowFrame::setWindowRes(Maths::Vec2 windowRes)
	{
		WindowFrame::windowRes = windowRes;
	}

	void WindowFrame::setFullscreen(bool fullscreen)
	{
		WindowFrame::fullscreen = fullscreen;
	}

	void WindowFrame::setFrameRate(float frameRate)
	{
		WindowFrame::frameRate = frameRate;
	}

	std::string WindowFrame::getTitle()
	{
		return title;
	}

	Maths::Vec2 WindowFrame::getWindowPos()
	{
		return windowPos;
	}

	Maths::Vec2 WindowFrame::getWindowRes()
	{
		return windowRes;
	}

	bool WindowFrame::getFullscreen()
	{
		return fullscreen;
	}

	float WindowFrame::getFrameRate()
	{
		return frameRate;
	}

	float WindowFrame::getAspect()
	{
		return (windowRes.x / windowRes.y);
	}

}// End of Core namespace