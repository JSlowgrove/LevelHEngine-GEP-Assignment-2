#include "WindowFrame.h"

#include "Logging.h"

std::string WindowFrame::title;
Vec2 WindowFrame::windowPos;
Vec2 WindowFrame::windowRes;
bool WindowFrame::fullscreen;
float WindowFrame::frameRate;

void WindowFrame::setWindow(std::string inTitle, Vec2 inWindowPos, Vec2 inWindowRes, bool inFullscreen, float inFrameRate)
{
	setTitle(inTitle);
	setWindowPos(inWindowPos);
	setWindowRes(inWindowRes);
	setFullscreen(inFullscreen);
	setFrameRate(inFrameRate);

	//Log window details
	Logging::logI("Window title: " + title);
	Logging::logI("Window position: " + std::to_string(int(windowPos.x)) + ", " + std::to_string(int(windowPos.y)));
	Logging::logI("Window resolution: " + std::to_string(int(windowRes.x)) + ", " + std::to_string(int(windowRes.y)));
	Logging::logI("Window fullscreen: " + Logging::boolToString(fullscreen));
	Logging::logI("Window frame rate: " + std::to_string(frameRate));
}

void WindowFrame::setTitle(std::string inTitle)
{
	WindowFrame::title = inTitle;
}
	
void WindowFrame::setWindowPos(Vec2 inWindowPos)
{
	WindowFrame::windowPos = inWindowPos;
}

void WindowFrame::setWindowRes(Vec2 inWindowRes)
{
	WindowFrame::windowRes = inWindowRes;
}

void WindowFrame::setFullscreen(bool inFullscreen)
{
	WindowFrame::fullscreen = inFullscreen;
}

void WindowFrame::setFrameRate(float inFrameRate)
{
	WindowFrame::frameRate = inFrameRate;
}

std::string WindowFrame::getTitle()
{
	return title;
}

Vec2 WindowFrame::getWindowPos()
{
	return windowPos;
}

Vec2 WindowFrame::getWindowRes()
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