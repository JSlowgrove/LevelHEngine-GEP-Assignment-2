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
class Heightmap
{
public:
	Heightmap(std::string mapFileLocation);
	~Heightmap();

private:
	void initaliseHeightmap(std::string mapFileLocation);
	Uint32 getPixel(int x, int y, uint8_t bpp, SDL_Surface* map);
	Vec3 getNormal(Vec3 a, Vec3 b, Vec3 c);

	std::vector<Vec3> mapPointsVertex;//the vertex array for height map
	std::vector<Vec3> mapPointsNormal;//the normals array for height map
	std::vector<Vec3> mapPointsColour;//the colour array for height map
	std::vector<int> indices; //the array of indices to draw the height map
};