#include "AStar.h"

#include "../Core/Logging.h"

AStar::AStar(int inXNodes, int inYNodes, float inNodeWidth, float inNodeHeight)
{
	//initialise variables
	xNodes = inXNodes;
	yNodes = inYNodes;
	nodeDimensions = Vec2(inNodeWidth, inNodeHeight);

	//initialise arrays
	for (int x = 0; x < inXNodes; x++)
	{
		nodes.resize(x + 1);
		for (int y = 0; y < inYNodes; y++)
		{
			//add a new node [x][y]
			nodes[x].push_back(new Node(x, y));
		}
	}
}

AStar::~AStar()
{
	//delete pointers
	for (int x = 0; x < xNodes; x++)
	{
		for (int y = 0; y < yNodes; y++)
		{
			delete nodes[x][y];
		}
	}
}

void AStar::setDangerNode(int inNodeXIndex, int inNodeYIndex)
{
	//set the node to not be safe
	nodes[inNodeXIndex][inNodeYIndex]->setSafeNode(false);
}

void AStar::setSafeNode(int inNodeXIndex, int inNodeYIndex)
{
	//set the node to not be safe
	nodes[inNodeXIndex][inNodeYIndex]->setSafeNode(true);
}

void AStar::findNewPath(int inStartX, int inStartY, int inEndX, int inEndY)
{
	//reset listed information and start and stop nodes
	for (int x = 0; x < xNodes; x++)
	{
		for (int y = 0; y < yNodes; y++)
		{
			nodes[x][y]->setListed(false);
			nodes[x][y]->setStartNode(false);
			nodes[x][y]->setEndNode(false);
		}
	}

	//reset open closed list and the best path
	openList.clear();
	closedList.clear();
	bestPath.clear();

	//initialise start and end nodes
	nodes[inStartX][inStartY]->setStartNode(true);
	nodes[inEndX][inEndY]->setEndNode(true);

	//push back the start node to the open list and set it as listed
	openList.push_back(*nodes[inStartX][inStartY]);
	nodes[inStartX][inStartY]->setListed(true);

	//initialise the start, current and end node index
	startX = currentX = inStartX;
	startY = currentY = inStartY;
	endX = inEndX;
	endY = inEndY;

	//initialise the check
	bool reachedEnd = false;

	//the number of loops
	int loopIndex = 0;

	//loop until the end has been reached
	while (!reachedEnd)
	{
		//add the parent and child nodes to an open list if they are safe
		//and set there parent node and cost
		checkNodes(currentX, currentY);

		//find the next node
		findNextNode();

		//check if the end has been reached
		if (closedList.back().getEndNode())
		{
			//leave the loop
			reachedEnd = true;
			//Logging::logI("path found");
		}

		//if too many loops give up looking for a path
		if (loopIndex > 1300)
		{
			//leave the loop
			reachedEnd = true;
			//Logging::logI("too many loops, give up on a* test");
		}

		//increase loop index
		loopIndex++;
	}

	//find the best path
	findBestPath();
}

void AStar::checkNodes(int parentX, int parentY)
{
	//top test
	nodeTest(parentX, parentY, parentX, parentY - 1, 10);

	//left test
	nodeTest(parentX, parentY, parentX - 1, parentY, 10);

	//right test
	nodeTest(parentX, parentY, parentX + 1, parentY, 10);

	//bottom test
	nodeTest(parentX, parentY, parentX, parentY + 1, 10);
}

void AStar::nodeTest(int parentX, int parentY, int testX, int testY, int cost)
{
	//the node being tested
	Node currentNode = *nodes[testX][testY];

	//test if the test node is on the screen
	if (testX < (int)nodes.size() && testX >= 0 && testY < (int)nodes[0].size() && testY >= 0)
	{
		//test if the node is safe to move on and is not listed
		if (currentNode.getSafeNode() && !currentNode.getListed())
		{
			//set the node to be listed
			nodes[testX][testY]->setListed(true);

			//set the parent node of the node
			currentNode.setParentIndex(parentX, parentY);

			//set the cost to the cost of the parent node plus the newly added cost
			currentNode.setCostNode(nodes[parentX][parentY]->getCostNode() + cost);

			//work out the heuristic using the Manhattan method
			//(total number of squares moved horizontally and vertically to end)
			int h = (abs(testX - endX) + abs(testY - endY)) * cost;

			//set the fScore of the node
			currentNode.setFScoreNode(h + currentNode.getCostNode());

			//push the node
			openList.push_back(currentNode);
		}
	}
}

