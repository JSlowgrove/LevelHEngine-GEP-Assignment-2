#pragma once

#include "Component.h"

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

private:
	///The initial radius of the bounding sphere
	float initialSphereRad;
	///The  radius of the bounding sphere
	float sphereRad;
};