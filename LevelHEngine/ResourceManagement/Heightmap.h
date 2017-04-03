#pragma once

#include <SDL.h>
#include <vector>
#include "../Maths/Vec3.h"

/**
@brief Generates a mesh using a Heightmap for use with a renderer.
*/
namespace Heightmap
{
	/**
	@brief Initalises a heightmap.
	@param mapFileLocation The map files location.
	@param vertices A referecne to vertices vector.
	@param vertexNormals A referecne to vertex Normals vector.
	@param vertexTextures A referecne to vertex Textures vector.
	@param indices A referecne to indices vector.
	*/
	void initaliseHeightmap(std::string mapFileLocation, std::vector<float> &vertices,
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures, std::vector<unsigned int> &indices);

	/**
	@brief A function to get a pixel from a map.
	@param x The x position of the pixel.
	@param y The y position of the pixel.
	@param bpp The bits per pixel.
	@param nap A pointer to the map to search.
	@returns A pixel.
	*/
	Uint32 getPixel(int x, int y, uint8_t bpp, SDL_Surface* map);

	/**
	@brief A function to get a normal from 3 vectors.
	@param a Vector A.
	@param B Vector B.
	@param c Vector C.
	@returns A normal of the 3 vectors
	*/
	Vec3 getNormal(Vec3 a, Vec3 b, Vec3 c);
};