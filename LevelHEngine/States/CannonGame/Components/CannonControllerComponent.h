#pragma once

#include "../../../Components/Component.h"
#include "../../../Maths/Vec2.h"

/**
@brief A class that handles the cannon controller component.
*/
class CannonControllerComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~CannonControllerComponent();

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

	void handleInput();

	void update();
	void setCannonPower(float inPower) { cannonPower = inPower; }
	float getCannonPower() { return cannonPower; }

	void setCannonAngle(Vec2 inAngle) { cannonAngle = inAngle; }
	Vec2 getCannonAngle() { return cannonAngle; }

	void setCannonRotation(Vec3 inRot) { cannonRot = inRot; }
	Vec3 getCannonRotation() { return cannonRot; }

	Vec3 getCannonLaunchVelocities() { return calculateLaunchVeclocites(); }

private:
	///The cannon velocity
	float cannonPower;
	///The cannon angle
	Vec2 cannonAngle;
	///The cannon rotation
	Vec3 cannonRot;
	///The speed of the rotation
	float rotationSpeed;

	Vec3 calculateLaunchVeclocites();
};