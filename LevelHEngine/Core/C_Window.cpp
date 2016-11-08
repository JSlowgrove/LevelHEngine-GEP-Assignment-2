#include "C_Window.h"

C_Window::C_Window(std::string title, M_Vec2 targetRes, M_Vec2 windowPos, M_Vec2 windowSize, bool fullscreen) :
	title(title), targetRes(targetRes), windowPos(windowPos), windowSize(windowSize), fullscreen(fullscreen)
{
}

C_Window::~C_Window()
{
}

void C_Window::setWindow(std::string title, M_Vec2 targetRes, M_Vec2 windowPos, M_Vec2 windowSize, bool fullscreen)
{
	setTitle(title);
	setTargetResoultion(targetRes);
	setWindowPos(windowPos);
	setWindowSize(windowSize);
	setFullscreen(fullscreen);
}

void C_Window::setTitle(std::string title)
{
	this->title = title;
}

void C_Window::setTargetResoultion(M_Vec2 targetRes)
{
	this->targetRes = targetRes;
}

void C_Window::setWindowPos(M_Vec2 windowPos)
{
	this->windowPos = windowPos;
}

void C_Window::setWindowSize(M_Vec2 windowSize)
{
	this->windowSize = windowSize;
}

void C_Window::setFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
}

std::string C_Window::getTitle()
{
	return title;
}

M_Vec2 C_Window::getTargetResoultion()
{
	return targetRes;
}

M_Vec2 C_Window::getWindowPos()
{
	return windowPos;
}

M_Vec2 C_Window::getWindowSize()
{
	return windowSize;
}

bool C_Window::getFullscreen()
{
	return fullscreen;
}