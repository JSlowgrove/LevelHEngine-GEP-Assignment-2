#include "WindowFrame.h"

namespace Core
{

	WindowFrame::WindowFrame(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate) 
		: title(title), windowPos(windowPos), windowRes(windowRes), fullscreen(fullscreen), frameRate(frameRate)
	{
		//Log window details
		Logging::logI("Window title: " + title);
		Logging::logI("Window position: " + std::to_string(int(windowPos.x)) + ", " + std::to_string(int(windowPos.y)));
		Logging::logI("Window resolution: " + std::to_string(int(windowRes.x)) + ", " + std::to_string(int(windowRes.y)));
		Logging::logI("Window fullscreen: " + Logging::boolToString(fullscreen));
		Logging::logI("Window frame rate: " + std::to_string(frameRate));
	}

	WindowFrame::~WindowFrame()
	{
	}

	void WindowFrame::setWindow(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate)
	{
		setTitle(title);
		setWindowPos(windowPos);
		setWindowRes(windowRes);
		setFullscreen(fullscreen);
		setFrameRate(frameRate);
	}

	void WindowFrame::setTitle(std::string title)
	{
		this->title = title;
	}
	
	void WindowFrame::setWindowPos(Maths::Vec2 windowPos)
	{
		this->windowPos = windowPos;
	}

	void WindowFrame::setWindowRes(Maths::Vec2 windowRes)
	{
		this->windowRes = windowRes;
	}

	void WindowFrame::setFullscreen(bool fullscreen)
	{
		this->fullscreen = fullscreen;
	}

	void WindowFrame::setFrameRate(float frameRate)
	{
		this->frameRate = frameRate;
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

}// End of Core namespace