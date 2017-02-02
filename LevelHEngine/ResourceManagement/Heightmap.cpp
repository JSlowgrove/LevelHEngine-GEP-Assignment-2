#include "Heightmap.h"

Heightmap::Heightmap(std::string mapFileLocation)
{
	initaliseHeightmap(mapFileLocation);
}

Heightmap::~Heightmap()
{
}

void Heightmap::initaliseHeightmap(std::string mapFileLocation)
{
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
	float displayScale = 12.8f;
	float colourScale = 255.0f;

	//creates and array for the vertices of the height map
	std::vector<Vec3> mapVertices;
	mapPointsVertex.resize(height*width);
	mapPointsNormal.resize(height*width);
	mapPointsColour.resize(height*width);

	for (float y = 0; y < height; y++) //loop every row
	{
		for (float x = 0; x < width; x++)// loop every column
		{
			uint32_t offset = (y*width + x) * bpp; //set the offset using the bits per pixel

												   /*fill the current vector with the current y and x value and scale and move it to be in a better position
												   and get the value of the colour and use it as the z value and scale it to make it fit better*/
			mapPointsVertex[index] = Vec3((y * positionScale) - displayScale, (x * positionScale) - displayScale, getPixel(x, y, bpp, map) * heightScale);

			//set the colour of the map to the colour on the image and divide it by 255 so that the number is between 0 and 1
			mapPointsColour[index] = Vec3((getPixel(x, y, bpp, map) / colourScale), (getPixel(x, y, bpp, map) / colourScale), (getPixel(x, y, bpp, map) / colourScale));

			/*if the current position is not the the last row or the last column then create an indices for the triangle,
			this check is to stop infinite triangles*/
			if (index < ((width * height) - width) && x < (height - 1))
			{
				// adds the first triangle of the current square
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + width);
				// adds the second triangle of the current square
				indices.push_back(index + width);
				indices.push_back(index + 1);
				indices.push_back(index + (width + 1));
			}
			index++;//add one to the current position in the array

		}
	}
	//create the normals for all of the triangles
	for (int i = 0; i < (width*height) - width - 1; i++)
	{
		if ((i % 2) == 0)//work out if the current index is a multiple of two and switch between the needed normal type to get accordingly
		{
			mapPointsNormal[i] = getNormal(mapPointsVertex[i], mapPointsVertex[i + 1], mapPointsVertex[i + width]);
		}
		else
		{
			mapPointsNormal[i] = getNormal(mapPointsVertex[i + width], mapPointsVertex[i + 1], mapPointsVertex[i + width + 1]);
		}
	}
}

Uint32 Heightmap::getPixel(int x, int y, uint8_t bpp, SDL_Surface* map)
{
	bpp /= 8;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)map->pixels + y * map->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
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