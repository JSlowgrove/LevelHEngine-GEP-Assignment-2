#pragma once

#include "Component.h"
#include "../Maths/Vec3.h"

/**
@brief A class that handles the bounding box component.
*/
class BoundingBoxComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~BoundingBoxComponent();

	/**
	@brief A function to initalise the bounding box from a mesh.
	@param meshID The ID of the mesh.
	*/
	void initaliseBoundingBox(std::string meshID);

	/**
	@brief A function to return the dimensions of the bounding box.
	@returns The dimensions of the bounding box.
	*/
	Vec3 getBoundingBoxDimensions() { return boxDim; }

	/**
	@brief A function to scale the bounding box.
	@param The scale vector.
	*/
	void scaleBoundingBox(Vec3 scale) { boxDim = initialBoxDim * scale; }

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

	/**
	@brief A function to set the position of the box for the next loop for use with collision.
	@param inNextPos The position of the box next loop.
	*/
	void setNextPos(Vec3 inNextPos) { nextPos = inNextPos; }

	/**
	@brief A function to get the position of the box for the next loop for use with collision.
	@return The position of the box next loop.
	*/
	Vec3 getNextPos() { return nextPos; }

private:
	///The initial dimensions of the bouncing box
	Vec3 initialBoxDim;
	///The dimensions of the bouncing box
	Vec3 boxDim;
	///The position in the next loop
	Vec3 nextPos;
};