#pragma once

#include <SDL.h>
#include <vector>
#include "../../Maths/Vec2.h"
#include "Node.h"

/**
@brief Creates an object for A* path finding.
*/
class AStar
{
public:
	/**
	@brief Constructs the AStar object.
	@param xNodes The number of nodes in a row.
	@param yNodes The number of rows in the map.
	@param nodeWidth The width of a node.
	@param nodeHeight The height of a node.
	*/
	AStar(int inXNodes, int inYNodes, float inNodeWidth, float inNodeHeight);

	/**
	@brief Destructs the AStar object.
	*/
	~AStar();

	/**
	@brief Sets the Node at the inputed index to a danger Node.
	@param nodeXIndex The x index of the Node.
	@param nodeYIndex The y index of the Node.
	*/
	void setDangerNode(int inNodeXIndex, int inNodeYIndex);

	/**
	@brief Sets the Node at the inputed index to a safe Node.
	@param nodeXIndex The x index of the Node.
	@param nodeYIndex The y index of the Node.
	*/
	void setSafeNode(int inNodeXIndex, int inNodeYIndex);

	/**
	@brief Finds a new path to follow.
	@param startX The start x index value.
	@param startY The start y index value.
	@param endX The end x index value.
	@param endY The end y index value.
	*/
	void findNewPath(int inStartX, int inStartY, int inEndX, int inEndY);

	/**
	@brief Gets the position of the next node in the path.
	@returns The Node position.
	*/
	Vec2 getNextPathNode();

	/**
	@brief Displays the open and closed lists.
	@param renderer A pointer to the renderer.
	*/
	void drawLists(SDL_Renderer* renderer);

private:
	///The arrays of Nodes.
	std::vector<std::vector<Node*>> nodes;
	///The open list of Nodes.
	std::vector<Node> openList;
	///The closed list of Nodes.
	std::vector<Node> closedList;
	///The array of Nodes for the best path.
	std::vector<Node> bestPath;
	///The number of nodes.
	int xNodes, yNodes;
	///The current node index.
	int currentX, currentY;
	///The end node index.
	int endX, endY;
	///The start node index.
	int startX, startY;
	///The Dimensions of a node.
	Vec2 nodeDimensions;

	/**
	@brief Check the surrounding nodes.
	@param parentX The parent node x index value.
	@param parentY The parent node y index value.
	*/
	void checkNodes(int parentX, int parentY);

	/**
	@brief Test the node for the open list setup.
	@param parentX The parent x index value.
	@param parentY The parent y index value.
	@param testX The test x index value.
	@param testY The test y index value.
	@param cost The cost to add to the node.
	*/
	void nodeTest(int parentX, int parentY, int testX, int testY, int cost);

	/**
	Find the next node.
	*/
	void findNextNode();

	/**
	@brief Find the best path.
	*/
	void findBestPath();
};