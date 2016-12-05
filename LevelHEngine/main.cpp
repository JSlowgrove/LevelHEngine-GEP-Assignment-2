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

	///The application instance 
	std::shared_ptr<Core::Application> application = std::make_shared<Core::Application>("Level H Engine", Maths::Vec2(700, 200), Maths::Vec2(640, 480), false, 60.0f);

	///Run the application
	application->run(argc, argv);

	///Destroy the application
	application->destroy();

	return 0;
}