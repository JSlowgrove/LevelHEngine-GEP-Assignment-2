#pragma once

#include <string>
#include <vector>

/**
@brief A namespace that contains functions to use loadPNG to create screenshots.
*/
namespace Screenshot
{
	void exportPNG(std::string filename, std::vector<unsigned char>& image, unsigned int width, unsigned int height);

	void generateScreenshot();
}