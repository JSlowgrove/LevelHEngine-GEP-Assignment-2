#pragma once

/**
@brief Creates a Node object for use with path finding.
*/
class Node
{
public:
	/**
	@brief Constructs the Node object.
	@param inNodeXIndex The Node x index.
	@param inNodeYIndex The Node y index.
	*/
	Node(int inNodeXIndex, int inNodeYIndex);

	/**
	@brief Destructs the Node object.
	*/
	~Node();

	/**
	@brief Set the parentNode index.
	@param inParentNodeXIndex The X index of the parentNode.
	@param inParentNodeYIndex The Y index of the parentNode.
	*/
	void setParentIndex(int inParentNodeXIndex, int inParentNodeYIndex);

	/**
	@brief Get the parentNode X index.
	@return The X index of the parentNode.
	*/
	int getParentXIndex();

	/**
	@brief Get the parentNode Y index.
	@return The Y index of the parentNode.
	*/
	int getParentYIndex();

	/**
	@brief Set the node.
	@param inStartNode The setting of the node.
	*/
	void setStartNode(bool inStartNode);

	/**
	@brief Get If the node is a startNode.
	@return If the node is a startNode.
	*/
	bool getStartNode();

	/**
	@brief Set the node.
	@param inEndNode The setting of the node.
	*/
	void setEndNode(bool inEndNode);

	/**
	@brief Get If the node is an endNode.
	@return If the node is an endNode.
	*/
	bool getEndNode();

	/**
	@brief Set the node.
	@param inSafe The setting of the node.
	*/
	void setSafeNode(bool inSafe);

	/**
	@brief Get If the node is safe.
	@return If the node is safe.
	*/
	bool getSafeNode();

	/**
	@brief Set the cost.
	@param inCost The cost to move to the node.
	*/
	void setCostNode(int inCost);

	/**
	@brief Get the cost.
	@return The cost to move to the node.
	*/
	int getCostNode();

	/**
	@brief Set the fScore.
	@param inFScore The fScore to of the node.
	*/
	void setFScoreNode(int inFScore);

	/**
	@brief Get the fScore.
	@return The fScore to of the node.
	*/
	int getFScoreNode();

	/**
	@brief Get the x index.
	@return The x index of the node.
	*/
	int getXIndex();

	/**
	@brief Get the y index.
	@return The y index of the node.
	*/
	int getYIndex();

	/**
	@brief Set the value of listed.
	@param inListed If the node is listed.
	*/
	void setListed(bool inListed);

	/**
	@brief Get the value of listed.
	@return If the node is listed.
	*/
	bool getListed();

private:
	///The index of the parent node.
	int parentNodeXIndex, parentNodeYIndex;
	///The index of the node.
	int nodeXIndex, nodeYIndex;
	///Boolean values to if they are a specific node.
	bool startNode, endNode;
	///If the node safe to walk on.
	bool safe;
	///The cost to move to the node.
	int cost;
	///The f score of the node.
	int fScore;
	///Boolean values for if the node is on a list.
	bool listed;
};