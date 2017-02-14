#pragma once

#include "Component.h"
#include "../Maths/Vec3.h"

/**
@brief A class that handles the bounding sphere component.
*/
class BoundingSphereComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~BoundingSphereComponent();

	/**
	@brief A function to initalise the bounding sphere from a mesh.
	@param meshID The ID of the mesh.
	*/
	void initaliseBoundingSphere(std::string meshID);

	/**
	@brief A function to return the radius of the bounding sphere.
	@returns The radius of the bounding sphere.
	*/
	float getBoundingSphereRadius() { return sphereRad; }

	/**
	@brief A function to scale the sphere.
	@param The scale vector.
	*/
	void scaleBoundingSphere(Vec3 scale) { sphereRad = initialSphereRad * scale.x; }

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

	/**
	@brief A function to set the position of the sphere for the next loop for use with collision.
	@param inNextPos The position of the sphere next loop.
	*/
	void setNextPos(Vec3 inNextPos) { nextPos = inNextPos; }

	/**
	@brief A function to get the position of the sphere for the next loop for use with collision.
	@return The position of the sphere next loop.
	*/
	Vec3 getNextPos() { return nextPos; }

private:
	///The initial radius of the bounding sphere
	float initialSphereRad;
	///The  radius of the bounding sphere
	float sphereRad;
	///The position in the next loop
	Vec3 nextPos;
};