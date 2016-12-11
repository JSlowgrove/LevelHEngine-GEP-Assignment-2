#pragma once

#include "Component.h"
#include "../Maths/Vec3.h"

/**
@brief A class that handles the bounding box component.
*/
class BoundingBoxComponent : public Component
{
public:
	virtual ~BoundingBoxComponent();

	void initaliseBoundingBox(std::string meshID);
	Vec3 getBoundingBoxDimensions() { return boxDim; }
	void scaleBoundingBox(Vec3 scale) { boxDim = initialBoxDim * scale; }

	virtual void onAwake();
	virtual void onDestroy();

private:
	///The initiial dimensions of the bouncing box
	Vec3 initialBoxDim;
	///The dimensions of the bouncing box
	Vec3 boxDim;
};