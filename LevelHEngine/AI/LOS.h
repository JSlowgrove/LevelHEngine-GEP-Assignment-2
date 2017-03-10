#pragma once

#include <SDL.h>
#include <vector>
#include "../Maths/Vec2.h"
#include "Node.h"

/**
@brief A Namespace that contains functions for the Line Of Sight.
*/
namespace LOS
{
	/**
	@brief Check if two positions can see each other.
	@param a Position a.
	@param b Position b.
	@param map A 2D vector of nodes. 
	@param nodeSize The size of the node.
	@return If the position can see each other.
	*/
	bool lineOfSight(Vec2 a, Vec2 b, std::vector<std::vector<Node*>> map, int nodeSize);

	/**
	@brief Check if two lines intersect.
	@param a Position a. (line 1)
	@param b Position b. (line 1)
	@param v Position c. (line 2)
	@param d Position d. (line 2)
	@param axis Axis that the second line being tested is on.
	@return If the lines intersect.
	*/
	bool lineLineIntersectionCheck(Vec2 a, Vec2 b, Vec2 c, Vec2 d, char axis);

	/**
	@brief Check if two positions can see each other and draw the tested tiles.
	@param a Position a.
	@param b Position b.
	@param map A 2D vector of nodes.
	@param nodeSize The size of the node.
	@param renderer A pointer to the renderer.
	*/
	void drawLineOfSight(Vec2 a, Vec2 b, std::vector<std::vector<Node*>> map, int nodeSize, SDL_Renderer* renderer);

	/**
	@brief Find a new target position to go to.
	@param a Position a.
	@param map A 2D vector of nodes.
	@param nodeSize The size of the node.
	@return The new target position.
	*/
	Vec2 getNewTarget(Vec2 a, std::vector<std::vector<Node*>> map, int nodeSize);
}