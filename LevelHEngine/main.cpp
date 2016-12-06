#include "Core/Application.h"
#include <memory>
#include "Core/Logging.h"

///Forces the game to run on the NIVDIA GPU, if one is available.
///http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc, char *argv[])
{
	///Log the time and date the program started
	Core::Logging::logI("Program Started: " + Core::Logging::getCurrentDateAndTime());

	///Initialise the application instance 
	Core::Application::init("Level H Engine", Maths::Vec2(60, 60), Maths::Vec2(1280, 720), false, 60.0f);

	///Run the application
	Core::Application::run(argc, argv);

	///Destroy the application
	Core::Application::destroy();

	return 0;
}