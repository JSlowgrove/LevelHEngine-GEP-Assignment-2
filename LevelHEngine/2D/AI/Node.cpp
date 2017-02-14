#include "Node.h"

Node::Node(int inNodeXIndex, int inNodeYIndex)
{
	//initialise the booleans
	startNode = false;
	endNode = false;
	listed = false;
	safe = true;

	//initialise the variables
	nodeXIndex = inNodeXIndex;
	nodeYIndex = inNodeYIndex;
	parentNodeXIndex = 0;
	parentNodeYIndex = 0;
	cost = 0;
	fScore = 0;
}

Node::~Node()
{
}

void Node::setParentIndex(int inParentNodeXIndex, int inParentNodeYIndex)
{
	//set the variables to the input
	parentNodeXIndex = inParentNodeXIndex;
	parentNodeYIndex = inParentNodeYIndex;
}

int Node::getParentXIndex()
{
	//return the x parent node index
	return parentNodeXIndex;
}

int Node::getParentYIndex()
{
	//return the y parent node index
	return parentNodeYIndex;
}

void Node::setStartNode(bool inStartNode)
{
	//set the node
	startNode = inStartNode;
}

bool Node::getStartNode()
{
	//return startNode
	return startNode;
}

void Node::setEndNode(bool inEndNode)
{
	//set the node
	endNode = inEndNode;
}

bool Node::getEndNode()
{
	//return endNode
	return endNode;
}

void Node::setSafeNode(bool inSafe)
{
	//set the node
	safe = inSafe;
}

bool Node::getSafeNode()
{
	//return safeNode
	return safe;
}

void Node::setCostNode(int inCost)
{
	//set the node cost
	cost = inCost;
}

int Node::getCostNode()
{
	//return the node cost
	return cost;
}

void Node::setFScoreNode(int inFScore)
{
	//set the node fScore
	fScore = inFScore;
}

int Node::getFScoreNode()
{
	//return the node fScore
	return fScore;
}

int Node::getXIndex()
{
	//return the node x index
	return nodeXIndex;
}

int Node::getYIndex()
{
	//return the node y index
	return nodeYIndex;
}

void Node::setListed(bool inListed)
{
	//set the node
	listed = inListed;
}

bool Node::getListed()
{
	//return listed
	return listed;
}