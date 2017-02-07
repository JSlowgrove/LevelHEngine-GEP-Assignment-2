#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "../Maths/Vec3.h"
#include "../Core/Logging.h"

//Generates a mesh using a Heightmap for use with a renderer.
namespace Heightmap
{
	void initaliseHeightmap(std::string mapFileLocation, std::vector<float> &vertices,
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures, std::vector<unsigned int> &indices);
	Uint32 getPixel(int x, int y, uint8_t bpp, SDL_Surface* map);
	Vec3 getNormal(Vec3 a, Vec3 b, Vec3 c);
};