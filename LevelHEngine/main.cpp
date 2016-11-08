#include "Core/C_Application.h"

///Forces the game to run on the NIVDIA GPU, if one is available.
///http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

///The application instance 
C_Application* application = new C_Application();

int main(int argc, char *argv[])
{
	application->init(argc, argv);
	application->run();
	application->destroy();
	delete application;
	return 0;
}