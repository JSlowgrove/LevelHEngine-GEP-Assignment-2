#include "Screenshot.h"

#include "WindowFrame.h"
#include "Logging.h"
#include "../ExternalLibraries/lodepng.h"
#include <time.h>
#include <GL/glew.h>

void Screenshot::exportPNG(std::string filename, std::vector<unsigned char>& image, unsigned int width, unsigned int height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename.c_str(), image, width, height);

	//if there's an error, log it
	if (error)
	{
		Logging::logE("encoder error " + std::to_string(error) + ": " + lodepng_error_text(error));
	}
}

void Screenshot::generateScreenshot()
{
	unsigned int w = (unsigned int)WindowFrame::getWindowRes().x;
	unsigned int h = (unsigned int)WindowFrame::getWindowRes().y;

	//Get date/time based on current system
	time_t currentDateTime = time(NULL);

	//Convert to C-String
	char str[26];
	ctime_s(str, sizeof str, &currentDateTime);

	for (unsigned int i = 0; i < 26; i++)
	{
		if (str[i] == ':')
		{
			str[i] = '-';
		}
		else if (str[i] == '\n')
		{
			str[i] = ']';
		}
	}

	//use this to create a timestamped name for the screenshot
	std::string path = "Screenshots/Screenshot [" + std::string(str) +".png";

	GLint* OpenGLimage = new GLint[w * h * 4];
	glReadPixels(0.0f, 0.0f, w, h, GL_RGBA, GL_FLOAT, OpenGLimage);

	std::vector<unsigned char> pixels;
	//convert to char array
	for (unsigned int i = 0; i < w * h * 4; i++)
	{
		pixels.push_back((char)OpenGLimage[i]);
	}

	//gernerate the png screenshot
	exportPNG(path, pixels, w, h);
}
