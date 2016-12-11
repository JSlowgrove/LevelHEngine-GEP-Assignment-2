#pragma once

#include "Component.h"

/**
@brief A class that handles the bounding sphere component.
*/
class BoundingSphereComponent : public Component
{
public:
	virtual ~BoundingSphereComponent();

	void initaliseBoundingSphere(std::string meshID);
	float getBoundingSphereRadius() { return sphereRad; }
	void scaleBoundingSphere(Vec3 scale) { sphereRad = initialSphereRad * scale.x; }

	virtual void onAwake();
	virtual void onDestroy();

private:
	///The initial radius of the bounding sphere
	float initialSphereRad;
	///The  radius of the bounding sphere
	float sphereRad;
};