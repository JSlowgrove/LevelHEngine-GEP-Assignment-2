#include "Heightmap.h"

#include <SDL_image.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include "../Core/Logging.h"

void Heightmap::initaliseHeightmap(std::string mapFileLocation, std::vector<float> &vertices,
	std::vector<float> &vertexNormals, std::vector<float> &vertexTextures, std::vector<unsigned int> &indices)
{
	std::vector<Vec3> mapPointsVertex;//the vertex array for height map

	//Loads the image as a surface
	SDL_Surface* map = IMG_Load(mapFileLocation.c_str());

	//Image load check
	if (!map)
	{
		//Error message
		std::string message = "Unable to load image from: " + mapFileLocation + ", Error is: " + IMG_GetError();
		Logging::logE(message);
		return;
	}

	//get the image format
	SDL_PixelFormat* mapformat = map->format;

	//loads the bits per pixel, height and width to new variables.
	uint8_t bpp = mapformat->BitsPerPixel;
	int height = map->h;
	int width = map->w;

	//declares the variables needed for the height map
	uint32_t index = 0;
	float heightScale = 0.05f;
	float positionScale = 0.1f;
	float displayScale = (positionScale * width) * 0.5f;

	//creates and array for the vertices of the height map
	mapPointsVertex.resize(height*width);
	
	for (int y = 0; y < height; y++) //loop every row
	{
		for (int x = 0; x < width; x++)// loop every column
		{
			Uint8 redChannel;
			Uint8 greenChannel;
			Uint8 blueChannel;
			Uint8 alphaChannel;

			Uint32 rawPixelData = getPixel(int(x), int(y), bpp, map);
			SDL_GetRGBA(rawPixelData, map->format, &redChannel, &greenChannel, &blueChannel, &alphaChannel);

			/*fill the current vector with the current y and x value and scale and move it to be in a better position
			and get the value of the colour and use it as the z value and scale it to make it fit better*/
			mapPointsVertex[index] = Vec3((y * positionScale) - displayScale, (x * positionScale) - displayScale, redChannel * heightScale);
			vertices.push_back((y * positionScale) - displayScale);
			vertices.push_back((x * positionScale) - displayScale);
			vertices.push_back(redChannel * heightScale);

			//generate the texture coordinates for the heightmap
			vertexTextures.push_back(float(x) * (1.0f / width));
			vertexTextures.push_back(float(height - y) * (1.0f / height));

			/*if the current position is not the the last row or the last column then create an indices for the triangle,
			this check is to stop infinite triangles*/
			if (index < uint32_t(((width * height) - width)) && x < (height - 1))
			{
				// adds the first triangle of the current square
				indices.push_back(index);
				indices.push_back(index + width);
				indices.push_back(index + width + 1);
				// adds the second triangle of the current square
				indices.push_back(index);
				indices.push_back(index + width + 1);
				indices.push_back(index + 1);
			}
			
			index++;//add one to the current position in the array
			
		}
	}
	
	//create the normals for all of the triangles
	for (int i = 0; i < width * height; i++)
	{
		if (i >= (width*height) - width - 1) //quick hack to get normal array size to match vertices array
		{
			vertexNormals.push_back(mapPointsVertex[i].x);
			vertexNormals.push_back(mapPointsVertex[i].y);
			vertexNormals.push_back(mapPointsVertex[i].z);
		}
		else if ((i % 2) == 0)//work out if the current index is a multiple of two and switch between the needed normal type to get accordingly
		{
			Vec3 norm = getNormal(mapPointsVertex[i], mapPointsVertex[i + 1], mapPointsVertex[i + width]);
			vertexNormals.push_back(norm.x);
			vertexNormals.push_back(norm.y);
			vertexNormals.push_back(norm.z);
		}
		else
		{
			Vec3 norm = getNormal(mapPointsVertex[i + width], mapPointsVertex[i + 1], mapPointsVertex[i + width + 1]);
			vertexNormals.push_back(norm.x);
			vertexNormals.push_back(norm.y);
			vertexNormals.push_back(norm.z);
		}
	}
}

Uint32 Heightmap::getPixel(int x, int y, uint8_t bpp, SDL_Surface* map)
{
	bpp /= 8;

	int pixelIndex = y * map->w + x;

	/* Here p is the address to the pixel we want to retrieve */
	//Uint8 *p = (Uint8 *)map->pixels + y * map->pitch + x * bpp;
	Uint8* p = (Uint8*)map->pixels + pixelIndex * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

Vec3 Heightmap::getNormal(Vec3 a, Vec3 b, Vec3 c) //a function to work out the normals for the map
{
	//*******************************
	//***	C **************************
	//***	  |\ ***********************
	//***	^ | \ **********************
	//***	| |  \ *********************
	//***	  ----- ********************
	//***	A -----> B *****************
	//********************************

	Vec3 ab = b - a; //up
	Vec3 ac = c - a; //right

	Vec3 normals;
	normals.x = (ac.y*ab.z) - (ac.z*ab.y);//work out the x of the normal
	normals.y = -((ab.z*ac.x) - (ab.x*ac.z));//work out the y of the normal
	normals.z = (ac.x*ab.y) - (ac.y*ab.x);//work out the z of the normal

	//the factor that I need to divide by to work out the normal
	float factor = sqrt((normals.x*normals.x) + (normals.y*normals.y) + (normals.z*normals.z));

	//works out the normals
	normals.x = normals.x / factor;
	normals.y = normals.y / factor;
	normals.z = normals.z / factor;

	return normals;// returns the normal
}