void AStar::findNextNode()
{
	//the current closest node index
	unsigned int closestIndex = 0;

	//loop through the open list of nodes
	for (unsigned int i = 1; i < openList.size(); i++)
	{
		//if the current fScore is lower set the current to the current index
		if (openList[closestIndex].getFScoreNode() >= openList[i].getFScoreNode())
		{
			closestIndex = i;
		}
	}

	//If the openList is empty
	if (openList.size() == 0)
	{
		//quit
		return;
	}

	//set the current x and y
	currentX = openList[closestIndex].getXIndex();
	currentY = openList[closestIndex].getYIndex();

	//move the initial node to the closed list
	closedList.push_back(openList[closestIndex]);

	//remove the node from the open list
	openList.erase(openList.begin() + closestIndex);
}

Vec2 AStar::getNextPathNode()
{
	//initialise and set the position of the next node to the index of the back of the closed list
	Vec2 nextNodePosition = { (float)(bestPath.back().getXIndex() * nodeDimensions.x), 
		(float)(bestPath.back().getYIndex() * nodeDimensions.y) };
	
	//remove the node at the front of the list
	bestPath.erase(bestPath.begin() + (bestPath.size() - 1));

	//return the next node position
	return nextNodePosition;
}

void AStar::findBestPath()
{
	//Copy the closed list to the local vector full path
	std::vector<Node> fullPath = closedList;

	//store the x and y index of the back of the full path as the initial parent
	int parentX = fullPath.back().getXIndex();
	int parentY = fullPath.back().getYIndex();
	
	//set a boolean for escaping the loop when the path is complete
	bool home = false;

	//loop until home
	while (!home)
	{
		//get the node at the back of the path
		Node currentNode = fullPath.back();
		//remove the node at the back of the full path
		fullPath.pop_back();
		//if the current node is the parent node
		if (parentX == currentNode.getXIndex() && parentY == currentNode.getYIndex())
		{
			//store the node to the best path
			bestPath.push_back(currentNode);
			//check if the node is a start node
			if (currentNode.getStartNode())
			{
				//home has been reached
				home = true;
			}
			else
			{
				//set the parent node to the parent node of the current nodes parent index
				parentX = currentNode.getParentXIndex();
				parentY = currentNode.getParentYIndex();
			}
		}
	}
}

// void AStar::drawLists(SDL_Renderer* renderer)
// {
// 	//set draw colour to yellow
// 	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0x00);
// 
// 	//creates a rectangle
// 	SDL_Rect box;
// 
// 	for (auto node : openList)
// 	{
// 		//update the box for the tile
// 		box.x = node.getXIndex() * (int)nodeDimensions.x;
// 		box.y = node.getYIndex() * (int)nodeDimensions.y;
// 		box.w = (int)nodeDimensions.x;
// 		box.h = (int)nodeDimensions.y;
// 
// 		//draw the tiles outline
// 		SDL_RenderDrawRect(renderer, &box);
// 	}
// 
// 	//set draw colour to red
// 	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
// 
// 	for (auto node : closedList)
// 	{
// 		//update the box for the tile
// 		box.x = node.getXIndex() * (int)nodeDimensions.x;
// 		box.y = node.getYIndex() * (int)nodeDimensions.y;
// 		box.w = (int)nodeDimensions.x;
// 		box.h = (int)nodeDimensions.y;
// 
// 		//draw the tiles outline
// 		SDL_RenderDrawRect(renderer, &box);
// 	}
// 
// 	//set draw colour to green
// 	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
// 
// 	//draw the best path
// 	for (auto node : bestPath)
// 	{
// 		//update the box for the tile
// 		box.x = node.getXIndex() * (int)nodeDimensions.x;
// 		box.y = node.getYIndex() * (int)nodeDimensions.y;
// 		box.w = (int)nodeDimensions.x;
// 		box.h = (int)nodeDimensions.y;
// 
// 		//draw the tiles outline
// 		SDL_RenderFillRect(renderer, &box);
// 	}
// }