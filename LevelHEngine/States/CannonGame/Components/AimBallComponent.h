#pragma once

#include "../../../Components/Component.h"
#include "../../../Maths/Vec3.h"

/**
@brief A class that handles the aim ball component.
*/
class AimBallComponent : public Component
{
public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~AimBallComponent();

	/**
	@brief A virtual function for the componets awake
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy
	*/
	virtual void onDestroy();

	void setVelocities(Vec3 inVel);

	void update();

	void setResetPos(Vec3 inPos) { resetPos = inPos; }
	void resetBall();

	void applyGravity();

	void setUse(bool use) { inUse = use; }

private:
	///The velocites of the ball
	Vec3 velocities;
	Vec3 resetPos;
	bool inUse;
};